#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256   // Total number of characters in the input alphabet

// Function to create the bad character heuristic table
void badCharHeuristic(char *pattern, int M, int badchar[NO_OF_CHARS]) {
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Fill the actual value of last occurrence
    for (i = 0; i < M; i++)
        badchar[(int)pattern[i]] = i;
}

// Boyer-Moore search algorithm using Bad Character Heuristic
void boyerMooreSearch(char *text, char *pattern) {
    int N = strlen(text);
    int M = strlen(pattern);
    int badchar[NO_OF_CHARS];

    badCharHeuristic(pattern, M, badchar);

    int s = 0;  // s is the shift of the pattern with respect to text
    while (s <= (N - M)) {
        int j = M - 1;

        // Keep reducing index j while characters match
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        // If the pattern is present at current shift
        if (j < 0) {
            printf("Pattern found at index %d\n", s);

            // Shift pattern so that next character in text aligns
            s += (s + M < N) ? M - badchar[text[s + M]] : 1;
        } else {
            // Shift the pattern so that the bad character aligns
            int shift = j - badchar[text[s + j]];
            s += (shift > 1) ? shift : 1;
        }
    }
}

int main() {
    // --- Test Input ---
    char text[] = "ABAAABCD";
    char pattern[] = "ABC";

    printf("Text: %s\n", text);
    printf("Pattern: %s\n\n", pattern);

    boyerMooreSearch(text, pattern);

    return 0;
}

