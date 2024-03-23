#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Add
float add(float *num0, float *num1)
{
    return *num0 + *num1;
}

// Subtract
float sub(float *num0, float *num1)
{
    return *num0 - *num1;
}

// Multiply
float mul(float *num0, float *num1)
{
    return *num0 * *num1;
}

// Divided
float divi(float *num0, float *num1)
{
    if (*num1 == 0)
    {
        printf("Error: Division by zero\n");
        exit(EXIT_FAILURE);
    }
    return *num0 / *num1;
}

bool isNumber(const char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            if (str[i] != '.' && str[i] != '-')
            {
                return false;
            }
        }
    }
    return true;
}

bool verifyOperation(char* operation)
{
    if (*operation == '+' || *operation == '-' || *operation == '.' || *operation == '/')
    {
        return true;
    }
    else if (strcmp(operation, "add") == 0)
    {
        *operation = '+';
    }
    else if (strcmp(operation, "sub") == 0)
    {
        *operation = '-';
    }    
    else if (strcmp(operation, "mul") == 0)
    {
        *operation = '.';
    }    
    else if (strcmp(operation, "div") == 0)
    {
        *operation = '/';
    }
    else 
    {
        return false;
    }
    return true;
}

bool verifyCommand(int argc, char *argv[], float number[], char **operation)
{
    if (argc != 7)
    {
        printf("Wrong number of arguments.\n");
        printf("Usage in any order: %s -n0 <number0> -o <operation> -n1 <number1>\n", argv[0]);
        return false;
    }

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n0") == 0)
        {
            if (isNumber(argv[i + 1]))
            {
                number[0] = atof(argv[i + 1]);
            }
            else
            {
                printf("-n0 arguments must be a number.\n");
                return false;
            }
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            if (verifyOperation(argv[i + 1]))
            {
                *operation = argv[i + 1];
            }
            else
            {
                printf("Check -o arguments for correct operation.\n");
                return false;
            }
        }
        else if (strcmp(argv[i], "-n1") == 0)
        {
            if (isNumber(argv[i + 1]))
            {
                number[1] = atof(argv[i + 1]);
            }
            else
            {
                printf("-n1 arguments must be a number.\n");
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[])
{

    char *operation;
    float number[2];
    if (verifyCommand(argc, argv, number, &operation))
    {
        switch (*operation)
        {
        case '+':
            printf("Result: %.2f\n", add(&number[0], &number[1]));
            break;
        case '-':
            printf("Result: %.2f\n", sub(&number[0], &number[1]));
            break;
        case '.':
            printf("Result: %.2f\n", mul(&number[0], &number[1]));
            break;
        case '/':
            printf("Result: %.2f\n", divi(&number[0], &number[1]));
            break;
        default:
            printf("Invalid operation\n");
            return EXIT_FAILURE;
        }
    }
    return 0;
}
