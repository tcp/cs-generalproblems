#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Problem 5
 *   Write a method to replace all spaces in a string with '%20'.
 */

// Basic find and replace. The catch is that we need to move things around. It is
// easier to create a new string and dump the old one than to do realloc and temp
// variables.
void replaceSpaces(char** string) {
  int i, j;
  int count = 0;
  char* temp;

  // count number of spaces
  for (i = 0; (*string)[i] != '\0'; i++) {
    if ((*string)[i] == ' ') {
      count++;
    }
  }

  // lets re-size so we get the correct final string
  temp = (char*) malloc(i + (count*2) + 1);

  // swap each space ' ' with '%20'
  for (i = 0, j = 0; (*string)[i] != '\0'; i++) {
    if ((*string)[i] == ' ') {
      temp[j++] = '%';
      temp[j++] = '2';
      temp[j++] = '0';
    }
    else {
      temp[j++] = (*string)[i];
    }
  }

  // todo: check locality performance when maintaining i = original length

  // close the string
  temp[j] = '\0';

  // free former pointer (and the whole string);
  free(*string);

  // point to new pointer
  *string = temp;
}

// I also decided to do a print '%20' function
void printWithEncodedSpaces(char* string, int endline) {
  int i;

  for (i = 0; string[i] != '\0'; i++) {
    if (string[i] == ' ') {
      printf("%%20");
    }
    else {
      printf("%c", string[i]);
    }
  }

  if (endline) {
    printf("\n");
  }
}

// Testing
int main() {
  char* str;

  str = (char*) malloc(sizeof(char) * 100);
  
  strcpy(str, "Raging Elephants");

  printf("String is > %s < before replacing spaces.\n", str);

  replaceSpaces(&str);

  printf("String is > %s < after replacing spaces\n", str);

  strcpy(str, "sushi samba");

  printf("String is > %s < but we are just printing below\n", str);

  printWithEncodedSpaces(str, 1);

  return 0;
}
