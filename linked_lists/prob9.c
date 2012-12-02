#include <stdlib.h>
#include <stdio.h>

// My personal preference is to keep a set of pointers that 'control' the linked
// list. These pointers are, at least, direct access to the HEAD and TAIL of the
// linked list. If the list is large, I usually keep a pointer at element 2^n,
// with n growing with the list.

// For 'difficulty' purposes, I decided not to include HEAD, TAIL and other
// control pointers. I think the problems also kinda require this, as they are
// usually asking me to remove things from the list, replace and so on.

// Also, this is a quick, unpolished (obviously) implementation that I did while
// I was on the train from Stockholm to Uppsala. :)
typedef struct node_list {
  char value;
  struct node_list* next;
} Node;

Node* new_node() {
  Node* node = (Node*) malloc(sizeof(Node));
  node->value = (rand() % 26) + 'A';
  node->next = NULL;
}

/* Problem 9
 *   Write code to remove duplicates from an unsorted linked list.
 *   FOLLOW UP
 *   How would you solve this problem if a temporary buffer is not allowed?
 */

// To remove duplicates in an unsorted linked list if a temporary buffer is not
// allowed, I will iterate through the list elements, starting from the head,
// and search for duplicates in every element ahead. If an element is a
// duplicate, remove it by making the previous element point to the next element
// of the duplicate.
void removeDuplicates(Node* head) {
  Node* node = head;   // element that will iterate through list
  Node* prev = head;   // keeps track of "previous" element
  Node* search_start;  // pointer to the currently evaluated element 

  int i;

  for (i = 0; node != NULL; i++) {
    // Updates value to be checked (curr_value), 
    search_start = node;
    prev = node;

    // points to the next element
    node = node->next;

    while (node != NULL) {
      // No match. Continue list node iteration, updates prev.
      if (node->value != search_start->value) {
	prev = node;
	node = node->next;
      }
      // Match! Lets remove the element
      else {
	// PREV -> NEXT
	prev->next = node->next;
	free(node);
	node = prev->next;
      }
    }

    // moves the node to the next element to be iterated
    node = search_start->next;
  }
}

int main() {
  srand((unsigned) time(NULL));
  Node* root = new_node();
  Node* node = root;
  int i;

  for (i = 0; i < 15; i++) {
    node->next = new_node();
    node = node->next;
  }

  node = root;

  while(node != NULL) {
    printf("%c->", node->value);
    node = node->next;
   }

  printf("end\n\n");

  if (root != NULL) {
    removeDuplicates(root);
  }

  node = root;

  while(node != NULL) {
    printf("%c->", node->value);
    node = node->next;
  }

  printf("null\n");

  return 0;
}
