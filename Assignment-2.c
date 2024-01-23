#include <stdio.h>
#include <stdlib.h>

float add(float num1, float num2) {
    return num1 + num2;
}

float subtract(float num1, float num2) {
    return num1 - num2;
}

float multiply(float num1, float num2) {
    return num1 * num2;
}

float divide(float num1, float num2) {
    if (num2 != 0) {
        return num1 / num2;
    } else {
        printf("Error! Division by zero is not allowed.\n");
        return 0;
    }
}

int main() {

    char optr;
    float num1, num2, result;
    char continueCalc;

    int clearBuffer;

    while (1) {

        printf("Choose your operator  (+, -, *, /) : ");
        if (scanf(" %c", &optr) != 1) {
            printf("Error! invalid input\n");
            while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF);
            continue;
        }

        printf("Enter two numbers : ");
        if (scanf("%f %f", &num1, &num2) != 2) {
            printf("Error! invalid input\n");
            while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF);
            continue;
        }

        switch (optr) {
            case '+':
                result = add(num1, num2);
                break;
            case '-':
                result = subtract(num1, num2);
                break;
            case '*':
                result = multiply(num1, num2);
                break;
            case '/':
                result = divide(num1, num2);
                break;
            default:
                printf("Error! Invalid operator.\n");
                continue;
        }

        printf("Result : %.2f \n", result);

        printf("Do you want to continue? (If you want enter 'Y' or 'y') : ");
        scanf(" %c", &continueCalc);

        if (continueCalc != 'Y' && continueCalc != 'y') {
            printf("Calculator closed.\n");
            break;
        }
    }

    return 0;
}
