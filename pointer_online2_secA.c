#include <stdio.h>
#include <stdlib.h>

void decomp(char *input,char **output){
    char * p = input;
    int len = 0;
    while(*p != '\0'){
        char ch = *p++;
        int count = 0;
        while(*p >= '0' && *p <= '9'){
            count = count*10 + *p-'0';
            p++;
        }
        len += count;
    }
    *output = (char *)malloc((len+1)*sizeof(char));
    int i = 0;
    p = input;
    while(*p != '\0'){
        char ch = *p++;
        int count = 0;
        while(*p >= '0' && *p <= '9'){
            count = count*10 + *p-'0';
            p++;
        }
        int i2 = 0;
        while(i2 < count){
            *(*output+i) = ch;
            i2++;
            i++;
        }
    }
    *(*output+i) = '\0';
}

int main(){
    char enc[101];
    scanf("%s",enc);
    char *out;
    decomp(enc,&out);
    printf("%s",out);
    free(out);
}
