#include <stdio.h>
#include <math.h>
#include <string.h>
#define MAX_SIZE 100000
#define MAX_BINS 1000
#define MAX_STARS 50
#include <stdlib.h>
#include <time.h>
#define PI 3.14159265358979323846

// Function to generate a normally distributed random number
double generate_normal(double mu, double sigma) {
  double U1 = (double)rand() / (double)RAND_MAX;
  double U2 = (double)rand() / (double)RAND_MAX;
  double X1 = sqrt(-2 * log(U1)) * cos(2 * PI * U2);
  return mu + sigma * X1;
}

void populate_array_gaussian(double *array, int size, double mu, double sigma, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < size; i++) {
        array[i] = generate_normal(mu, sigma);
    }
}

void populate_array_uniform(double *array, int size, double min, double max, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < size; i++) {
        array[i] = min + (double)rand() / ((double)RAND_MAX / (max - min));
    }
}

int main()
{
    double array[MAX_SIZE];
    printf("Commands:\n\n  ");
    printf("set     - Set array size, seed, and distribution (uniform or gaussian)\n  ");
    printf("min     - Print minimum value\n  ");
    printf("max     - Print maximum value\n  ");
    printf("mean    - Print mean value\n  ");
    printf("stddev  - Print standard deviation\n  ");
    printf("hist    - Plot histogram\n  ");
    printf("summary - Print min, max, mean, stddev\n  ");
    printf("help    - Show this help message\n  ");
    printf("exit    - Exit the program\n");
    int set_count = 0;
    double min,max,mean,stddev;
    int size,bins;
    unsigned int seed;
    while(1)
    {
        printf("\nEnter command: ");
        char command[20];
        scanf("%s",command);
        if(strcmp(command,"set")==0){
            printf("Enter number of elements: ");
            scanf("%d",&size);
            printf("Enter seed: ");
            scanf("%u",&seed);
            char dis_com[20];
            printf("Distribution?(uniform or gaussian): ");
            scanf("%s",dis_com);
            if(strcmp(dis_com,"uniform")==0){
                double min1,max1;
                printf("Enter min and max: ");
                scanf("%lf%lf",&min1,&max1);
                populate_array_uniform(array,size,min1,max1,seed);
                printf("Array initialized with uniform distribution.\n");
                set_count++;
            }
            else if(strcmp(dis_com,"gaussian")==0){
                double mean1,stddev1;
                printf("Enter mean and stddev: ");
                scanf("%lf%lf",&mean1,&stddev1);
                populate_array_gaussian(array,size,mean1,stddev1,seed);
                printf("Array initialized with gaussian distribution.\n");
                set_count++;
            }
            else{
                printf("Invalid distribution\n");
            }
        }
        if(set_count){
            min = array[0];
            for(int i = 0; i < size; i++){
                if(min > array[i])
                    min = array[i];
            }
            max = array[0];
            for(int i = 0; i < size; i++){
                if(max < array[i])
                    max = array[i];
            }
            double sum = 0;
            for(int i = 0; i < size; i++){
                sum = sum + array[i];
            }
            mean = sum / size;
            double sum_dev = 0;
            for(int i = 0; i < size; i++){
                sum_dev = sum_dev + (mean - array[i])*(mean - array[i]);
            }
            stddev = sqrt(sum_dev/size);
        }
        if(strcmp(command,"min")==0){
            if(set_count != 0)
                printf("%0.4lf\n",min);
            else{
                printf("Array not initialized. Use 'set' command first\n");
            }
        }
        else if(strcmp(command,"max")==0){
            if(set_count != 0)
                printf("%0.4lf\n",max);
            else{
                printf("Array not initialized. Use 'set' command first\n");
            }
        }
        else if(strcmp(command,"mean")==0){
            if(set_count != 0)
                printf("%0.4lf\n",mean);
            else{
                printf("Array not initialized. Use 'set' command first\n");
            }
        }
        else if(strcmp(command,"stddev")==0){
            if(set_count != 0)
                printf("%0.4lf\n",stddev);
            else{
                printf("Array not initialized. Use 'set' command first\n");
            }
        }
        else if(strcmp(command,"hist")==0){
            if(set_count != 0){
                int bin_counts[MAX_BINS];
                printf("Enter the number of bins: ");
                scanf("%d",&bins);
                if(bins <= 0 || bins >MAX_BINS)
                    printf("Invalid number of bins. Must be between 1 and 1000\n");
                else{
                    double bin_width = (max - min) / bins;
                    for(int i = 0; i < size; i++){
                        int bin_index = (int)((array[i] - min) / bin_width);
                        if(bin_index == bins)
                            bin_index--;
                        bin_counts[bin_index]++;
                    }
                    int max_cnt = bin_counts[0];
                    for(int i = 1; i < bins; i++){
                        if(max_cnt < bin_counts[i])
                            max_cnt = bin_counts[i];
                    }
                    for(int i = 0; i < bins; i++){
                        double initial = min + i*bin_width;
                        double endpoint = initial + bin_width;
                        int star_no = (int)(((double)bin_counts[i] / max_cnt) * MAX_STARS);
                        printf("[%8.4lf -- %8.4lf]: ",initial,endpoint);
                        for(int i = 1; i <= star_no; i++){
                            printf("*");
                        }
                        printf("\n");
                    }
                }

            }
            else{
                printf("Array not initialized. Use 'set' command first\n");
            }
        }
        else if(strcmp(command,"summary")==0){
            if(set_count != 0){
                printf("min    : %10.4lf\n",min);
                printf("max    : %10.4lf\n",max);
                printf("mean   : %10.4lf\n",mean);
                printf("stddev : %10.4lf\n",stddev);
            }
            else
                printf("Array not initialized. Use 'set' command first\n");
        }
        else if(strcmp(command,"help")==0){
            printf("Commands:\n\n  ");
            printf("set     - Set array size, seed, and distribution (uniform or gaussian)\n  ");
            printf("min     - Print minimum value\n  ");
            printf("max     - Print maximum value\n  ");
            printf("mean    - Print mean value\n  ");
            printf("stddev  - Print standard deviation\n  ");
            printf("hist    - Plot histogram\n  ");
            printf("summary - Print min, max, mean, stddev\n  ");
            printf("help    - Show this help message\n  ");
            printf("exit    - Exit the program\n\n");
        }
        else if(strcmp(command,"exit")==0){
            break;
        }
        else{
            if(set_count == 0)
                printf("Unknown command. Type 'help' for list of commands.\n");
        }
    }
    return 0;
}
