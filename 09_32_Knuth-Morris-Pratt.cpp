#include <stdio.h>
#include <string.h>

// Function to compute the Longest Prefix Suffix (LPS) array
void computeLPSArray(char pattern[], int M, int lps[]) {
    int len = 0;  // length of the previous longest prefix suffix
    int i = 1;
    lps[0] = 0;   // lps[0] is always 0

    // Build the lps array
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Pattern Searching Algorithm
void KMPSearch(char pattern[], char text[]) {
    int M = strlen(pattern);
    int N = strlen(text);

    int lps[M];
    computeLPSArray(pattern, M, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

// Main function
int main() {
    // --- Test Input ---
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABCABAB";

    printf("Text: %s\n", text);
    printf("Pattern: %s\n\n", pattern);

    KMPSearch(pattern, text);

    return 0;
}

