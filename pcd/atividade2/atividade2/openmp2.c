#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>

#define dim 2048
#define generations 10
#define numThreads 4

// Constants to measure time
#define MICRO ((unsigned long) 1000000)
#define NANOS ((unsigned long)1000000000)

#define SRAND_VALUE 1985

int grid[dim][dim];
int newgrid[dim][dim];

void initGeneration() {
  srand(SRAND_VALUE);
  
  for (int i = 0; i < dim; i++) 
    for (int j = 0; j < dim; j++)
      grid[i][j] = rand() % 2;
}

void printMatrix(int mat[dim][dim]) {
  for (int i = 0; i < dim; i++)  {
    for (int j = 0; j < dim; j++)
        printf("%d ", mat[i][j]);
    printf("\n");
  }
}

int countAliveCells(int grid[dim][dim]) {
    int aliveCells = 0;
    int i, j;
    omp_set_num_threads(numThreads);
    #pragma omp parallel private(i, j) reduction(+:aliveCells)
    #pragma omp for
    for(i=0; i<dim; i++) {  
            for(j=0; j<dim; j++) { 
                if(grid[i][j] == 1) {
                    aliveCells++;
                }
            }
    }
    return aliveCells;
}

int getNeighbors(int grid[dim][dim], int i, int j) {
  int ret = 0, row, col;
  for (int k = i - 1; k <= i + 1; k++) {
    if (k < 0) row = dim - 1;
    else if (k == dim) row = 0;
    else row = k;
    for (int l = j - 1; l <= j + 1; l++) {
      if (k == i && l == j) continue; // verify if actual pos is equal to cell pos

      if (l < 0) col = dim - 1;
      else if (l == dim) col = 0;
      else col = l;
      if (grid[row][col] == 1) ret++;  
    }
  }
  return ret;
}

void copyMatrix(int old[dim][dim], int current[dim][dim]) {
    int i, j;
    for(i=0; i<dim; i++)
        for(j=0; j<dim; j++)
            old[i][j]=current[i][j];
}

int main() {
    struct timeval before, after;
    time_t elapsedUs;
    gettimeofday(&before, NULL);

    initGeneration();
    printf("Alive cells: %d\n\n", countAliveCells(grid));

    gettimeofday(&after, NULL);
    elapsedUs = after.tv_usec - before.tv_usec + (after.tv_sec - before.tv_sec) * MICRO;
    printf("Runtime: %lf s\n",  (double)elapsedUs/MICRO);
    
    return 0;
}