#include <iostream>
#include <cstdlib>
#include <ctime>
#include "walks.hpp"
#include "3D_SAW.cpp"
#include "paths.hpp"

using namespace std;

int ell[3] = {1,3,1};

int main()
{
	long long counter = 0;

	clock_t begin, end;
	double timespent;

	int N;
	cout << "Please enter an integer N>1. SAWcounter will count the number of SAWs of length N.\n";
	cin >> N;

	node *walk = line(0,0);
	walk_output(*walk);

	begin = clock();
	counter = pathSAW(walk,N,false,true);
	end = clock();

	cout << "According to SAWcounter, there are " << counter
	     << " SAWs of length " << N << " on the 3D lattice\n";

	timespent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "The calculation took " << timespent << " seconds.\n";


	return 0;
}

