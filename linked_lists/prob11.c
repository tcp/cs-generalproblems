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

/* Problem 11
 *  Implement an algorithm to delete a node in the middle of a single linked
 *  list, given only access to that node.
 *  EXAMPLE
 *  Input: the node ‘c’ from the linked list a->b->c->d->e
 *  Result: nothing is returned, but the new linked list looks like a->b->d->e
 */

// The important thing to notice in this question is the word MIDDLE. From the
// example above, 'e' would never be asked to be removed by using this function.
// My solution to this problem is to make use of the node->next element, copying
// it to node and making the pointer node->next point to node->next->next. In
// other words, from the example above, to element 'c' we copy 'd'. Then, this
// element will point to 'e'. The old 'd' will be free'd and removed from the
// list.
void deleteNode(Node* node) {
  Node* toDelete; // deletable element (the old 'd' from the example)

  // Node copying
  node->value = node->next->value;
  node->next = node->next->next;

  // Free deletable element
  free(toDelete);
  toDelete = NULL;
}

// Print list starting from node 'root'
void printList(Node* root) {
  Node* node = root;

  while (node != NULL) {
    printf("%c->", node->value);
    node = node->next;
  }

  printf("end\n");
}

// Testing
int main() {
  Node* root;
  Node* node;
  int i;

  srand((unsigned) time(NULL));

  root = new_node();

  node = root;

  for (i = 0; i < 35; i++) {
    node->next = new_node();
    node = node->next;
  }

  printList(root);

  node = root->next->next->next;

  deleteNode(node);

  printList(root);

  return 0;
}
