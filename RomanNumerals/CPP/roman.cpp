#include <iostream>
#include <string>
using namespace std;

string decimalToRoman(int num) {
    string table[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string result = "";
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            num -= values[i];
            result += table[i];
        }
    }
    return result;
}

int main() {
    int decimal;
    cout << "Enter a decimal number: ";
    cin >> decimal;
    cout << "The equivalent Roman numeral is: " << decimalToRoman(decimal) << endl;
    return 0;
}
