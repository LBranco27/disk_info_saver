#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "avl.h"
#include "rb.h"
#include "function.h"

typedef struct table_name{
	FILE *file;
	bst index;
} table_name;

typedef struct table_tags{
	FILE *file;
	avl index;
} table_tags;

typedef struct table_date{
	FILE *file;
	rb index;
} table_date;

void initialize_bst(bst *root){
	*root = NULL;
}
void initialize_avl(avl *root){
	*root = NULL;
}
void initialize_rb(rb *root){
	*root = NULL;
}
//
//
disk *print_tree_bst(bst, table_name*);
void print_tree_avl(avl, table_name*);
void print_tree_rb(rb, table_name*);
//
//

int initialize_table_bst(table_name *tab){
	initialize_bst(&tab->index);
	tab->file = fopen("d_bst.dat", "a+b");
	tab->index = load_file_bst("index_bst.dat", tab->index);
	//printf("\nindex-iniciio:= %d\n", tab->index->data->index);
	//printf("\nkey:= %s\n", tab->index->data->key);
	
	if(tab->file != NULL){
		return 1;
	}
	else{
		return 0;
	}
}
int initialize_table_avl (table_tags *tab) {
	initialize_avl(&tab->index);
	tab->file = NULL;
	tab->index = load_file_avl("index_avl.dat", tab->index);
	
	if(tab->file != NULL){
		return 1;
	}
	else{
		return 0;
	}
}
int initialize_table_rb (table_date *tab) {
	initialize_rb(&tab->index);
	tab->file = NULL;
	tab->index = load_file_rb("index_rb.dat", tab->index);
	
	if(tab->file != NULL){
		return 1;
	}
	else{
		return 0;
	}
}

void finish (table_name *tab, table_tags *tab_avl, table_date *tab_rb){
	fclose(tab->file);
	save_file_bst("index_bst.dat", tab->index);
	save_file_avl("index_avl.dat", tab_avl->index);
	save_file_rb("index_rb.dat", tab_rb->index);
}

void save_file_bst(char *name, bst a){
	FILE *file;
	file = fopen(name,"wb");
	if(file != NULL) {
		save_aux_bst(a, file);
		fclose(file);
	}
}
void save_file_avl(char *name, avl a){
	FILE *file;
	file = fopen(name,"wb");
	if(file != NULL) {
		save_aux_avl(a, file);
		fclose(file);
	}
}
void save_file_rb(char *name, rb a){
	FILE *file;
	file = fopen(name,"wb");
	if(file != NULL) {
		save_aux_rb(a, file);
		fclose(file);
	}
}

void save_aux_bst(bst root, FILE *file){
	if(root != NULL){
		//printf("\nstrlenkey:%d\n", strlen(root->data->key));
		//printf("\nescritoskey: %d\n", fwrite(root->data->key, sizeof(char), strlen(root->data->key), file));
		//printf("\nescritosindex: %d\n", fwrite(&root->data->index, sizeof(root->data->index), 1, file));
		fwrite(root->data->key, sizeof(char), strlen(root->data->key), file);
		fwrite("\0", sizeof(char), 1, file);
		fwrite(&root->data->index, sizeof(root->data->index), 1, file);
		save_aux_bst(root->left, file);
		save_aux_bst(root->right, file);
	}
}
void save_aux_avl(avl root, FILE *file){
	if(root != NULL){
		fwrite(root->data, sizeof(index_tags), 1, file);
		save_aux_avl(root->left, file);
		save_aux_avl(root->right, file);
	}
}
void save_aux_rb(rb root, FILE *file){
	if(root != NULL){
		fwrite(root->data, sizeof(index_date), 1, file);
		save_aux_rb(root->left, file);
		save_aux_rb(root->right, file);
	}
}


bst load_file_bst (char *name, bst a) {
	FILE *file;
	file = fopen(name, "rb");
	index_name *temp;
	if(file != NULL){
		temp = (index_name*) malloc(sizeof(index_name));
		char *name = (char*) malloc(sizeof(char)*300);
		while(1) {
			for(int i = 0; i<300; i++){
				if((name[i] = fgetc(file)) == '\0' || name[i] == -1){
					if(name[i] == -1){
						free(name);
						free(temp);
						fclose(file);
						return a;
					}
					//if(name[i] == '\0'){
					//	puts("ASDOSADOASDA");
					//}
					break;
				}
			}
			temp->key = name;
			//printf("\ntemp.key = %s", temp->key);
			fread(&temp->index, sizeof(int), 1, file);
			//printf("\ntemp.index = %d", temp->index);
			a = insert_bst(a, temp);
			name = (char*) malloc(sizeof(char)*300);
			temp = (index_name*) malloc(sizeof(index_name));
		}
		free(name);
		fclose(file);
	}
	return a;
}
avl load_file_avl (char *name, avl a) {
	FILE *file;
	file = fopen(name, "rb");
	index_tags *temp;
	if(file != NULL){
		temp = (index_tags*) malloc(sizeof(index_tags));
		while(fread(temp, sizeof(index_tags), 1, file)) {
			//puts("inserted");
			a = insert_avl(a, temp);
			temp = (index_tags*) malloc(sizeof(index_tags));
		}
		fclose(file);
	}
	return a;
}
rb load_file_rb (char *name, rb a) {
	FILE *file;
	file = fopen(name, "rb");
	index_date *temp;
	if(file != NULL){
		temp = (index_date*) malloc(sizeof(index_date));
		while(fread(temp, sizeof(index_date), 1, file)) {
			insert_rb(&a, temp);
			temp = (index_date*) malloc(sizeof(index_date));
		}
		fclose(file);
	}
	return a;
}

