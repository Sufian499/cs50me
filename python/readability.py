from cs50 import get_string


# Count every alphanumeric char
def count_letters(text):
    c = 0
    for char in text:
        if char.isalpha():
            c += 1
    return c


def count_senteces(text):
    c = 0
    for word in text:  # The text is split up per words.
        if "." in word or "!" in word or "?" in word:
            c += 1
    return c


def coleman_lieu_formula(W, S, L):
    L = L / W * 100  # Letters per 100 words
    S = S / W * 100  # Sentences per 100 words
    index = 0.0588 * L - 0.296 * S - 15.8  # coleman lieu formula
    return index


def main():
    # Input
    text_input = get_string("Text: ")
    # Letters
    L = count_letters(text_input)
    # Words
    text_input = text_input.split()
    W = len(text_input)
    # Sentences
    S = count_senteces(text_input)

    # Gent grade level
    index = round(coleman_lieu_formula(W, S, L), 0)
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade: {int(index)}")


if __name__ == "__main__":
    main()
