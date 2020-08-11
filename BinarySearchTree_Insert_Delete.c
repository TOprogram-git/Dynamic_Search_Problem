#include <stdio.h>
#include <stdlib.h>

int n = 10;
int a[10] = {57,22,80,14,34,71,87,4,17,59};

typedef struct BSTnode{
    int key;
    struct BSTnode *lson,*rson;
}tree_node;

tree_node *root = NULL;

tree_node* create_new_node(int x){
    tree_node *tree_new;
    
    tree_new = (tree_node*)malloc(sizeof(tree_node));
    if(tree_new == NULL){
        exit(EXIT_FAILURE);
    }
    tree_new->lson = NULL;
    tree_new->rson = NULL;
    tree_new->key = x;
    
    return tree_new;
}

void Insert_tree(int x,tree_node *node){
    if(node == NULL){
        root = create_new_node(x);
        return;
    }
    if(node->key > x){
        if(node->lson != NULL) Insert_tree(x, node->lson);
        else node->lson = create_new_node(x);
    }
    else{
        if(node->rson != NULL) Insert_tree(x, node->rson);
        else node->rson = create_new_node(x);
    }
    return;
}

void print_tree(int depth, tree_node* node){
    if(node == NULL) return;
    print_tree(depth+1, node->lson);
    for(int i=0; i<depth; i++){
        printf(" ");   
    }
    printf("%d\n",node->key);
    print_tree(depth+1, node->rson);
}

void free_tree(tree_node* node){
    if(node == NULL) return;
    free_tree(node->lson);
    free_tree(node->rson);
    free(node);
}

void Delete_tree(int x){
    tree_node *u,*p,*left_biggest;
    int direction=0;
    u = root;
    p = NULL;
    while(u != NULL && u->key != x){
        if(u->key > x){
            p = u;
            u = u->lson;
            direction = -1;
        }
        else{
            p = u;
            u = u->rson;
            direction = 1;
        }
    }
    if(u == NULL){
        printf("%dはありません\n",x);
        return;
    }
    
    if(u->lson == NULL || u->rson == NULL){
        if(u->lson == NULL){
            if(direction == -1) p->lson = u->rson;
            if(direction == 1) p->rson = u->rson;
            if(direction == 0) root = u->rson;
        }
        else{
            if(direction == -1) p->lson = u->lson;
            if(direction == 1) p->rson = u->lson;
            if(direction == 0) root = u->lson;
        }
        free_tree(u);
    }
    else{
        left_biggest = u->lson;
        p = u;
        direction = -1;
        while(left_biggest->rson != NULL){
            p = left_biggest;
            left_biggest = left_biggest->rson;
            direction = 1;
        }
        
        u->key = left_biggest->key;
        if(direction == -1) p->lson = left_biggest->lson;
        else p->rson = left_biggest->lson;
        free(left_biggest);
    }
    printf("%dを削除しました\n",x);
    return;
}

int main(void){
    int x,j;
    for(int i=0; i<n; i++){
        Insert_tree(a[i],root);
    }
    print_tree(0,root);
    printf("\n");
    do{
        printf("終了(0),挿入(1),削除(2)：");
        scanf("%d",&j);
        switch(j){
            case 1:
                printf("値の入力：");
                scanf("%d",&x);
                Insert_tree(x,root);
                print_tree(0,root);
                printf("\n");
                break;
            case 2:
                printf("削除する値を入力:");
                scanf("%d",&x);
                Delete_tree(x);
                print_tree(0,root);
                printf("\n");
                break;
        }
    }while(j != 0);
}
