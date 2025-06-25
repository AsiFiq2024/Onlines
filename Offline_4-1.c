#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void neg_rem(int* input,int n,int** output, int* new_size){
    int j = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", input+i);
        if(*(input+i) >= 0){
            *(*output+j) = *(input+i);
            j++;
        }
    }
    *new_size = j;
}

int main(){
    int n;
    scanf("%i",&n);

    int *a = (int *)malloc(n * sizeof(int));
    assert(a != NULL);
    int *b = (int *)malloc(n * sizeof(int));
    assert(b != NULL);
    int new_n;
    neg_rem(a,n,&b,&new_n);
    printf("%d\n",new_n);
    for(int i = 0; i < new_n; i++){
        printf("%d ",*(b+i));
    }
    free(a);
    free(b);
}
