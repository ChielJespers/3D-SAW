
using namespace std;

const int DIM=3; /* Walks on the DIM-dimensional lattice */


typedef struct node node;
struct node {
	int coord[DIM];
	node *nextptr;
};

typedef struct direction direction;
struct direction {
	int coord;
	bool sign;
};

void copydata(node *walk1, node walk2) {
/* Copies the data in walk2 to walk1 */
	if (walk1 == NULL) {
		cout << "Invalid input: walk1 is NULL.\n";
		exit(1); 
	}

	int i;
	for (i=0; i<DIM; i++) {
		walk1->coord[i] = (walk2.coord)[i];
	}

}

void copydata(int coord[DIM], node walk2) {
/* Copies the data in walk2 to coord[DIM] */
	int i;
	for (i=0; i<DIM; i++) {
		coord[i] = (walk2.coord)[i];
	}

}

void copydata(node* walk1, int coord[DIM]) {
/* Copies the data in coord[DIM] to walk1 */
	int i;
	if (walk1 == NULL) {
		exit(1); }
	for (i=0; i<DIM; i++) {
		walk1->coord[i] = coord[i]; 
	}

}

node* line(int n, int i) {
/* Creates a line of length n (so consisting of n+1 nodes) starting at (0,0,..,0) going in the i-th direction  */
	if ((i > DIM-1) || (i < 0)) {
		return NULL; }
	node *output, *temp;
	output = (node*)malloc((n+1)*sizeof(node));
	temp = output;
	int j,k;
	for (j=0; j<n; j++) {
		for (k=0; k<DIM; k++) {
			if (k == i) {
				temp->coord[k] = j; }
			else {
				temp->coord[k] = 0; }
		}
		temp->nextptr = temp + 1;
		temp = temp->nextptr;		
	}
	for (k=0; k<DIM; k++) {
		if (k == i) {
			temp->coord[k] = j; }
		else {
			temp->coord[k] = 0; }
	}
	temp->nextptr = NULL;
	return output;
}



node* walk_from_string(direction string[], int n) {
/* Creates a walk of length n starting at the origin from a string of directions */
	if (n < 0) {
		return NULL; }
	int i,j, tempcoord[DIM];
	node *output, *temp;
	output = (node*)malloc((n+1)*sizeof(node));
	temp = output;
	for (j=0; j<DIM; j++) {
		temp->coord[j] = 0; }
	for (i=0; i<n; i++) {
		temp->nextptr = temp + 1;
		if ((string[i].coord < 0) || (string[i].coord >= DIM)) {
			cout << "Invalid input.\n";
			exit(1);
		}

		for (j=0; j<DIM; j++) {
			if (j == string[i].coord) {
				if (string[i].sign == true) {
					tempcoord[j] = temp->coord[j] + 1; }
				else {
					tempcoord[j] = temp->coord[j] - 1; }
			}
			else {
				tempcoord[j] = temp->coord[j]; 
			}
		}
		temp = temp->nextptr;
		for (j=0; j<DIM; j++) {
			temp->coord[j] = tempcoord[j]; }
	}
	temp->nextptr = NULL;
	return output;
}

int walk_length(node walk) {
/* Returns the length of a walk */
	node *temp = walk.nextptr;
	int output = 0;
	while(temp != NULL) {
		output++;
		temp = temp->nextptr;
	}
	return output;
}
node* concatenate(node walk1, node walk2) {
/* Takes two walks of length n1 respectively n2 and returns the head-tail concatenation of them */

	int n1, n2;
	n1 = walk_length(walk1); n2 = walk_length(walk2);

/* Check for empty paths */
	if (n1 < 0) {
		return NULL; }
	if (n2 < 0) {
		return NULL; }

/* Form the concatenation */
	node *output, temp1, *temp2;
	int tempcoord[DIM];
	output = (node*)malloc((n1+n2+1)*sizeof(node));
	temp1 = walk1; temp2 = output;
	int i;

	while (true) {
		copydata(temp2,temp1);
		if (temp1.nextptr != NULL) {
			temp1 = *(temp1.nextptr);
			temp2->nextptr = temp2 + 1;
			temp2 = temp2->nextptr; 
		}
		else {
			break; }
	}
	copydata(tempcoord,*temp2);
	temp2->nextptr = temp2 + 1;
	temp1 = walk2;
	while (true) {
		for (i=0; i<DIM; i++) {
			temp2->coord[i] = (temp1.coord)[i] + tempcoord[i];
		}
		if (temp1.nextptr != NULL) {
			temp1 = *(temp1.nextptr);	
			temp2->nextptr = temp2 + 1; 
			temp2 = temp2->nextptr;
		}
		else {
			break; }
	}
	temp2->nextptr = NULL;
	return output;
}

node* hook(int ell[DIM]) {
/* Creates a hook-shaped walk with parameters ell[0],...,ell[DIM-1]. */
	int i;
	if (ell[0] < 0) {
		return NULL; }
	node *output = line(ell[0],0), *temp1, *temp2;
	for (i=1; i<DIM; i++) {
		if (ell[i] < 0) {
			return NULL; }
		temp1 = line(ell[i],i);
		temp2 = concatenate(*output,*temp1);
		free(temp1);
		temp1 = output; output = temp2;
		free(temp1);
	}
	return output;
}

void walk_output(node walk) {
/* Outputs the x- and y- coordinates of a given walk */
	node temp = walk;
	int i; 
	while (true) {
		cout << "(";
		for (i=0; i<DIM-1; i++) {
			cout << (temp.coord)[i] << ","; }
		cout << (temp.coord)[DIM-1] << "), ";
		if (temp.nextptr != NULL) {
			temp = *(temp.nextptr); }
		else {
			break; }
	}
	std::cout << "\n";
}
