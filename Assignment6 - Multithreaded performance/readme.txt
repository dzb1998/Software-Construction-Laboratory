Zhubo Deng
605186231

The original program didn't implement multithreading, so we want to implement 
multithreading to make it more efficient.

I added three global variables to control the thread: 

	int nthreads;
	scene_t scene;
	float threadArr[width][height][3];

and I added another function to do the split threading:

	void *fillThreadArr(void *thread_num) 

In this function, I just paste the code from the original main because we want 
it to perform the original syxtax.

In the main, I set up the threading with:

	ret = pthread_create(&tid[n], NULL, fillThreadArr, &thread_num[n]);
	ret = pthread_join(tid[n], NULL);

which basically were what we learned in the class.

While I was testing the code, it first came to a run-time error. The server 
didn't response in a long time, so I hit contorl-c to exit and go back to 
check the code again.

I notice that in the old version of main function, 

	int nthreads = argc == 2 ? atoi( argv[1] ) : 0;
	scene_t scene = create_sphereflake_scene( sphereflake_recursion );

Since I already declare them in the global variable, so there's no need to 
re-set them in the main.

Then I modified:

	nthreads = argc == 2 ? atoi( argv[1] ) : 0;
	scene = create_sphereflake_scene( sphereflake_recursion );


The code finally works, and the result I got (which was also in the separate 
make-log.txt file):

	[classzde@lnxsrv06 ~/srt]$ make clean check
	rm -f *.o *.tmp 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm srt srt.tgz
	gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o 
	main.o main.c
	gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o 
	raymath.o raymath.c
	gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o 
	shaders.o shaders.c
	gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o 
	raymath.o shaders.o -lm -lpthread
	time ./srt 1-test.ppm >1-test.ppm.tmp

	real	0m47.956s
	user	0m47.945s
	sys	0m0.003s
	mv 1-test.ppm.tmp 1-test.ppm
	time ./srt 2-test.ppm >2-test.ppm.tmp

	real	0m23.942s
	user	0m47.619s
	sys	0m0.004s
	mv 2-test.ppm.tmp 2-test.ppm
	time ./srt 4-test.ppm >4-test.ppm.tmp

	real	0m12.186s
	user	0m48.562s
	sys	0m0.005s
	mv 4-test.ppm.tmp 4-test.ppm
	time ./srt 8-test.ppm >8-test.ppm.tmp

	real	0m6.488s
	user	0m50.418s
	sys	0m0.005s
	mv 8-test.ppm.tmp 8-test.ppm
	for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
	  diff -u baseline.ppm $file || exit; \
	done
	[classzde@lnxsrv06 ~/srt]$ 

The improvement of implementing multithreading is obvious. After testing, the 
thread number = 8 is the fastest, followed by 4, 2, 1, as we expected, since 
the more threads they are parallel while processing, the faster the time it 
will take. When I actually run the program, I did feel it took less time when 
thread number goes larger, as the "time" record shown above.



