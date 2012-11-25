#include <stdio.h>
#include <stdlib.h>

/* Problem 4
 * Write a method to decide if two strings are anagrams or not.
 */

// The solution for this problem is simple: sort both strings and check if each
// corresponding char on string1 and string2 match. In other words, if
// string1[i] == string2[j].

// Sort the string using insertion sort
void sort(char* string) {
  int i, j, key;

  for (j = 1; string[j] != '\0'; j++) {
    key = string[j];
    i = j - 1;
    
    while (i >= 0 && string[i] > key) {
      string[i+1] = string[i];
      i = i - 1;
    }

    string[i+1] = key;
  }
}

// Sort and compare strings
int anagram(char* string1, char* string2) {
  int i;
  int sorted_str1 = 0, sorted_str2 = 0;

  if (string1[0] != '\0') {
    sort(string1);
    sorted_str1 = 1;
  }

  if (string2[0] != '\0') {
    sort(string2);
    sorted_str2 = 1;
  }

  for (i = 0; string1[i] != '\0'; i++) {
    if (string1[i] != string2[i]) {
      return 0;
    }
  }

  // Handles case where string1[0] = '\0'.
  if (!sorted_str1 && sorted_str2) {
    return 0;
  }

  return 1;
}

int main() {
  char string1[10] = "";
  char string2[10] = "aaazzzaw";
  char string3[10] = "banana";
  char string4[10] = "ananab";
  char string5[10] = "";
  char string6[10] = "";

  printf("%s and %s : ", string1, string2);
  printf("%s\n", anagram(string1, string2) ? "yes" : "no");

  printf("%s and %s : ", string3, string4);
  printf("%s\n", anagram(string3, string4) ? "yes" : "no");

  printf("%s and %s : ", string5, string6);
  printf("%s\n", anagram(string5, string6) ? "yes" : "no");

  return 0;
}
