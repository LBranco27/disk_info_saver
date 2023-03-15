#ifndef AVL_H
#define AVL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct index_tags{
	char key[128];
	int index;
} index_tags;

typedef struct node_avl {
	index_tags *data;
	struct node_avl *left;
	struct node_avl *right;
	int height;
} node_avl;
typedef node_avl * avl;

node_avl *create_node(index_tags *data){
	node_avl *new_node = (node_avl*) malloc(sizeof(node_avl));
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->height = 1;
	return new_node;
}

int max(int a, int b){
	if(a > b){
		return a;
	}
	return b;
}

int heightc(node_avl *node){
	if(node == NULL){
		return 0;
	}
	return node->height;
}

int balancen(node_avl *node){
	if(node == NULL){
		return 0;
	}
	return heightc(node->left) - heightc(node->right);
}

node_avl *rotate_right(node_avl *b){
	node_avl *a = b->left;
	node_avl *c = a->right;

	a->right = b;
	b->left = c;

	b->height = max(heightc(b->left), heightc(b->right)) + 1;
	a->height = max(heightc(a->left), heightc(a->right)) + 1;

	return a;
}

node_avl *rotate_left(node_avl *b){
	node_avl *a = b->right;
	node_avl *c = a->left;

	a->left = b;
	b->right = c;

	b->height = max(heightc(b->left), heightc(b->right)) + 1;
	a->height = max(heightc(a->left), heightc(a->right)) + 1;

	return a;
}

node_avl *min_value_avl(node_avl *root) {
	node_avl *current = root;

	while(current && current->left != NULL){
		current = current->left;
	}
	return current;
}

node_avl *insert_avl (node_avl *root, index_tags *data){
	if (root == NULL){
		return create_node(data);
	}
	if ( data->key[0] < root->data->key[0] ) {
		root->left = insert_avl(root->left, data);
	}
	else if ( data->key[0] < root->data->key[0] ) {
		root->right = insert_avl(root->right, data);
	}else{
		return root;
	}

	root->height = 1 + max(heightc(root->left), heightc(root->right));

	int balance = balancen(root);

	if (balance > 1 && data->key[0] < root->left->data->key[0] ) {
		return rotate_right(root);
	}

	if (balance < -1 && data->key[0] > root->right->data->key[0] ) {
		return rotate_left(root);
	}

	if (balance > 1 && data->key[0] > root->left->data->key[0]) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}

	if (balance < -1 && data->key[0] < root->right->data->key[0]) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}

	return root;
}

node_avl *delete_avl(node_avl *root, char *name){
	if(root == NULL) {
		puts("Disk name not found");
		return root;
	}
	if (name[0] < root->data->key[0]){
		root->left = delete_avl(root->left, name);
	}
	else if (name[0] > root->data->key[0]){
		root->right = delete_avl(root->right, name);
	} else {
		if (root->left == NULL){
			if(strcmp(root->data->key, name) == 10){
				node_avl *temp = root->right;
				free(root);
				puts("Disk deleted!");
				return temp;
			}
			return root;
		}
		else if (root->right == NULL){
			if(strcmp(root->data->key, name) == 10){
				node_avl *temp = root->left;
				free(root);
				puts("Disk deleted!");
				return temp;
			}
			return root;
		}
		node_avl *temp = min_value_avl(root->right);
		root->data = temp->data;
		root->right = delete_avl(root->right, name);
	}
	return root;
}

node_avl *search_avl(node_avl *avl, char *name){
	if(avl == NULL || strcmp(avl->data->key, name) == 10 || strcmp(avl->data->key, name) == 0) {
		return avl;
	}
	if(name[0] < avl->data->key[0]){
		return search_avl(avl->left, name);
	} else {
		return search_avl(avl->right, name);
	}
}

avl load_file_avl(char*, avl);

void save_file_avl(char*, avl);

void save_aux_avl(avl, FILE*);



#endif 