void add_disk(table_name *tab, disk *disk, table_tags *tab_avl, table_date *tab_rb){
	int pos_new_register;
	if(tab->file != NULL) {
		fseek(tab->file, 0L, SEEK_END);
		pos_new_register = ftell(tab->file);

		index_name *new = (index_name*) malloc(sizeof(index_name));
		index_tags *new_avl = (index_tags*) malloc(sizeof(index_tags));
		index_date *new_rb = (index_date*) malloc(sizeof(index_date));
		//new->key = (char*) malloc(sizeof(strlen(disk->name)));
		//strcpy(new->key, disk->name);
		new->key = disk->name;
		new->index = pos_new_register;
		tab->index = insert_bst(tab->index, new);

		strcpy(new_avl->key, disk->tags);
		new_avl->index = pos_new_register;
		tab_avl->index = insert_avl(tab_avl->index, new_avl);
	
		strcpy(new_rb->key, disk->date);
		new_rb->index = pos_new_register;
		insert_rb(&tab_rb->index, new_rb);
	
		fwrite(disk->name, sizeof(char), strlen(disk->name), tab->file);
		//printf("%ld",);
		fwrite("\0", sizeof(char), 1,tab->file);
		fwrite(disk->content, sizeof(disk->content), 1, tab->file);
		fwrite(disk->date, sizeof(disk->date), 1, tab->file);
		fwrite(disk->tags, sizeof(disk->tags), 1, tab->file);
		fwrite(disk->extra, sizeof(disk->extra), 1, tab->file);

		
	}
}

bst remove_disk_bst(bst root, char *name){
	return delete_bst(root, name);
}
avl remove_disk_avl(avl root, char *name){
	return delete_avl(root, name);
}
void remove_disk_rb(rb *root, char *name){
	delete_rb(root, name);
}

disk *search_disk_bst(bst root, char *name, table_name *tab){
	bst temp = search_bst(root, name);
	if(temp != NULL){
		return print_tree_bst(temp, tab);
	} else {
		printf("\nNome not found!\n");
		return NULL;
	}
}
void search_disk_avl(avl root, char *name, table_tags *tab, table_name *tab_n){
	avl temp = search_avl(root, name);
	if(temp != NULL){
		print_tree_avl(temp, tab_n);
	} else {
		printf("\nTags not found!\n");
	}
} 
void search_disk_rb(rb root, char *name, table_date *tab, table_name *tab_n){
	if(root == NULL){
		return;
	}
	rb temp = search_rb(root, name);
	if(temp != NULL){
	puts("print_tree_rb");
		print_tree_rb(temp, tab_n);
	} else {
		printf("\nDate not found!\n");
	}
}

char *end (char *string){
	string[strlen(string)] = '\0';
	string[strlen(string)-1] = '\n';

	return string;
}

disk *read_data(){
	disk *new = (disk*) malloc(sizeof(disk));
	char *buffer = (char*) malloc(256 * sizeof(char));
	
	getchar();
	printf("Type the disk's name: ");
	fgets(buffer, 254, stdin);
	buffer = end(buffer);
	new->name = strdup(buffer);

	printf("Type the disk's content: ");
	fgets(new->content, 256, stdin);
	printf("Type the disk's date: ");
	fgets(new->date, 32, stdin);
	printf("Type the disk's tags (separate with comma (,)): ");
	fgets(new->tags, 128, stdin);
	printf("Type the disk's extra: ");
	fgets(new->extra, 128, stdin);

	//teste
	printf("\n-----------\n%s\n%s\n%s\n%s\n%s----------\n", new->name, new->content, new->date, new->tags, new->extra);
	free(buffer);
	return new;
}
// TREE - TREE - TREE - TREE -

