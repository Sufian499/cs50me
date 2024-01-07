import cs50

# Make an array form int
def make_credit_array(number):
    number_list = list()
    for i in repr(number):
        number_list.append(int(i))
    return number_list


def valid_credit_number(number):
    # if master card
    if number[0] == 5 and number[1] in range(1, 6) and len(number) == 16:
        return "MASTERCARD"

    # if AMEX
    if len(number) == 15 and number[0] == 3:
        if number[1] == 4 or number[1] == 7:
            return "AMEX"

    # if VISA
    if number[0] == 4:
        if len(number) == 13 or len(number) == 16:
            return "VISA"

    # else
    return "INVALID"

# If the * 2 number is bigger than 10 we return the 2 digits
def bigger_than_10(number):
    if number >= 10:
        first_digit = number / 10
        second_digit = number % 10
        number = int(first_digit) + int(second_digit)
    return number

# Algorithm
def luhn_checksum(number):
    sum_nums = 0  # Variable para la suma de los numeros que se multiplicaran por 2
    tmp_sum_nums = (
        0  # Variable temporal para almacenar los numeros que se multiplicarán por 2.
    )
    for i in range(len(number)):
        if i % 2 != 0:
            tmp_sum_nums = number[i] * 2
            tmp_sum_nums = bigger_than_10(tmp_sum_nums)
            sum_nums = sum_nums + tmp_sum_nums
        else:
            sum_nums = sum_nums + number[i]
    return sum_nums % 10


def main():
    # Pedir tarjeta
    credit_num = cs50.get_int("Number: ")
    credit_num = make_credit_array(credit_num)
    validation = valid_credit_number(credit_num)
    credit_num.reverse() # I reverse the list to itarate the *2 numbers more easily

    # Conditions for the output
    if validation == "INVALID":
        print(validation)
    if luhn_checksum(credit_num) == 0:
        print(validation)
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
  
