#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NUM_TABLE_CHARS 256 // # ASCII Table

/* Problem 3
 * Design an algorithm and write code to remove the duplicate characters
 * in a string without using any additional buffer. NOTE: One or two 
 * additional variables are fine. An extra copy of the array is not.
 * FOLLOW UP
 * Write the test cases for this method.
 */

// To solve this, in order, I assumed it is only letters present in the
// string which makes it easier to provide a quick answer. Also, assumed
// ASCII encoding. I tried to avoid using an int array representing the symbols
// in the ASCII table, just to do it differently. The solution with the array is
// presented further down.

// I compared each character to a 64-bit long variable that identifies each
// letter of the english alphabet.
// Each bit represent a letter identified sequentially from 'A' in the ASCII
// table. If a letter is present in the string, the bit in the 64-bit variable
// is set to 1.
// If a character has already been used, it is just discarded.
void removeDuplicates(char* string) {
  uint64_t bitCheck = 0;
  int stop = 0; 
  int i;

  for (i = 0; string[i] != '\0'; i++) {
    if ((bitCheck & (1 << (string[i] - 'A'))) == 0) {
      bitCheck |= (1 << (string[i] - 'A'));
      string[stop] = string[i];
      stop++;
    }
  }

  // ends the string at the proper place
  string[stop] = '\0';
}

// removes duplicate using int array that represents the encoding table
void removeDuplicatesWithArray(char* string) {
  int chars[NUM_TABLE_CHARS] = { 0 };
  int stop = 0;
  int i;

  for (i = 0; string[i] != '\0'; i++) {
    if (!chars[string[i]]) {
      chars[string[i]] = 1;
      string[stop++] = string[i];
    }
  }

  string[stop] = '\0';
}

int main() {
  char str1[] = "abcd"; // expected: abcd
  char str2[] = "abcab"; // expected: abc
  char str3[] = ""; // expected : 
  char str4[] = "aaaabbbbbbbb"; // expected: ab
  char str5[] = "uahdfuhadsfuahsdf"; // expected: uahdfs
  char str6[] = "papapapaololololololol"; // expected: paol

  printf("%s : ", str1);
  removeDuplicates(str1);
  printf("%s\n", str1);

  printf("%s : ", str2);
  removeDuplicates(str2);
  printf("%s\n", str2);

  printf("%s : ", str3);
  removeDuplicates(str3);
  printf("%s\n", str3);

  printf("%s : ", str4);
  removeDuplicates(str4);
  printf("%s\n", str4);

  printf("%s : ", str5);
  removeDuplicates(str5);
  printf("%s\n", str5);

  printf("%s : ", str6);
  removeDuplicates(str6);
  printf("%s\n", str6);

  return 0;
}
