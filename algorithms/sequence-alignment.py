"""
Farham Ahmad
Algorithm: Sequence alignment.
"""

MATCH = 10
MISMATCH_PENALTY = -2
GAP_PENALTY = -5


def align(str1, str2):
    """Method to determine a global alignment of two sequences
    represented as strings, using dynamic programming.
    """

    n = len(str1)
    m = len(str2)

    scores = [
        [ 0 for j in range(m+1) ]
        for i in range(n+1)
    ]
    directions = [
        [ '.' for j in range(m+1) ]
        for i in range(n+1)
    ]
    
    scores[0][0] = 0
    for i in range(1, n+1):
        scores[i][0] = scores[i-1][0] + GAP_PENALTY
        directions[i][0] = "UP"
    for j in range(1, m+1):
        scores[0][j] = scores[0][j-1] + GAP_PENALTY
        directions[0][j] = "LEFT"

    for i in range(1, n+1):
        for j in range(1, m+1):

            if str1[i-1] == str2[j-1]:  # match found
                scores[i][j] = scores[i-1][j-1] + MATCH
                directions[i][j] = "DIAG"
            else:
                gap_str1 = (scores[i][j-1] + GAP_PENALTY, "LEFT")
                gap_str2 = (scores[i-1][j] + GAP_PENALTY, "UP")
                mismatch = (scores[i-1][j-1] + MISMATCH_PENALTY, "DIAG")

                max_value, direction = sorted([gap_str1, gap_str2, mismatch], key=lambda x: x[0])[-1]
            
                scores[i][j] = max_value
                directions[i][j] = direction
    
    print("PRINTING SCORES....")
    __print(scores)
    print()

    print("PRINTING DIRECTIONS...")
    __print(directions)

    sequence1 = ""
    sequence2 = ""

    ptr = (n,m)
    while True:
        i, j = ptr
        if directions[i][j] == "DIAG":
            sequence1 += str1[i-1]
            sequence2 += str2[j-1]
            ptr = (i-1,j-1)
        elif directions[i][j] == "UP":
            sequence1 += str1[i-1]
            sequence2 += '-'
            ptr = (i-1,j)
        else:
            sequence1 += '-'
            sequence2 += str2[j-1]
            ptr = (i,j-1)

        if ptr == (0,0): break
        
    
    sequence1 = sequence1[::-1]
    sequence2 = sequence2[::-1]

    print(f"SEQ1: {sequence1}")
    print(f"SEQ2: {sequence2}")

def __print(table):
    """Helper method to print a structured table."""
    for row in table:
        print(row)

def main():
    """Development and Testing."""

    # s1 = "TAATTACGCAG"
    # s2 = "GATACT"

    s1 = "ab"
    s2 = "ba"

    align(s1, s2)

if __name__ == "__main__":
    main()