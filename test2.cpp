#include <iostream>
#include <cstdlib>
#include <ctime>
#include "walks.hpp"
#include "3D_SAW.cpp"
#include "paths.hpp"

using namespace std;


int main () {

	int N = 3;
	direction string[1]; string[0].coord = 0; string[0].sign = false;
	node *walk1 = line(0,0), *walk2 = walk_from_string(string,1), *walk3 = concatenate(*walk1,*walk2);
	cout << pathSAW(walk3,N,false,false) << "\n";

}


