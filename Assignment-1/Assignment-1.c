#include <stdio.h>

int main() { 
    
    int i, j, space, num_row;
    char check = 'y';

    while (check =='y')
    {
        printf("Enter the number of rows to operate : ");
        scanf("%d",&num_row);

        int clearBuffer;

        while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF); // to clear out the input buffer 

        for (i = 1; i <= num_row; i++) {
                
            for (space = i; space < num_row; space++) {
                printf(" ");
            }
                
            for (j = 1; j <= 2 * i - 1; j++) {
                printf("*");
            }
            if(i!=num_row) {
                printf(" "); //For single segment peak
            }

            for (j = 1; j <= 2 * (num_row - i) - 1; j++) { //the middle section is to make the decreasesment of the code, -1 is to map out the sharp edge
                printf(" ");
            }
            printf(" ");

            for (j = 1; j <= 2 * i - 1; j++) {
                printf("*");
            }
            printf("\n");
        }

        printf("continue? (y/n) : ");
        check = getchar();

        while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF);

        while(check != 'y' && check != 'n') {
            printf("The code is just asking for (y/n) : ");
            check = getchar();

            while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF);
        }
    }
    printf("\nThe end of the implemented code.\n");
    printf("----------------------------------");

    return 0;
}
