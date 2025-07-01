#include <stdio.h>
#include <stdlib.h>

int main(){
    char *input = (char *)malloc(101*sizeof(char));
    scanf("%s",input);
    int n = 1;
    while(*(input+n) != '\0'){
        n++;
    }
    int n2 = n;
    char temp;
    for(int i = 0; i < n; i++){
        if(*(input+i) == 'a'||*(input+i) == 'e'||*(input+i) == 'i'||*(input+i) == 'o'||*(input+i) == 'u'){
            for(int j = n-1; j > i; j--){
                if(*(input+j) == 'a'||*(input+j) == 'e'||*(input+j) == 'i'||*(input+j) == 'o'||*(input+j) == 'u'){
                    temp = *(input+j);
                    *(input+j) = *(input+i);
                    *(input+i) = temp;
                    n = j;
                    break;
                }
            }
        }
    }
    printf("%s",input);
    printf("\n");
    if(*(input) == 'a'||*(input) == 'e'||*(input) == 'i'||*(input) == 'o'||*(input) == 'u'){
        temp = *input;
        for(int i = 1; i < n2; i++){
            *(input+i-1) = *(input+i);
        }
        *(input+n2-1) = temp;
    }
    printf("%s",input);
    free(input);
}
