def decimal_to_roman(decimal):
    roman_numeral_map = (('M', 1000),
                        ('CM', 900),
                        ('D', 500),
                        ('CD', 400),
                        ('C', 100),
                        ('XC', 90),
                        ('L', 50),
                        ('XL', 40),
                        ('X', 10),
                        ('IX', 9),
                        ('V', 5),
                        ('IV', 4),
                        ('I', 1))

    result = []
    for r, num in roman_numeral_map:
        count = int(decimal / num)
        result.append(r * count)
        decimal -= num * count
    return ''.join(result)


if __name__ == "__main__":
    decimal = int(input("Enter a decimal number: "))
    print("The equivalent Roman numeral is:", decimal_to_roman(decimal))
