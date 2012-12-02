#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Problem 8
 *   Assume you have a method isSubstring which checks if one word is a substring of
 *   another. Given two strings, s1 and s2, write code to check if s2 is a rotation
 *   of s1 using only one call to isSubstring (i.e., "waterbottle" is a rotation of
 *   "erbottlewat").
 */

// Solution here is to concatenate both strings and use isSubstring.

// Concatenates string
char* concatenate(char* string) {
  int length, i;
  char* new_str;

  // count string length
  for (length = 0; string[length] != '\0'; length++);

  // allocate 'new string'
  new_str = (char*) malloc((length * 2) + 1);

  // copy content from original string
  for (i = 0; i < length; i++) {
    new_str[i] = string[i];
    new_str[i+length] = string[i];
  }

  // mark the end of the string
  new_str[i+length] = '\0';

  return new_str;
}

int main() {
  char str1[15] = "mercury";
  char *str2;

  str2 = (char*) malloc(sizeof(char) * 10);

  strcpy(str2, "curymer");

  str2 = concatenate(str2);

  // isSubstring will now run on (pattern, concatenated string).
  // printf("%s\n", isSubstring(str1, str2) ? "yes" : "no");

  return 0;
}