disk *print_tree_bst(bst root, table_name *tab) {
	char *name = (char*) malloc(sizeof(char)*300);
	disk *temp = (disk*) malloc(sizeof(disk));
	fseek(tab->file, root->data->index, SEEK_SET);
	//fseek(tab->file, 0, SEEK_SET);
	for(int i = 0; i<300; i++){
		if((name[i] = fgetc(tab->file)) == '\0' || name[i] == -1){
			//if(name[i+1] == '\0'){
			//	puts("andoandsodoandoadosadsa");
			//}
			break;
		}
	}
	temp->name = name;
	//printf("\nname:=%s\n", name);
	fread(temp->content, sizeof(temp->content), 1, tab->file);
	fread(temp->date, sizeof(temp->date), 1, tab->file);
	fread(temp->tags, sizeof(temp->tags), 1, tab->file);
	fread(temp->extra, sizeof(temp->extra), 1, tab->file);
	printf("\n[name: %s content: %s date: %s tags: %s extra: %s]\n", temp->name, temp->content, temp->date, temp->tags, temp->extra);
	return temp;
	free(name);
}
void print_tree_avl(avl root, table_name *tab) {
	char *name = (char*) malloc(sizeof(char)*300);
	disk *temp = (disk*) malloc(sizeof(disk));
	//puts("printed");
	fseek(tab->file, root->data->index, SEEK_SET);
	for(int i = 0; i<300; i++){
		if((name[i] = fgetc(tab->file)) == '\0' || name[i] == -1){
			//if(name[i+1] == '\0'){
			//	puts("andoandsodoandoadosadsa");
			//}
			break;
		}
	}
	temp->name = name;
	//printf("\nname:=%s\n", name);
	fread(temp->content, sizeof(temp->content), 1, tab->file);
	fread(temp->date, sizeof(temp->date), 1, tab->file);
	fread(temp->tags, sizeof(temp->tags), 1, tab->file);
	fread(temp->extra, sizeof(temp->extra), 1, tab->file);
	printf("\n[name: %s content: %s date: %s tags: %s extra: %s]\n", temp->name, temp->content, temp->date, temp->tags, temp->extra);
	free(temp);
	free(name);
}
void print_tree_rb(rb root, table_name *tab) {
	char *name = (char*) malloc(sizeof(char)*300);
	disk *temp = (disk*) malloc(sizeof(disk));
	if (root == NULL) {
		free(temp);
		free(name);
		puts("Empty tree!");
		return;
	}
	//printf("root->data->index:%s\n", root->data->key);
	fseek(tab->file, root->data->index, SEEK_SET);
	//fseek(tab->file, 0, SEEK_SET);
	for(int i = 0; i<300; i++){
		if((name[i] = fgetc(tab->file)) == '\0' || name[i] == -1){
			//if(name[i+1] == '\0'){
			//	puts("andoandsodoandoadosadsa");
			//}
			break;
		}
	}
	temp->name = name;
	fread(temp->content, sizeof(temp->content), 1, tab->file);
	fread(temp->date, sizeof(temp->date), 1, tab->file);
	fread(temp->tags, sizeof(temp->tags), 1, tab->file);
	fread(temp->extra, sizeof(temp->extra), 1, tab->file);
	printf("\n[name: %s content: %s date: %s tags: %s extra: %s]\n", temp->name, temp->content, temp->date, temp->tags, temp->extra);
	free(temp);
	free(name);
}

void pre_order_bst(bst root, table_name *tab) {
	if(root != NULL){
		//printf("\nindex na preorder_bst:= %d\n", root->data->index);
		print_tree_bst(root, tab);
		pre_order_bst(root->left, tab);
		pre_order_bst(root->right, tab);
	}
}
void in_order_bst(bst root, table_name *tab) {
	if(root != NULL){
		in_order_bst(root->left, tab);
		print_tree_bst(root, tab);
		in_order_bst(root->right, tab);
	}
}
void pos_order_bst(bst root, table_name *tab) {
	if(root != NULL){
		pos_order_bst(root->left, tab);
		pos_order_bst(root->right, tab);
		print_tree_bst(root, tab);
	}
}

void pre_order_avl(avl root, table_tags *tab, table_name *tab_n) {
	if(root != NULL){
		print_tree_avl(root, tab_n);
		pre_order_avl(root->left, tab, tab_n);
		pre_order_avl(root->right, tab, tab_n);
	}
}
void in_order_avl(avl root, table_tags *tab, table_name *tab_n) {
	if(root != NULL){
		in_order_avl(root->left, tab, tab_n);
		print_tree_avl(root, tab_n);
		in_order_avl(root->right, tab, tab_n);
	}
}
void pos_order_avl(avl root, table_tags *tab, table_name *tab_n) {
	if(root != NULL){
		pos_order_avl(root->left, tab, tab_n);
		pos_order_avl(root->right, tab, tab_n);
		print_tree_avl(root, tab_n);
	}
}

void pre_order_rb(rb root, table_date *tab, table_name *tab_n) {
	if(root != NULL){
		print_tree_rb(root, tab_n);
		pre_order_rb(root->left, tab, tab_n);
		pre_order_rb(root->right, tab, tab_n);
	}
}
void in_order_rb(rb root, table_date *tab, table_name *tab_n) {
	if(root != NULL){
		in_order_rb(root->left, tab, tab_n);
		print_tree_rb(root, tab_n);
		in_order_rb(root->right, tab, tab_n);
	}
}
void pos_order_rb(rb root, table_date *tab, table_name *tab_n) {
	if(root != NULL){
		pos_order_rb(root->left, tab, tab_n);
		pos_order_rb(root->right, tab, tab_n);
		print_tree_rb(root, tab_n);
	}
}

// TREE - TREE - TREE - TREE -
