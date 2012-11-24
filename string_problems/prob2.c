#include <stdio.h>
#include <stdlib.h>

/* Problem 2
 * Write code to reverse a C-Style String.
 */

// Count until the end of the string and exchange pairs (0, n), (1, n-1), ...
void reverseString(char* string) {
  // We want 'i' to be positioned at the beginning of the string
  // and 'j' to be positioned at the end.
  int i, j;

  // Count the size of the string using 'j'
  for (j = 0; string[j] != '\0'; j++);

  // now, place 'i' at the beginning of the string (i = 0) and
  // place 'j' at the end (j = j - 1), but not at '\0' where it
  // is after counting the string size
  for (i = 0, --j; i <= j; i++, j--) {
    string[j] += string[i];
    string[i] = string[j] - string[i];
    string[j] -= string[i];
  }
}

// Testing
int main() {
  char string[5] = "abcd";

  printf("string %s ---> ", string);
  reverseString(string);
  printf("%s\n", string);

  return 0;
}
