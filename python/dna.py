import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    csv_file = sys.argv[1]  # Filename
    STRs = list()  # Lista con los headers
    rows = []  # lista con un diccionario basado en el csv
    try:
        with open(csv_file, "r") as database:
            reader = csv.DictReader(database)
            for row in reader.fieldnames:
                STRs.append(row)
            for row in reader:
                rows.append(row)
    except FileNotFoundError:
        print("File not found")
        return

    # TODO: Read DNA sequence file into a variable
    txt_file = sys.argv[2]  # Filename
    dna_sequence = ""  # String to store the sequence
    try:
        with open(txt_file, "r") as sequence:
            dna_sequence = sequence.read()
    except FileNotFoundError:
        print("File not found")
        return

    # TODO: Find longest match of each STR in DNA sequence
    matches = dict()
    # Loop through the STR and store in a dictionary the STR and the longes match value
    for STR in STRs:
        if STR != "name":
            matches[STR] = longest_match(dna_sequence, STR)
    # TODO: Check database for matching profiles
    # Loop to check the dict of the database, looping through every row of names and returning the name of the person
    # that haves all matches with the matches dictionary created previously.
    for row in rows:
        c = 0
        for STR in matches:
            if int(matches[STR]) == int(row[STR]):
                c += 1
        if c == len(matches):
            print(row["name"])
            sys.exit(0)

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
