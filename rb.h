#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef RB_H
#define RB_H
#define RED 0
#define BLACK 1

typedef struct index_date{
	char key[32];
	int index;
} index_date;

typedef struct node_rb {
	index_date *data;
	int color;	
	struct node_rb *left; 
	struct node_rb *right; 
	struct node_rb *parent;
} node_rb;
typedef node_rb *rb;

node_rb *create_node_rb(index_date *data){
	node_rb *rb = (node_rb*) malloc(sizeof(node_rb));
    rb->data = (index_date*) malloc(sizeof(index_date));
    memcpy(rb->data, data, sizeof(index_date));
	rb->color = RED;
	rb->left = NULL;
	rb->right = NULL;
	rb->parent = NULL;
	return rb;
}

node_rb *root = NULL;

void left_rotate_rb(node_rb **root, node_rb *x) {
	node_rb *y = x->right;
	x->right = y->left;
	if (y->left != NULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL) {
		*root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void right_rotate_rb(node_rb **root, node_rb *x) {
	node_rb *y = x->left;
	x->left = y->right;
	if (y->right != NULL) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL) {
		*root = y;
	} else if (x == x->parent->right) {
		x->parent->right = y;
	} else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}


node_rb *search_rb(node_rb *root, char *key) {
		puts("rodou");
		//printf("strcmp:%d\n", strcmp(root->data->key, key));
	if (root == NULL || strcmp(root->data->key, key) == 0 || strcmp(root->data->key, key) == 10) {
		puts("retornou");
		return root;
	}
	if (strcmp(root->data->key, key) > 0) {
		return search_rb(root->left, key);
	} else {
		return search_rb(root->right, key);
	}
}

node_rb* minimum_rb(node_rb* node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}

node_rb *successor_rb(node_rb *x) {
	node_rb *y;
	if (x->right != NULL) {
		return minimum_rb(x->right);
	}
	y = x->parent;
	while (y != NULL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

void insert_rb(node_rb **root, index_date *data) {
    //BST insert
    node_rb *z = create_node_rb(data);
    node_rb *y = NULL;
    node_rb *x = *root;
    while (x != NULL) {
        y = x;
        if (strcmp(z->data->key, x->data->key) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == NULL) {
        *root = z;
    } else if (strcmp(z->data->key, y->data->key) < 0) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    //fix
    while (z != *root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            node_rb *y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate_rb(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate_rb(root, z->parent->parent);
            }
        } else {
            node_rb *y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate_rb(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate_rb(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;  //root is black
}

void transplant_rb(node_rb **root, node_rb *u, node_rb *v) {
    if (u->parent == NULL) {
        *root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

void delete_fixup_rb(node_rb **root, node_rb *x) {
    node_rb *w;
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate_rb(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate_rb(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate_rb(root, x->parent);
                x = *root;
            }
        } else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate_rb(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate_rb(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate_rb(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

void delete_rb(node_rb **root, char *key) {
    node_rb *z = search_rb(*root, key);
    if (z == NULL) {
        return;
    }
    node_rb *x;
    node_rb *y = z;
    int y_original_color = y->color;
    if (z->left == NULL) {
        x = z->right;
        transplant_rb(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant_rb(root, z, z->left);
    } else {
        y = minimum_rb(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) {
                x->parent = y;
            }
        } else {
            transplant_rb(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant_rb(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z->data);
    free(z);
    if (y_original_color == BLACK) {
		if(x != NULL){
		        delete_fixup_rb(root, x);
		}
    }
}







rb load_file_rb(char*, rb);

void save_file_rb(char*, rb);

void save_aux_rb(rb, FILE*);

#endif 
