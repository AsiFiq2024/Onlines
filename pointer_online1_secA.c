#include <stdio.h>
#include <stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    int **mat =(int **)malloc(n*sizeof(int*));
    for(int i = 0; i < n; i++){
        *(mat+i) = (int *)malloc(n*sizeof(int));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d",(*(mat + i) + j));
        }
    }
    int **mat2 =(int **)malloc(n*sizeof(int*));
    for(int i = 0; i < n; i++){
        *(mat2+i) = (int *)malloc(n*sizeof(int));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            *(*(mat2+j)+n-1-i) = *(*(mat+i)+j);
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            *(*(mat+i)+j) = *(*(mat2+i)+j);
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ",*(*(mat+i)+j));
        }
        printf("\n");
    }
}
