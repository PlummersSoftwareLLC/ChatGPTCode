#include <stdio.h>
#include <string.h>

void decimal_to_roman(int decimal_num, char *roman_numeral) {
    // Define arrays to represent the Roman numeral symbols and their corresponding decimal values
    char symbols[13][3] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    
    // Initialize the result string with an empty string
    roman_numeral[0] = '\0';
    
    // Loop through each value in the list of decimal values
    for (int i = 0; i < 13; i++) {
        // If the decimal number is greater than or equal to the current value
        while (decimal_num >= values[i]) {
            // Add the corresponding symbol to the result string
            strcat(roman_numeral, symbols[i]);
            // Decrement the decimal number by the current value
            decimal_num -= values[i];
        }
    }
}

int main() {
    int decimal_num;
    char roman_numeral[50];
    
    // Get user input for the decimal number
    printf("Enter a decimal number: ");
    scanf("%d", &decimal_num);
    
    // Call the function to convert the decimal number to a Roman numeral
    decimal_to_roman(decimal_num, roman_numeral);
    
    // Print the resulting Roman numeral
    printf("The Roman numeral equivalent of %d is %s.\n", decimal_num, roman_numeral);
    
    return 0;
}
