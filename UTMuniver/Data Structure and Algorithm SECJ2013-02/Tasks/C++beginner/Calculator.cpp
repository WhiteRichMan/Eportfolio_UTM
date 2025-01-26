//
// Created by Руслан Загидуллин on 21.10.2024.
//

#include "Calculator.h"
#pragma once
class Calculate{

public:
    double Calculate(double x, char oper, double y);
};
    switch(oper){
    case '+':return x + y;
    case '-':return x - y;
    case '*':return x * y;
    case '/':return x / y;
    default:return 0.0;
    }
}