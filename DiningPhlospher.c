#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>


int MAX_ITER = 200;								// number of eating times
int num = 5;								        // number of philospers and forks
double waiting_time_averages [ 5 ];						// storing of average hungry time
enum { thinking, hungry, eating } state [ 5 ];					// philospher states
pthread_mutex_t lock;								// mutex for accessing philospher states to avoid deadlock
pthread_cond_t self [ 5 ];							// condition variable for accessing 
pthread_t philo [ 5 ];
int identity [ 5 ] = { 0, 1, 2, 3, 4 };
int eat_count = 0;


void *phil_run ( void *arg );
void *pickup_forks ( int );
void *return_forks ( int );
void *test ( int );

int main ( )
{	
	pthread_mutex_init ( &lock, NULL );
	int i = 0;
	for ( i = 0; i < num; i++ )						// intialization
	{
		state [ i ] = thinking;
		pthread_cond_init ( &self [ i ], NULL );
		waiting_time_averages [ i ] = 0.0; 
	}
										// thread identifier
	for ( i = 0; i < num; i++ )
	{
		pthread_create ( &philo [ i ], NULL, phil_run, &identity [i]);	// creating threads with default attributes and their number as
										// passing value to program
	}
	
	for ( i = 0; i < num; i++ )						// waiting for thread termination sequentially 			
	{
		pthread_join ( philo [ i ], NULL );						
		printf ( "Thread of Philospher %d is finished executing \n", i+1 );
	}
	
	/* Printing the values of average waiting times of each philospher while staying hungry to compare waiting times */
	
	printf ( "The Hungry Time averages of Philosphers are : \n" );
	
	for ( i = 0; i < num; i++ )						// printing waiting times
	{
		printf ( " PHILOSPHER %d ------------- %f \n", i+1, waiting_time_averages [ i ] );
	}
	return 0;
}

/* phil_run allows each philospher to think and eat which we execute as seperate thread */

void *phil_run ( void *arg )
{	
	int *tmp_ptr = ( int *)arg;
	int id = *tmp_ptr;
	double total_waiting_time = 0.0;
	time_t start_t, end_t;
	double time_of_wait;
	printf ("Philospher %d started working \n",id + 1);
	time_t t;
	srand ( ( unsigned ) time ( &t ) );
	
	for ( int iter = 0; iter < MAX_ITER; iter++ )
	{
		printf ( "# Eating count = %d \n", eat_count );
		
		int rand_time = ( rand())%2 + 1;							// random thinking time
		printf ( "Philospher %d is Thinking for %d seconds. \n", id + 1 , rand_time );
		//float rnd_time = ((float)rand_time) / 1000.0;
		sleep ( rand_time );
		
		time ( &start_t );
		pickup_forks ( id );									// picking forks
		time ( &end_t );
		time_of_wait = difftime ( end_t, start_t );						// hungry time caluculation
		printf ( "Philospher %d is Hungry for %f seconds. \n", id + 1, time_of_wait );
		
		int rnd_time = ( rand())%2 + 1;								// random eating time
		sleep ( rnd_time );
		printf ( "Philospher %d eating at %d th time for %d seconds. \n", id + 1, iter+1, rnd_time );
		return_forks ( id );									// returning forks
		
		eat_count++;
		total_waiting_time = total_waiting_time + time_of_wait; 
	}
	
	waiting_time_averages [ id ] = total_waiting_time / 200.00;
	
	return NULL;
}

/* function to pick forks */

void *pickup_forks ( int id )
{
	pthread_mutex_lock ( &lock );						// lock to access states
	state [ id ] = hungry;
	pthread_mutex_unlock ( &lock );
	test ( id );								 
	pthread_mutex_lock ( &lock );
	if ( state [ id ] != eating )
	{
		pthread_cond_wait ( &self [ id ], &lock );			// condition wait if forks not available
	}
	pthread_mutex_unlock ( &lock );
	return NULL;
}

/* function to release forks */

void *return_forks ( int id )
{
	pthread_mutex_lock ( &lock );						
	state [ id ] = thinking;
	pthread_mutex_unlock ( &lock );
	test ( ( id + num - 1 ) % num );					// call to check for other philosphers to avoid starvation
	test ( ( id + 1 ) % num );
}

/* function to allocate forks and avoid deadlocks */

void *test ( int id )
{
	int is_even = ( id % 2 == 0);						// old implementation to avoid deadlock
	int num1 = ( id + num -1 ) % num;
	int num2 = ( id + 1 ) % num;
	if ( is_even )
	{

		pthread_mutex_lock( &lock );
		if ( (state[num1] != eating) && (state[num2] != eating) && (state[id] == hungry) )
		{
			state[ id ] = eating;
			pthread_cond_signal ( &self [ id ] );
		}
		pthread_mutex_unlock( &lock );
	}
	else
	{
		pthread_mutex_lock( &lock );
		if ( (state[num1] != eating) && (state[num2] != eating) && (state[id] == hungry) )
		{
			state[ id ] = eating;
			pthread_cond_signal ( &self [ id ] );
		}
		pthread_mutex_unlock( &lock );
	}
}

