#include <iostream>
#include <cstdlib>
#include <ctime>
#include "walks.hpp"
#include "3D_SAW.cpp"
#include "paths.hpp"

using namespace std;

long long SAWcounter_3D(int N); 
/* Abuses symmetries of the square lattice to hopefully find the number of SAWs about 48 times as fast as usual */

int main() {

	int N;
	cout << "Please enter an integer N > 1. SAWcounter will calculate the number of SAWs of length N.\n";
	cin >> N;
	clock_t begin, end;
	double timespent;
	begin = clock();
	cout << "According to SAWcounter_3D, there are " << SAWcounter_3D(N)
	     << " SAWs of length " << N << " on the 3D lattice.\n";
	end = clock();
	timespent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "The calculation took " << timespent << " seconds.\n";
	return 0;

}


long long SAWcounter_3D(int N) {
	
	long long output=0;
	node *walk1, *walk2, *walk3;
	direction string[1];
	int ell1,ell2,ell[3];
	for (ell1=1; ell1<N; ell1++) {
		for (ell2=1; ell2 <= (N-ell1); ell2++) {
			if ((ell1 + ell2) == N) {
				output = output + 24; }
			else {
			/* Initialize 3-dimensional hook and calculate nr of walks */				
				ell[0] = ell1; ell[1] = ell2; ell[2] = 1;
				walk1 = hook(ell);
				//walk_output(*walk1);
				//cout << pathSAW(walk1,N,false,true) << "\n";
				output = output + 48 * pathSAW(walk1,N,false,true);
				free(walk1);

			/* Initialize 2-dimensional hooks and calculate nr of walks */
				ell[0] = ell1; ell[1] = ell2; ell[2] = 0;
				string[0].coord = 0; string[0].sign = true;
				walk1 = hook(ell); walk2 = walk_from_string(string,1); walk3 = concatenate(*walk1,*walk2);
				//walk_output(*walk3);
				//cout << pathSAW(walk3,N,true,false) << "\n";
				output = output + pathSAW(walk3,N,true,false);
				free(walk2); free(walk3);

				string[0].sign = false;
				walk2 = walk_from_string(string,1); walk3 = concatenate(*walk1,*walk2);
				//walk_output(*walk3);
				//cout << pathSAW(walk3,N,true,false) << "\n";
				output = output + pathSAW(walk3,N,true,false);
				free(walk1); free(walk2); free(walk3);
			}
		}
	}

	output = output + 6;
	return output;
}





