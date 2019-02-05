# Multithreaded PI Approximation 

Main code: piApprox.cpp

Following solution calculates PI number approximation using Monte Carlo method and multiple threads. Before calculation takes place, user is asked to input number of samples and number of threads.

This project was created in Microsoft Visual Studio 2015.
Raw *.cpp file and a compiled program for Linux can be found in "For Linux" folder. Used g++ 7.2.1 compiler.

*IMPORTANT* If you are willing to compile piApprox.cpp in your Linux terminal, be sure to add -pthread option during compiling (e.g. "g++ piApproxLinux.cpp -o piApproxLinux -pthread").
