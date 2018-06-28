
using namespace std;


typedef struct tnode tnode;
struct tnode { //works
	tnode *up;
	tnode *down;
	tnode *right;
	tnode *left;
	tnode *prev;
};

tnode *addwalk(int path_x[], int path_y[], int n, int start, tnode* input) { //works
/* If (path_x,path_y) is a path of length n, adds the part of the path starting at "start"
   to the tree "input" */
	int i;
	tnode *temp2;
	temp2 = input;
	for (i=start; i<n; i++) {
		if ((path_x[i+1] - path_x[i]) == 0) {
			if ((path_y[i+1] - path_y[i]) == 1) {
				if (temp2->up == NULL) {
					temp2->up = (tnode*)calloc(1,sizeof(tnode));
					temp2->up->prev = temp2;
				}
				temp2 = temp2->up;
			}
			if ((path_y[i+1] - path_y[i]) == -1) {
				if (temp2->down == NULL) {
					temp2->down = (tnode*)calloc(1,sizeof(tnode));
					temp2->down->prev = temp2;
				}
				temp2 = temp2->down;
			}
		}

		if ((path_y[i+1] - path_y[i]) == 0) {
			if ((path_x[i+1] - path_x[i]) == 1) {
				if (temp2->right == NULL) {
					temp2->right = (tnode*)calloc(1,sizeof(tnode));
					temp2->right->prev = temp2;
				}
				temp2 = temp2->right;
			}
			if ((path_x[i+1] - path_x[i]) == -1) {
				if (temp2->left == NULL) {
					temp2->left = (tnode*)calloc(1,sizeof(tnode));
					temp2->left->prev = temp2;
				}
				temp2 = temp2->left;
			}
		}
	}
	return temp2;
}


int clean_up_tree(tnode* tree) { //works
/* Frees every node of a given tree */
	if (tree == NULL) {
		return 0; }
	tnode *temp1, *temp2, *temp3, *temp4;
	temp1 = tree->up; temp2 = tree->left; temp3 = tree->down; temp4 = tree->right;
	if (tree->up != NULL) {
		tree->up->prev = NULL; tree->up = NULL; }
	clean_up_tree(temp1);

	if (tree->left != NULL) {
		tree->left->prev = NULL; tree->left = NULL; }
	clean_up_tree(temp2);

	if (tree->down != NULL) {
		tree->down->prev = NULL; tree->down = NULL; }
	clean_up_tree(temp3);

	if (tree->right != NULL) {
		tree->right->prev = NULL; tree->right = NULL; }
	clean_up_tree(temp4);

	free(tree);

	return 0;
}


int nr_of_leaves(tnode tree) { //works
/* Counts the number of leaves of a given tree */
	int output=0;
	if (tree.up != NULL) {
		output = output + nr_of_leaves(*tree.up); }
	if (tree.down != NULL) {
		output = output + nr_of_leaves(*tree.down); }
	if (tree.left != NULL) {
		output = output + nr_of_leaves(*tree.left); }
	if (tree.right != NULL) {
		output = output + nr_of_leaves(*tree.right); }
    if ((tree.up == NULL) && (tree.down == NULL) && (tree.left == NULL) && (tree.right == NULL)) {
        output = output + 1; }
    return output;
}

int endpoint_depth(tnode endpoint) { //works
/* Calculates the depth of a given node of a tree */
	tnode *temp = endpoint.prev;
	int output = 0;
	while (true) {
		if (temp != NULL) {
            output = output + 1;
            temp = temp->prev;
        }
        else {
            break; }
	}
	return output;
}

char* string_from_endpoint(tnode *endpoint, int depth) { //works
/* Finds the string of values "up,left,right,down" associated to the walk indicated by "endpoint" */
	tnode* temp = endpoint;
	int counter = 0;
	if (depth == 0) {
		return NULL; }
	char *output = (char*)malloc(depth*sizeof(char));
	while (temp->prev != NULL) {
		if (temp->prev->up == temp) {
			output[depth - 1 - counter] = 'u'; }
		if (temp->prev->right == temp) {
			output[depth - 1 - counter] = 'r'; }
		if (temp->prev->down == temp) {
			output[depth - 1 - counter] = 'd'; }
		if (temp->prev->left == temp) {
			output[depth - 1 - counter] = 'l'; }
		counter = counter + 1;
		temp = temp->prev;
	}

	return output;
}

void tree_adder(int i, int N, bool **occ, int path_x[], int path_y[], tnode*** endpoints, tnode* tree, long long &counter, int length);

tnode* tree_of_walks(int N, node *walk, tnode*** endpoints) { //probably works
/* Determines the tree of walks of length N starting with "walk" */

	int i=0, length = walk_length(*walk);
	long long counter = 0;
	long long nr_of_walks = pathSAW(walk,N);
	*endpoints = (tnode**)malloc(sizeof(tnode*)*nr_of_walks);

	int path_x[N], path_y[N];
	bool **occ = matallocb(2*N+1,2*N+1);

	tnode* output = (tnode*)malloc(sizeof(tnode));
	output->prev = NULL;
	output->up = NULL; output->right = NULL; output->down = NULL; output->left = NULL;



/* Check for empty and very long walks */
	if (length < 0) {
		cout << "Can not count the number of walks without a specified starting point.\n";
		return NULL;
		}
	if (length > N) {
		return output; }

/* Clear pre-existing paths */
	clear_path(occ,path_x,path_y,N);

/* Set up the path specified by walk */
	node *temp = walk;
	for (i=0; i < length; i++) {
		path_x[i] = N + temp->xcoord; path_y[i] = N + temp->ycoord;
			/* Lattice has offset -N,-N, so the origin is (N,N) */
		occ[path_x[i]][path_y[i]] = true;
		temp = temp->nextptr;
	}
	path_x[length] = temp->xcoord + N; path_y[length] = temp->ycoord + N;

/* Apply tree_adder */
	tree_adder(length,N,occ,path_x,path_y,endpoints,output,counter,length);

/* Output and clean-up */
	matfreeb(occ);

	return output;
}

void tree_adder(int i, int N, bool **occ, int path_x[], int path_y[], tnode*** endpoints, tnode* tree, long long &counter, int length)
{ //probably works
	if (!occ[path_x[i]][path_y[i]]){
		if (i==N){
			(*endpoints)[counter] = addwalk(path_x,path_y,N,length,tree);
			counter++;
		}
		else{
		/* Try all paths starting at (path_x[i],path_y[i]) */
			occ[path_x[i]][path_y[i]]=true;
			path_x[i+1]=path_x[i]+1; path_y[i+1]=path_y[i];
			tree_adder(i+1,N,occ,path_x,path_y,endpoints,tree,counter,length);

			path_x[i+1]=path_x[i]-1; path_y[i+1]=path_y[i];
			tree_adder(i+1,N,occ,path_x,path_y,endpoints,tree,counter,length);

			path_x[i+1]=path_x[i]; path_y[i+1]=path_y[i]+1;
			tree_adder(i+1,N,occ,path_x,path_y,endpoints,tree,counter,length);

			path_x[i+1]=path_x[i]; path_y[i+1]=path_y[i]-1;
			tree_adder(i+1,N,occ,path_x,path_y,endpoints,tree,counter,length);

			occ[path_x[i]][path_y[i]]=false;
		}
	}
}


