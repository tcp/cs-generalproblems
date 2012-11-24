#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Problem 1
 *  Implement an algorithm to determine if a string has all unique characters.
 *  What if you can not use additional data structures?
 */

// Easy way to solve it: Check each ASCII char in the string using an array
// and make sure they do not repeat. 
int checkString(char* string) {
  int chars[256] = {0}; // ASCII chars
  int i;

  // Iterate through all chars in the string
  for (i = 0; string[i] != '\0'; i++) {
    // char has been visited!
    if (chars[string[i]])
      return 0;

    // visit char
    chars[string[i]] = 1;  // I would add this at the top
  }

  return 1;
}

// CheckString 'clever', without an array. Do a bitwise check. It works well
// if you know what kind of String it is. If you only take letters, one could
// use a uint64_t (unsigned 64 bits). Letters in ASCII domain!
int cleverCheckString(char* string) {
  uint64_t bitCheck = 0; // hence the stdint include
  int i = 0;

  // Iterate through all chars
  for (i = 0; string[i] != '\0'; i++) {
    // Check if bit specific position is occupied or not, by comparing
    // the bits in bitCheck to the relative position of the ASCII char in string
    // to its position in the ASCII table starting from 'A' (65)
    if (bitCheck & 1 << (string[i] - 'A')) {
      return 0;
    }

    // Occupy bit position
    bitCheck |= (1 << (string[i] - 'A'));
  }

  return 1;
}

// Another solution would be to sort the string and count the occurence of
// each char. Then it would solve the need to use an array to check if the char
// has been used before. The problem with this solution is that it would cost
// you the original array.
void sort(char* string) {
  int i, j;

  for (i = 0; string[i] != '\0'; i++) {
    for (j = i + 1; string[j] != '\0'; j++) {
      if (string[i] > string[j]) {
	string[j] += string[i];
	string[i] = string[j] - string[i];
	string[j] -= string[i];
      }
    }
  }
}


int sortAndCheckString(char* string) {
  int i = 0;

  // sort string
  sort(string);
  
  // compare sorted string
  while(string[i] != '\0') {
    if (string[i] == string[++i])
      return 0;
  }

  return 1;
}

// Testing..
int main() {
  char test_ok[50] = "abcd";
  char test_fail[50] = "dcbad";

  printf("%s : %s\n", test_ok, checkString(test_ok) ? "pass" : "fail");
  printf("%s : %s\n", test_fail, checkString(test_fail) ? "pass" : "fail");

  printf("%s : %s\n", test_ok, cleverCheckString(test_ok) ? "pass" : "fail");
  printf("%s : %s\n", test_fail, cleverCheckString(test_fail) ?
	 "pass" : "fail");

  printf("%s : %s\n", test_ok, sortAndCheckString(test_ok) ? "pass" : "fail");
  printf("%s : ", test_fail);
  printf("%s\n", sortAndCheckString(test_fail) ? "pass" : "fail");

  return 0;
}
