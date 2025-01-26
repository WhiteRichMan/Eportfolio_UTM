#include <iostream>

void add(double a, double b) {
    std::cout << "Result: " << a + b << std::endl;
}

void subtract(double a, double b) {
    std::cout << "Result: " << a - b << std::endl;
}

void multiply(double a, double b) {
    std::cout << "Result: " << a * b << std::endl;
}

void divide(double a, double b) {
    if (b != 0) {
        std::cout << "Result: " << a / b << std::endl;
    } else {
        std::cout << "Error: Division by zero!" << std::endl;
    }
}

int main() {
    double num1, num2;
    char operation;

    std::cout << "Enter first number: ";
    std::cin >> num1;

    std::cout << "Enter operation (+, -, *, /): ";
    std::cin >> operation;

    std::cout << "Enter second number: ";
    std::cin >> num2;

    switch (operation) {
        case '+':
            add(num1, num2);
            break;
        case '-':
            subtract(num1, num2);
            break;
        case '*':
            multiply(num1, num2);
            break;
        case '/':
            divide(num1, num2);
            break;
        default:
            std::cout << "Error: Invalid operation!" << std::endl;
            break;
    }

    return 0;
}