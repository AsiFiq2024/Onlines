#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Array size: ");
    scanf("%d",&n);
    int *arr1 = (int*)malloc(n*sizeof(int));
    printf("Elements: ");
    for(int i = 0; i < n; i++){
        scanf("%d",arr1+i);
    }
    int a,b;
    printf("Pair: ");
    scanf("%d%d",&a,&b);
    int *arr2 = (int*)malloc((n+abs(b)-1)*sizeof(int));
    if(b > 0){
        for(int i = 0; i < n; i++){
            if(i == a){
                for(int j = 0; j < abs(b);j++){
                    *arr2 = *(arr1+a);
                    arr2++;
                }
            }
            else{
                *arr2 = *(arr1+i);
                arr2++;
            }
        }
    }
    else if(b == 0){
        for(int i = 0; i < n; i++){
            if(i != a){
                *arr2 = *(arr1+i);
                arr2++;
            }
        }
    }
    else{
        for(int j = 0; j < abs(b);j++){
            *arr2 = *(arr1+a);
            arr2++;
        }
        for(int i = a+1; i < n;i++){
            *arr2 = *(arr1+i);
            arr2++;
        }
        for(int i = 0;i < a; i++){
            *arr2 = *(arr1+i);
            arr2++;
        }
    }
    arr2 -= n+abs(b)-1;
    for(int i = 0; i < n+abs(b)-1;i++){
        printf("%d ",*(arr2+i));
    }
    free(arr1);
    free(arr2);
}
