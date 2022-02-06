## Bind vs Lambda comparison

**********************
	1. Compile time
	2. Execution time
	3. Valgrind tool
**********************

**********************
***  Using Bind    ***
**********************

[ratnesh1.tiwari@localhost ep016_avoiding_std_bind]$
[ratnesh1.tiwari@localhost ep016_avoiding_std_bind]$ /usr/bin/time g++ -Wall -Wpedantic -g -std=c++17 -o Bind_vs_Lambda Bind_vs_Lambda.cpp
0.51user 0.06system 0:00.58elapsed 99%CPU (0avgtext+0avgdata 78060maxresident)k
0inputs+2808outputs (0major+26242minor)pagefaults 0swaps

[ratnesh1.tiwari@localhost ep016_avoiding_std_bind]$ /usr/bin/time ./Bind_vs_Lambda
0.24user 0.00system 0:00.24elapsed 99%CPU (0avgtext+0avgdata 1020maxresident)k
0inputs+0outputs (0major+299minor)pagefaults 0swaps

[ratnesh1.tiwari@localhost ep016_avoiding_std_bind]$ valgrind --tool=callgrind ./Bind_vs_Lambda
==47601== Callgrind, a call-graph generating cache profiler
==47601== Copyright (C) 2002-2017, and GNU GPL'd, by Josef Weidendorfer et al.
==47601== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==47601== Command: ./Bind_vs_Lambda
==47601==
==47601== For interactive control, run 'callgrind_control -h'.
==47601==
==47601== Events    : Ir
==47601== Collected : 1161438253
==47601==
==47601== I   refs:      1,161,438,253
[ratnesh1.tiwari@localhost ep016_avoiding_std_bind]$

**********************
***  Using Lambda  ***
**********************

[ratnesh1.tiwari@localhost ep016_avoiding_std_bind]$ /usr/bin/time g++ -Wall -Wpedantic -g -std=c++17 -o Bind_vs_Lambda Bind_vs_Lambda.cpp
0.47user 0.06system 0:00.54elapsed 99%CPU (0avgtext+0avgdata 73040maxresident)k
0inputs+2528outputs (0major+24704minor)pagefaults 0swaps

[ratnesh1.tiwari@localhost ep016_avoiding_std_bind]$ /usr/bin/time ./Bind_vs_Lambda
0.18user 0.00system 0:00.18elapsed 99%CPU (0avgtext+0avgdata 1020maxresident)k
0inputs+0outputs (0major+299minor)pagefaults 0swaps

[ratnesh1.tiwari@localhost ep016_avoiding_std_bind]$ valgrind --tool=callgrind ./Bind_vs_Lambda
==54242== Callgrind, a call-graph generating cache profiler
==54242== Copyright (C) 2002-2017, and GNU GPL'd, by Josef Weidendorfer et al.
==54242== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==54242== Command: ./Bind_vs_Lambda
==54242==
==54242== For interactive control, run 'callgrind_control -h'.
==54242==
==54242== Events    : Ir
==54242== Collected : 924438020
==54242==
==54242== I   refs:      924,438,020
[ratnesh1.tiwari@localhost ep016_avoiding_std_bind]$
[ratnesh1.tiwari@localhost ep016_avoiding_std_bind]$


**********************
*** END OF FILE    ***
**********************


