#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d",&n);
    int **a = (int **)malloc(n*sizeof(int *));
    for(int i = 0; i < n; i++){
        *(a+i) = (int *)malloc(n*sizeof(int));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d",(*(a+i)+j));
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ",*(*(a+i)+j));
        }
        printf("\n");
    }
    printf("\n");
    int **aT = (int **)malloc(n*sizeof(int *));
    for(int i = 0; i < n; i++){
        *(aT+i) = (int *)malloc(n*sizeof(int));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            *(*(aT+i)+j) = *(*(a+j)+i);
        }
    }
    int temp;
    for(int i = 0; i < n; i++){
        temp = *(*(aT+i)+n-1);
        *(*(aT+i)+n-1) = *(*(aT+i)+0);
        *(*(aT+i)+0) = temp;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ",*(*(aT+i)+j));
        }
        printf("\n");
    }
}
