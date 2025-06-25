#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int comp_letter(char* a, char* b){
    while(*a && *b){
        if(*a != *b)
            return *a-*b;
        a++;
        b++;
    }
    return *a-*b;
}

int main(){
    int n;
    scanf("%d",&n);
    char **word = (char**)malloc(n*sizeof(char *));

    for(int i = 0; i < n; i++){
        *(word + i) = (char *)malloc(26*sizeof(char));
        scanf("%25s",*(word+i));
    }

    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(comp_letter(*(word+j),*(word+j+1)) > 0){
                char* temp = *(word+j);
                *(word+j) = *(word+j+1);
                *(word+j+1) = temp;
            }
        }
    }

    for(int i = 0; i < n; i++){
        printf("%s\n",*(word+i));
    }

    for (int i = 0; i < n; i++) {
        free(*(word+i));
    }
    free(word);
}
