#ifndef BST_H
#define BST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct index_name {
	char *key;
	int index;
} index_name;

typedef struct node_bst {
	index_name *data;
	struct node_bst *left;
	struct node_bst *right;
} node_bst;
typedef node_bst * bst;

node_bst *create_node_bst_bst(index_name *data) {
	node_bst *new_node_bst = (node_bst*) malloc(sizeof(node_bst));
	new_node_bst->data = data;
	new_node_bst->left = NULL;
	new_node_bst->right = NULL;
	return new_node_bst;
}

node_bst *min_value_bst(node_bst *root) {
	node_bst *current = root;

	while(current && current->left != NULL){
		current = current->left;
	}
	return current;
}
	
node_bst *insert_bst (node_bst *root, index_name *data) {
	if (root == NULL){
		return create_node_bst_bst(data);
	}
	if (data->key[0] < root->data->key[0]) {
		root->left = insert_bst(root->left, data);
	} else {
		root->right = insert_bst(root->right, data);
	}
	return root;
}

node_bst *delete_bst(node_bst *root, char *name) {
	if(root == NULL) {
		puts("Disk name not found");
		return root;
	}
	if (name[0] < root->data->key[0]){
		root->left = delete_bst(root->left, name);
	}
	else if (name[0] > root->data->key[0]){
		root->right = delete_bst(root->right, name);
	} else {
		if (root->left == NULL){
			if(strcmp(root->data->key, name) == 10){
				node_bst *temp = root->right;
				free(root);
				puts("Disk deleted!");
				return temp;
			}
			return root;
		}
		else if (root->right == NULL){
			if(strcmp(root->data->key, name) == 10){
				node_bst *temp = root->left;
				free(root);
				puts("Disk deleted!");
				return temp;
			}
			return root;
		}
		node_bst *temp = min_value_bst(root->right);
		root->data = temp->data;
		root->right = delete_bst(root->right, name);
	}
	return root;
}

node_bst *search_bst(node_bst *bst, char *name){
	//printf("\nkey:%s\n", bst->data->key);
	
	if(bst == NULL || strcmp(bst->data->key, name) == 10 || strcmp(bst->data->key, name) == 0){
		return bst;
	}
	if(name[0] < bst->data->key[0]){
		return search_bst(bst->left, name);
	} else {
		return search_bst(bst->right, name);
	}
}

int greater(int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

int height(bst root) {
	if(root == NULL) {
		return 0;
	}
	return 1 + greater(height(root->right), height(root->left));
}


bst load_file_bst(char*, bst);

void save_file_bst(char *, bst);

void save_aux_bst(bst, FILE *);

int height(bst);

#endif
