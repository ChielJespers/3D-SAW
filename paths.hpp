
using namespace std;



void clear_path(bool ***occ, int path[][3], int N){
	int i,j,k;
	for (i=0; i < 2*N+1; i++) {
		for(j=0; j < 2*N+1; j++) {
			for (k=0; k<2*N+1; k++) {
				occ[i][j][k] = false;
			}
		}
	}

	for (i=0; i < N+1; i++) {
		for (j=0; j<3; j++) {
			path[i][j];
		}
	}
}

long long pathSAW(node *walk, int N, bool weighted, bool directions)
{
/* Counts the number of SAWs of length N starting with the path specified by walk */
/* If weighted == true, counts the SAWs with weight */

	int i=0, j=0, length = walk_length(*walk);
	int path[N+1][DIM];
	long long output = 0;
	bool ***occ = cuboidallocb(2*N+1,2*N+1,2*N+1);

/* Check for empty and very long walks */
	if (length < 0) {
		cout << "Can not count the number of walks without a specified starting point.\n";
		return -1;
		}
	if (length > N) {
		return 0; }

/* Clear pre-existing paths */
	clear_path(occ,path,N);

/* Set up the path specified by walk */
	node *temp = walk;
	for (i=0; i < length; i++) {
		for (j=0; j<DIM; j++) {
			path[i][j] = N + temp->coord[j]; 
		}  /* Lattice has offset -N,-N, so the origin is (N,N,N) */
		occ[path[i][0]][path[i][1]][path[i][2]] = true;
		temp = temp->nextptr;
	}
	for (j=0; j<DIM; j++) {
		path[length][j] = N + temp->coord[j]; }

/* Application of SAW */
	if (weighted) {
		wSAW(length, N, occ, path, output, directions); }
	else {
		SAW(length, N, occ, path, output); }

/* Output and clean-up*/
	cuboidfreeb(occ);
	return output;

}

void path_output(bool **occ, int N) {
	int i,j;
	for (i=0; i < 2*N+1; i++) {
		for (j=0; j < 2*N+1; j++) {
			if (occ[i][j] == true) {
				cout << " 1"; }
			else {
				cout << " 0"; }
		}
		cout << "\n";
	}
}








