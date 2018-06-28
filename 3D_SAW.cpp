
bool ***cuboidallocb(int k, int m, int n) {
	/* This function allocates a k x m x n cuboid of booleans */
	int i,j;
	bool *pb, **ppb, ***pppb;

	if (k==0){
		pppb = NULL;
	} 
	else {
		pppb= (bool ***)malloc(k*sizeof(bool **));
		if (pppb==NULL) {
			exit(1); }
		if (m==0){
			for (i=0; i<k; i++) {
				pppb[i] = NULL; }
		}
		else {
			ppb = (bool **)malloc(k*m*sizeof(bool *));
			if (ppb==NULL) {
				exit(1); }
			pppb[0] = ppb;
			for (i=1; i<k; i++) {
				pppb[i] = pppb[i-1]+m; }
			if (n==0){
				for (i=0; i<k; i++) {
					for (j=0; j<m; j++) {
						pppb[i][j] = NULL;
					}
				}
			}
			else {
				pb = (bool *)malloc(k*m*n*sizeof(bool));
				if (pb==NULL) {
					exit(1); }
				pppb[0][0] = pb;
				for (i=0; i<k-1; i++) {
					for (j=1; j<m; j++) {
						pppb[i][j] = pppb[i][j-1] + n;
					}
					pppb[i+1][0] = pppb[i][m-1] + n;
				}
				for (j=1; j<m; j++) {
					pppb[k-1][j] = pppb[k-1][j-1] + n; }
			}
		}
	}
	return pppb;

}


void cuboidfreeb(bool ***pppb){
	/* This function frees a cuboid of booleans */

	if (pppb!=NULL){
		if (pppb[0]!=NULL){
			if (pppb[0][0]!=NULL){
				free(pppb[0][0]);
			}
		free(pppb[0]);
		}
	free(pppb);
    }

}


void SAW(int i, int N, bool ***occ, int path[][3], long long & counter)
{
	int sign,k,l;
	if (!occ[path[i][0]][path[i][1]][path[i][2]]){
		if (i==N){
			counter++;
		}
		else{
		/* Try all paths starting at (path_x[i],path_y[i]) */
			occ[path[i][0]][path[i][1]][path[i][2]]=true;
			for (sign=-1; sign<2; sign=sign+2) {
				for (k=0; k<DIM; k++) {
					for (l=0; l<DIM; l++) {
						if (k==l) {
							path[i+1][l] = path[i][l] + sign; }
						else {
							path[i+1][l] = path[i][l]; }
					}
					SAW(i+1,N,occ,path,counter);
				}
			}
			occ[path[i][0]][path[i][1]][path[i][2]]=false;
		}
	}
}


void wSAW(int i, int N, bool ***occ, int path[][3], long long & counter, bool directions)
{
	int sign,k,l;
	if (!occ[path[i][0]][path[i][1]][path[i][2]]){
		if (i==N){
			if (directions) {
				counter = counter + 48;
			}
			else {
				counter = counter + 24;
			}
		}
		else{
		/* Try all paths starting at (path_x[i],path_y[i]) */
			occ[path[i][0]][path[i][1]][path[i][2]]=true;
			for (sign=-1; sign<2; sign=sign+2) {
				for (k=0; k<DIM; k++) {
					for (l=0; l<DIM; l++) {
						if (k==l) {
							path[i+1][l] = path[i][l] + sign; }
						else {
							path[i+1][l] = path[i][l]; }
					}
					if (k==2) {
						if (directions == false) {
							if (sign == 1) {
								directions = true;
								wSAW(i+1,N,occ,path,counter,directions);
								directions = false;
							}
						}
						else {
							wSAW(i+1,N,occ,path,counter,directions); }
					}
					else {
						wSAW(i+1,N,occ,path,counter,directions); }
				}
			}
			occ[path[i][0]][path[i][1]][path[i][2]]=false;
		}
	}
}
