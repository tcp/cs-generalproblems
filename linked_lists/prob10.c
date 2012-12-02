#include <stdio.h>
#include <stdlib.h>

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

/* Problem 10
 *   Implement an algorithm to find the nth to last element of a singly linked
 *   list.
 */

// First solution: iterate until the end, get the list end and then run the list
// again until we are at LENGTH - N. This function will iterate through the list
// twice in the worse case (N = 1);
Node* findNtoLast(Node* root, int N) {
  int length;
  Node* node;
  int i;

  node = root;

  // walk to the end of the list
  for (length = 0; node != NULL; length++) {
    node = node->next;
  }

  // check the boundary
  if (N > length || N <= 0) {
    return NULL;
  }

  // back to beginning
  node = root;

  // walk to Nth to last element. N = 1 is the last element.
  for (i = 0; i < length - N; i++) {
    node = node->next;
  }

  // return element
  return node;
}

// Second solution: In this solution, I have two pointers that are going to be
// kept at a N-1 distance from each other. It is basically the same as last time
// but the list is only run over once.
Node* findNtoLastPointers(Node* root, int N) {
  Node* node;    // Node that will stay behind and will be the solution node
  Node* runner;  // Node that will be ahead by N-1 elements and runs to list end
  int i;

  if (N <= 0) {
    return NULL;
  }

  // Position runner and node at the start of the list
  runner = node = root;

  // Advances the runner N-1 positions in the list
  for (i = 0; i < N; i++) {
    runner = runner->next;
    // What if N > length?
    if (!runner && N > i + 1) {
      return NULL;
    }
  }

  // Make both pointers advance one node. When runner hits the end of the list,
  // then node is the Nth to last element.
  while (runner != NULL) {
    runner = runner->next;
    node = node->next;
  }

  return node;
}

// Print list function
void printList(Node* root) {
  Node* node;

  node = root;

  while (node != NULL) {
    printf("%c->", node->value);
    node = node->next;
  }

  printf("end\n");
}

int main() {
  Node* root;
  Node* node;
  int N;
  int i;

  N = 5;

  // Seed
  srand((unsigned) time(NULL));

  // Initialize new node
  root = new_node();

  // Positions at start of the list
  node = root;

  // Populates the list a little
  for (i = 0; i < 35; i++) {
    node->next = new_node();
    node = node->next;
  }

  printList(root);

  node = findNtoLast(root, N);

  if (node) {
    printf("N to last (count): %c\n", node->value);
  }
  else {
    printf("N to last (count): Invalid N!\n");
  }

  node = findNtoLastPointers(root, N);

  if (node) {
    printf("N to last (pointers): %c\n", node->value);
  }
  else {
    printf("N to last (pointers): Invalid N!\n");
  }

  return 0;
}
