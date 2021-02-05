#include <stdio.h>

int multiplyTwoIntegers(int number1, int number2);
int sumNumber(int num1, int num2);
int differenceTwoIntergers(int number1, int number2);

int main() {
    printf("hello");
    int num1 = 10, num2 = 5;
    printf("\nnumber1 + number2 = %d", sumNumber(num1, num2));
    printf("\nnumber1 * number2 = %d", multiplyTwoIntegers(num1, num2));
    printf("\nnumber1 * number2 = %d", differenceTwoIntergers(num1, num2));
    scanf("\n%d", &num1);
    return 0;
}

int multiplyTwoIntegers(int number1, int number2){
    return number1 * number2;
}

int sumNumber(int num1, int num2) {
    return num1 + num2;
}

int differenceTwoIntergers(int number1, int number2){
    return number1 - number2;
}
