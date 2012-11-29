#include <stdio.h>
#include <stdlib.h>

/* Problem 6
 *   Given an image represented by an NxN matrix, where each pixel in the image is
 *   4 bytes, write a method to rotate the image by 90 degrees. Can you do this in
 *   place?
 */

// The first solution is to just rotate the matrix with the help of a new matrix.
// By doing this, we will shift the objects as shown below in a 3x3 matrix:
//
// 1 2 3       7 4 1
// 4 5 6  ---> 8 5 2 
// 7 8 9       9 6 3
//
// The second solution, it is the same concept. The only difference is that I do it
// in place.

// Print function (debug)
void printImage(int** image, int N) {
  int i, j;

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("%d\t", image[i][j]);
    }
    printf("\n");
  }

  printf("\n");
}

// Rotate function will create a new image and rotate the original into the new,
// allocated image. We visit every element in the matrix once and this solution is
// not in place.
void rotate(int*** image, int N) {
  int i, j;

  int** rotatedImage;

  // initialize
  rotatedImage = (int**) calloc(N, sizeof(int) * N);

  for (i = 0; i < N; i++) {
    rotatedImage[i] = (int*) calloc(N, sizeof(int) * N);
  }

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      rotatedImage[j][N - i - 1] = (*image)[i][j];
    }
  }

  printImage(*image, N);

  printImage(rotatedImage, N);

  for (i = 0; i < N; i++) {
    free((*image)[i]);
  }

  free(*image);

  *image = rotatedImage;
}

// Doing it in place. Think about it as rotating squares inside a matrix.
// Starting from (0,0), make a square with the edges (0,0), (5,0), (5,5) and (0,5).
// Rotate that 90 degrees. Now, make a square with (0,1), (4,0), (5,4) and (1,5).
// Rotate. When the 'outside' of the matrix has been rotated, go inwards and rotate
// inside. Continue until its done!
int rotateInPlace(int** matrix, int N) {
  int temp;
  int i, j;

  printImage(matrix, N);

  // Visit the square from i to N-i-1. That means it visits from 0 to N-1,
  // then from 1 to N-2, 2 to N-3...
  // Cool to point out that N odd/even does not play a part in this solution
  for (i = 0; i < (N / 2); i++) {
    for (j = i; j < N - i - 1; j++) {
      // top left is temp
      temp = matrix[i][j];
      // top left = bottom left
      matrix[i][j] = matrix[N - j - 1][i];
      // bottom left = bottom right
      matrix[N - j - 1][i] = matrix[N - i - 1][N - j - 1];
      // bottom right = top right
      matrix[N - i - 1][N - j - 1] = matrix[j][N - i - 1];
      // top right = temp (old top left)
      matrix[j][N - i - 1] = temp;
    }
  }

  printImage(matrix, N);
}

int main() {
  int N;
  int i, j;
  int count = 1;

  N = 6;

  int** image;

  image = (int**) calloc(N, sizeof(int) * N);

  for (i = 0; i < N; i++) {
    image[i] = (int*) calloc(N, sizeof(int) * N);
  }

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      image[i][j] = count++;
    }
  }

  // Rotate 90 degrees
  rotate(&image, N);

  // Rotate 90 degrees again (180 in total!)
  rotateInPlace(image, N);

  for (i = 0; i < N; i++) {
    free(image[i]);
  }

  free(image);

  return 0;
}


