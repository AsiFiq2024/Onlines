#include <stdio.h>

int main(){
    int rows;
    int dig;
    int total_lev = 0;
    scanf("%d",&rows);
    for(int i = 1; i <= rows; i++){
        int k;
        scanf("%d",&k);
        int cond_count = 0;
        int level = 0;
        int sum = 0;
        int alt_sum = 0;
        int odd_sum = 0;
        int even_sum = 0;
        for(int j = 0; j < k; j++){
            scanf("%d",&dig);
            sum = sum + dig;
            if(j%2 != 0){
                alt_sum = alt_sum - dig;
                even_sum = even_sum + dig;
            }
            else{
                alt_sum = alt_sum + dig;
                odd_sum = odd_sum + dig;
            }
        }
        printf("Row %d: ",i);
        if(sum > 1){
            int check_prime = 0;
            for(int l = 2; l < sum; l++){
                if(sum % l == 0){
                    check_prime++;
                }
            }
            if(check_prime == 0){
                level = level + 5;
                cond_count = 1;
            }
        }
        if(sum > 9){
            int temp = sum;
            int rev_dig = 0;
            while(temp > 0){
                rev_dig = rev_dig + (temp % 10);
                rev_dig = rev_dig*10;
                temp /= 10;
            }
            rev_dig /= 10;
            if(sum == rev_dig){
                level = level + 3;
                cond_count = 1;
            }
        }
        else{
            level = level + 3;
            cond_count = 1;
        }
        if(alt_sum % 7 == 0){
            level = level + 4;
            cond_count++;
        }
        if(odd_sum == even_sum){
            level = level + 2;
            cond_count++;
        }
        total_lev = total_lev + level;
        switch(cond_count){
            case 0: printf("INACTIVE - ");
                    break;
            case 1: printf("LOW - ");
                    break;
            case 2: printf("MEDIUM - ");
                    break;
            case 3: printf("HIGH - ");
                    break;
        }
        printf("Energy Level %d\n",level);
    }
    printf("\nTotal Energy: %d",total_lev);
    return 0;
}
