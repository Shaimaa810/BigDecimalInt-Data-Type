#include "BigDecimalInt.h"
// constructor
BigDecimalInt::BigDecimalInt(string s) {
    regex is_valid("[-|+]?( ){0}[0-9]+");    // ? -->> zero or one ,  + -->> one or more
    if(regex_match(s, is_valid))
    {
        decStr = s;
        if(decStr[0] == '-')
            sign = '-';
        else
            sign = '+';
        if(decStr[0] == '-' || decStr[0] == '+')
            decStr.erase(decStr.begin());
    }
    else
    {
        cout << "Invalid number\n";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Default constructor
BigDecimalInt::BigDecimalInt() {

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// overloading < operator
bool BigDecimalInt::operator<(BigDecimalInt anotherDec) {
    if(sign == '+' && anotherDec.sign == '+'){       // str1 is positive & str2 is positive
        if((decStr.size() < anotherDec.decStr.size()) || (decStr.size() == anotherDec.decStr.size() && decStr < anotherDec.decStr))
            return true;
        else
            return false;
    }
    else if(sign == '-' && anotherDec.sign == '-'){    // str1 is negative & str2 is negative
        if((decStr.size() > anotherDec.decStr.size()) || (decStr.size() == anotherDec.decStr.size() && decStr > anotherDec.decStr))
            return true;
        else
            return false;
    }
    else if(sign == '+' && anotherDec.sign == '-'){   // str1 is positive & str2 is negative
        return false;
    }
    else{            // str1 is negative & str2 is positive
        return true;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// overloading > operator
bool BigDecimalInt::operator>(BigDecimalInt anotherDec) {
    if(sign == '+' && anotherDec.sign == '+'){    // num1 is positive & num2 is positive
        if((decStr.size() > anotherDec.decStr.size()) || (decStr.size() == anotherDec.decStr.size() && decStr > anotherDec.decStr))
            return true;
        else
            return false;
    }
    else if(sign == '-' && anotherDec.sign == '-'){  // num1 is negative & num2 is negative
        if((decStr.size() < anotherDec.decStr.size()) || (decStr.size() == anotherDec.decStr.size() && decStr < anotherDec.decStr))
            return true;
        else
            return false;
    }
    else if(sign == '+' && anotherDec.sign == '-'){   // num1 is positive & num2 is negative
        return true;
    }
    else{             // num1 is negative & num2 is positive
        return false;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// overloading == operator
bool BigDecimalInt::operator==(BigDecimalInt anotherDec) {
    if(sign == anotherDec.sign && decStr == anotherDec.decStr)
        return true;
    else
        return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BigDecimalInt BigDecimalInt::operator-(BigDecimalInt anotherDec) {
    BigDecimalInt ans;
    string num1 = decStr, num2 = anotherDec.decStr;
    if(BigDecimalInt(num1) < BigDecimalInt(num2))swap(num1, num2);
    string s(num1.size() - num2.size(),'0');
    num2 = s + num2;
    string res = "";

    if((sign == '+' && anotherDec.sign == '-') || (sign == '-' && anotherDec.sign == '+')){
        (sign == '+' && anotherDec.sign == '-') ? ans.sign = '+' :ans.sign = '-';
        int carry = 0;
        for (int i = num1.size() - 1; i >= 0; --i) {
            int n1 = num1[i] - '0', n2 = num2[i] - '0';
            int temp = n1 + n2 + carry;
            if(temp <= 9){
                res = to_string(temp) + res;
                carry = 0;
            }
            else{
                res = to_string(temp % 10) + res;
                carry = temp / 10;
            }
        }
        if(carry != 0)res = to_string(carry) + res;
    }
    else{
        //(BigDecimalInt(num1) > BigDecimalInt(num2)) ? ans.sign = '+' : ans.sign = '-';
        if(sign == '+' && anotherDec.sign == '+' && BigDecimalInt(decStr) > BigDecimalInt(anotherDec.decStr))
            ans.sign = '+';
        else if(sign == '+' && anotherDec.sign == '+' && BigDecimalInt(decStr) < BigDecimalInt(anotherDec.decStr))
            ans.sign = '-';
        else if(sign == '-' && anotherDec.sign == '-' && BigDecimalInt(decStr) < BigDecimalInt(anotherDec.decStr))
            ans.sign = '+';
        else
            ans.sign = '-';
        int borrow = 0;
        if(BigDecimalInt(num1) == BigDecimalInt(num2)){
            ans.sign = '+';
            res = "0";
        }
        else{
            for (int i = num1.size() - 1; i >= 0; --i) {
                int n1 = num1[i] - '0', n2 = num2[i] - '0';
                int temp = n1 - n2 - borrow;
                if(temp < 0){
                    borrow = 1;
                    temp += 10;
                    res = to_string(temp) + res;
                }
                else{
                    borrow = 0;
                    res = to_string(temp) + res;
                }
            }
        }
    }
    ans.decStr = res;
    return ans;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BigDecimalInt BigDecimalInt::operator+(BigDecimalInt anotherDec) {
    BigDecimalInt ans;
    string num1 = decStr, num2 = anotherDec.decStr;
    if(BigDecimalInt(num1) < BigDecimalInt(num2))swap(num1, num2);
    string s(num1.size() - num2.size(), '0');
    num2 = s + num2;
    string res = "";
    if(sign == anotherDec.sign){
        (sign == '+' && anotherDec.sign == '+')? ans.sign = '+' : ans.sign = '-';
        int carry = 0;
        for (int i = num1.size() - 1; i >= 0; --i) {
            int n1 = num1[i] - '0', n2 = num2[i] - '0';
            int temp = n1 + n2 + carry;
            if(temp <= 9){
                res = to_string(temp) + res;
                carry = 0;
            }
            else{
                res = to_string(temp % 10) + res;
                carry = temp / 10;
            }
        }
        if(carry != 0)res = to_string(carry) + res;
    }
    else{
        if(sign == '+' && anotherDec.sign == '-' && BigDecimalInt(decStr) > BigDecimalInt(anotherDec.decStr))
            ans.sign = '+';
        else if(sign == '-' && anotherDec.sign == '+' && BigDecimalInt(decStr) < BigDecimalInt(anotherDec.decStr))
            ans.sign = '+';
        else
            ans.sign = '-';
        if(BigDecimalInt(num1) == BigDecimalInt(num2)){
            res = "0";
            ans.sign = '+';
        }
        else{
            int borrow = 0;
            for (int i = num1.size() - 1; i >= 0; --i) {
                int n1 = num1[i] - '0', n2 = num2[i] - '0';
                int temp = n1 - n2 - borrow;
                if(temp < 0){
                    borrow = 1;
                    temp += 10;
                    res = to_string(temp) + res;
                }
                else{
                    borrow = 0;
                    res = to_string(temp) + res;
                }
            }
        }
    }
    ans.decStr = res;
    return  ans;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BigDecimalInt BigDecimalInt::operator=(BigDecimalInt &anotherDec) {
    BigDecimalInt ans;
    ans.sign = sign;
    ans.decStr = decStr;
    return ans;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char BigDecimalInt::get_sign() {
    return sign;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BigDecimalInt::size() {
    return decStr.size();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator <<(ostream &out, BigDecimalInt b){
    if(b.sign == '-')cout << b.sign;
    if(b.decStr.size() == 1)out << b.decStr;
    else{
        bool flag = true;
        for (int i = 0; i < b.decStr.size(); ++i) {
            if(b.decStr[i] == '0' && flag)continue;
            else if(b.decStr[i] != '0' && flag){
                out << b.decStr[i];
                flag = false;
            }
            else out << b.decStr[i];
        }
    }
    return out;
}

