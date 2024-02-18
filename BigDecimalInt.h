#ifndef BIGDECIMALINT_BIGDECIMALINT_H
#define BIGDECIMALINT_BIGDECIMALINT_H


#include <iostream>
#include <string>
#include <regex>
#include <stdlib.h>
using namespace std;

class BigDecimalInt {
private:
    string decStr;
    char sign;

public:
    BigDecimalInt(string);
    BigDecimalInt();
    friend ostream& operator <<(ostream &out, BigDecimalInt b);
    bool operator <(BigDecimalInt anotherDec);
    bool operator >(BigDecimalInt anotherDec);
    bool operator ==(BigDecimalInt anotherDec);
    BigDecimalInt operator -(BigDecimalInt anotherDec);
    BigDecimalInt operator +(BigDecimalInt anotherDec);
    BigDecimalInt operator=(BigDecimalInt &anotherDec);
    char get_sign();
    int size();

};



#endif //BIGDECIMALINT_BIGDECIMALINT_H
