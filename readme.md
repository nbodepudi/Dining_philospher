
GROUP NUMBER: 16
Members :
Naga Sai Bodepudi		         140123011
Sai Teja Talasila                140123040
Charan Kesav Akkalla			 140123004
Sujay Lakkimsetti			     140123020

	We have implemented using mutex and condition variables in pthreads library as suggested in Project 2 - The Dining Philosophers Problem of 
	Chapter 6 of Text Book (OS)Concepts, Ninth Edition, Silberschatz, Galvin, Gagne) Pg. No. 301.
	We have provided five outputs of my code in files attached.
	Most of implementation is included in comments in DiningPhilosphers.c file.
	compilation :
		gcc DiningPhilosphers DiningPhilosphers.c -pthreads
		./DiningPhilosphers
	
 	NO Deadlocks and Starvation have been detected for any number of eating times.
	
	
	The Average hungry time obtained is :
	output1 :
		 PHILOSPHER 1 ------------- 0.930000 
		 PHILOSPHER 2 ------------- 1.040000 
		 PHILOSPHER 3 ------------- 0.810000 
		 PHILOSPHER 4 ------------- 0.880000 
		 PHILOSPHER 5 ------------- 1.095000 
	output2: 
		 PHILOSPHER 1 ------------- 0.840000 
		 PHILOSPHER 2 ------------- 0.950000 
		 PHILOSPHER 3 ------------- 0.980000 
		 PHILOSPHER 4 ------------- 0.915000 
		 PHILOSPHER 5 ------------- 0.840000 
	output3:
		 PHILOSPHER 1 ------------- 0.825000 
		 PHILOSPHER 2 ------------- 0.975000 
		 PHILOSPHER 3 ------------- 0.855000 
		 PHILOSPHER 4 ------------- 0.795000 
		 PHILOSPHER 5 ------------- 0.965000  and etc.
