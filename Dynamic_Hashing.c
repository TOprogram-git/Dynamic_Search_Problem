#include <stdio.h>

#define m 27

int htb[m];
int flag[m];

int hash(int x) //ハッシュ値を求める
{
    x = x%m;
    return x;
}

void HashMethod(int x) //ハッシュ法でデータを配列:htb[]に挿入
{
    int j;
    j = hash(x);
    while(htb[j] != 0) j = (j+1)%m;
    flag[j] = 1;
    htb[j] = x;
}

void InitHash() //ハッシュ表の初期化
{
    for(int i=0; i<m; i++){
        htb[i]=0;
        flag[i]=0;
    }
}

void print_HashTable() //ハッシュ表の表示
{
    int i;
    printf("ハッシュ表\n");
    for(i=0; i<m-1; i++) printf("%2d,",htb[i]);
    printf("%2d\n",htb[i]);
    for(i=0; i<m-1; i++) printf("%2d,",flag[i]);
    printf("%2d\n",flag[i]);
}

int Search(int x) //探索
{
    int j;
    j = hash(x);
    while(flag[j] != 0 && htb[j] != x) j = j%m;
    if(x == htb[j]) return j;
    return -1;
}

int Delete_Hash(int x) //削除
{
    int j;
    j = Search(x);
    if(j == -1) return -1;
    htb[j] = 0;
    return j;
}

void Re_Hash(){
    int s[m];
    for(int i=0; i<m; i++) s[i]=0;
    for(int i=0,j=0; i<m; i++){
        if(htb[i] != 0){ 
            s[j] = htb[i];
            j++;
        }
    }
    InitHash();
    for(int i=0;i<m;i++){
        if(s[i] == 0) break;
        HashMethod(s[i]);
    }
    printf("Re_Hash\n");
}

int main(){
    int x,i,j;
    
    InitHash();
    print_HashTable();
    do{
        printf("終了(0),挿入(1),探索(2),削除(3)：");
        scanf("%d",&i);
        switch(i){
            case 0:
                break;
            case 1:
                printf("挿入する値の入力：");
                scanf("%d",&x);
                HashMethod(x);
                print_HashTable();
                break;
            case 2:
                printf("探索する値の入力：");
                scanf("%d",&x);
                j = Search(x);
                if(j == -1) printf("%dはありません\n",x);
                else printf("%d番目に%dを発見\n",j+1,x);
                print_HashTable();
                break;
            case 3:
                printf("削除する値の入力：");
                scanf("%d",&x);
                j = Delete_Hash(x);
                if(j == -1) printf("%dはありません\n",x);
                else printf("%d番目の%dを削除\n",j+1,x);
                print_HashTable();
                Re_Hash();
                print_HashTable();
                break;
            default:
                printf("値が間違っています。もう一度入力してください\n");
                print_HashTable();
                break;
        }
    }while(i != 0);
    return 0;
}
