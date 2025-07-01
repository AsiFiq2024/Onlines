#include <stdio.h>
#include <stdlib.h>

int pow(int a, int b){
    int rslt = 1;
    for(int i = 0; i < b; i++){
        rslt *= a;
    }
    return rslt;
}

int bin_dec(int n){
    int d_num = 0;
    int i = 0;
    while(n > 0){
        d_num += (n%10)*pow(2,i);
        i++;
        n /= 10;
    }
    return d_num;
}

int main(){
    char *str = (char *)malloc(101*sizeof(char));
    scanf("%s",str);
    int ans = 0;
    for(int i = 0;*(str+i)!='\0'; i+=4){
        int num = 0;
        for(int j = i; j < i+4;j++){
            num = num*10 + *(str+j)-'0';
        }
        ans = ans*10 + bin_dec(num);
    }
    printf("%d",ans);
    free(str);
}
