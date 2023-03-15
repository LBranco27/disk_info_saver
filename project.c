#include <stdio.h>
#include <stdlib.h>
#include "function.c"

int main(){
	int choice = 0;
	char name[255];
	
	table_name tab;
	table_tags tab_avl;
	table_date tab_rb;
	initialize_table_bst(&tab);
	initialize_table_avl(&tab_avl);
	initialize_table_rb(&tab_rb);

	printf("\n\n----- DISK MANAGER 3000 -----\n");
								
	//printf("\nindex:= %d\n", tab.index->data->index);
	//printf("\nkey:= %s\n", tab.index->data->key);
	
	while(1){
		printf("\n1 - insert new disk data\n");
		printf("2 - view all disks data\n");
		printf("3 - search disk data\n");
		printf("4 - delete one disk data\n");
		printf("9 - save & quit\n");
		printf("choose one:");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				add_disk(&tab, read_data(), &tab_avl, &tab_rb);
				break;
			case 2:
				printf("\nchoose what index you want to sort\n");
				printf("1 - name\n");
				printf("2 - tags\n");
				printf("3 - date\n");
				printf("choose one:");
				choice = 0;
				scanf("%d", &choice);
				switch(choice){
					case 1:
						printf("\nchoose what type of sort you want\n");
						printf("1 - pre-order\n");
						printf("2 - in-order\n");
						printf("3 - pos-order\n");
						printf("choose one:");
						choice = 0;
						scanf("%d", &choice);
						switch(choice){
							case 1:
								printf("\nPre-order:\n");
								pre_order_bst(tab.index, &tab);
								printf("\n");
								break;
							case 2:
								printf("\nIn-order:\n");
								in_order_bst(tab.index, &tab);
								printf("\n");
								break;
							case 3:
								printf("\nPos-order:\n");
								pos_order_bst(tab.index, &tab);
								printf("\n");
								break;
							default:
								break;
						}
						break;
					case 2:
						printf("\nchoose what type of sort you want\n");
						printf("1 - pre-order\n");
						printf("2 - in-order\n");
						printf("3 - pos-order\n");
						printf("choose one:");
						choice = 0;
						scanf("%d", &choice);
						switch(choice){
							case 1:
								printf("\nPre-order:\n");
								pre_order_avl(tab_avl.index, &tab_avl, &tab);
								printf("\n");
								break;
							case 2:
								printf("\nIn-order:\n");
								in_order_avl(tab_avl.index, &tab_avl, &tab);
								printf("\n");
								break;
							case 3:
								printf("\nPos-order:\n");
								pos_order_avl(tab_avl.index, &tab_avl, &tab);
								printf("\n");
								break;
							default:
								break;
						}
						break;
					case 3:
						printf("\nchoose what type of sort you want\n");
						printf("1 - pre-order\n");
						printf("2 - in-order\n");
						printf("3 - pos-order\n");
						printf("choose one:");
						choice = 0;
						scanf("%d", &choice);
						switch(choice){
							case 1:
								printf("\nPre-order:\n");
								pre_order_rb(tab_rb.index, &tab_rb, &tab);
								printf("\n");
								break;
							case 2:
								printf("\nIn-order:\n");
								in_order_rb(tab_rb.index, &tab_rb, &tab);
								printf("\n");
								break;
							case 3:
								printf("\nPos-order:\n");
								pos_order_rb(tab_rb.index, &tab_rb, &tab);
								printf("\n");
								break;
							default:
								break;
						}
						break;
					default:
						break;
				}
				break;
			case 3:
				printf("\nchoose what index you want to search\n");
				printf("1 - name\n");
				printf("2 - tags\n");
				printf("3 - date\n");
				printf("choose one:");
				choice = 0;
				scanf("%d", &choice);
				switch(choice){
					case 1:
						scanf("%s", name);
						search_disk_bst(tab.index, name, &tab);
						break;
					case 2:
						scanf("%s", name);
						search_disk_avl(tab_avl.index, name ,&tab_avl, &tab);
						break;
					case 3:
						scanf("%s", name);
						search_disk_rb(tab_rb.index, name ,&tab_rb, &tab);
						break;
					default:
						break;
				}
			case 4:
				printf("Type the name of the disk to delete: ");
				scanf("%s", name);
				tab.index = remove_disk_bst(tab.index, name);
				tab_avl.index = remove_disk_avl(tab_avl.index, name);
				remove_disk_rb(tab_rb.index, name);
				break;
			case 11:
				height(tab.index);
				printf("\nTree height(BST):%d\n", height(tab.index));
				break;
			case 9:
				finish(&tab, &tab_avl, &tab_rb);
				exit(0);
			default:
				break;
		}
	}

	return 0;
}
