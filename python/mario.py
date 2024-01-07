from cs50 import get_int


# inverted pyramid function
def print_pyramid_line(n):
    for i in range(n):
        print("#", end="")


# pyramind function
def print_mario_pyramid(n):
    # loop in a 2d array of n and only print # when the spaces match de row.
    spaces = n  # We do this with a variable that copy's n value that represents white spaces and substract 1 everytime we do the loop
    for i in range(n):
        spaces -= 1
        print(" " * spaces, end="")  # print white spaces
        print_pyramid_line(i + 1)
        print("  ", end="")  # 2 space gap
        print_pyramid_line(i + 1)
        print()


# main funct
def main():
    while True:
        n = get_int("Number: ")
        if n >= 1 and n <= 8:
            break
    print_mario_pyramid(n)


# call main funct
if __name__ == "__main__":
    main()
