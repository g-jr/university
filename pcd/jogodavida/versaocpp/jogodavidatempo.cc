/********************
 Game of Life (John H. Conway) implementation
 Developed by Gaspar Andrade
 *******************/
#include <iostream>
#include <pthread.h>
#include <cstring>
#include <chrono>
#include <cstdio>

#define SRAND_VALUE 1985
#define dim 2048
#define generation 2000

pthread_mutex_t lock;

struct args {
  int ***grid;
  int ***newgrid;
  int id;
  int totalThreads;
}; 
typedef args args_t;

int **allocateGrid(void) {
  int **ret;
  ret = new int*[dim];
  for (int i = 0; i < dim; i++)
    ret[i] = new int[dim];
  return ret;
}

void deallocateGrid(int **mat) {
  for (int i = 0; i < dim; i++)
    delete[] mat[i];
  delete[] mat;
}

void initGeneration(int **mat) {
  srand(SRAND_VALUE);
  for (int i = 0; i < dim; i++) 
    for (int j = 0; j < dim; j++)
      mat[i][j] = rand() % 2;
}

int getNeighbors(int **grid, int i, int j) {
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

void *threadRoutine(void *ar) {
  int temp;
  //args_t *ptr = (args_t) ar;
  args_t *ptr = (args_t*) ar;
  int i, j, n;
	
	pthread_mutex_lock(&lock);
	n = dim / ptr->totalThreads;
	i = ptr->id * n;  
  n = n * (ptr->id + 1);
	ptr->id++;
	pthread_mutex_unlock(&lock); 
  for (; i < n; i++) {
    for (j = 0; j < dim; j++) {
      temp = getNeighbors((*ptr->grid), i, j);
      if ((*ptr->grid)[i][j] == 1 && temp < 2) (*ptr->newgrid)[i][j] = 0; //  A
      else if ((*ptr->grid)[i][j] == 1 && (temp == 2 || temp == 3)) (*ptr->newgrid)[i][j] = 1; // B
      else if ((*ptr->grid)[i][j] == 1 && temp >= 4) (*ptr->newgrid)[i][j] = 0; // C
      else if ((*ptr->grid)[i][j] == 0 && temp == 3) (*ptr->newgrid)[i][j] = 1; // D
      else (*ptr->newgrid)[i][j] = 0;
    }
  }
  pthread_exit(NULL);
}

void printMatrix(int **mat) {
  for (int i = 0; i < dim; i++)  {
    for (int j = 0; j < dim; j++)
      std::cout << mat[i][j] << ' ';  
    std::cout << '\n';
  }
}

int main(void) {
  auto start = std::chrono::high_resolution_clock::now();
  int numThreads, numGenerations;
  std::cout << "enter with the number of threads: ";
  std::cin >> numThreads;
  std::cout << "enter with the number of generations: ";
  std::cin >> numGenerations;
  pthread_t tid[numThreads];
  args_t *argsThread = new args;
  argsThread->grid = new int**;
  argsThread->newgrid = new int**;

  *argsThread->grid = allocateGrid();
  *argsThread->newgrid = allocateGrid();

  initGeneration(*argsThread->grid);
  
  int total = 0;
  for (int i = 0; i < dim; i++)
    for (int j = 0; j < dim; j++)
      if ((*argsThread->grid)[i][j] == 1) total++;
  std::cout << "initial condition: " << total << '\n';

 	if (pthread_mutex_init(&lock, NULL) != 0) { 
  	printf("\n mutex init has failed\n"); 
		return 1; 
  } 
  
  int ***tempgrid;
  argsThread->totalThreads = numThreads;
  while (numGenerations--) {
    argsThread->id = 0;
    for (int i = 0; i < numThreads; i++)
      pthread_create(&tid[i], NULL, threadRoutine, argsThread);
    for (int i = 0; i < numThreads; i++)
      pthread_join(tid[i], NULL);
    tempgrid = argsThread->grid;
    argsThread->grid = nullptr;
    argsThread->grid = argsThread->newgrid;
    if (numGenerations > 0) {
      argsThread->newgrid = tempgrid;
    } else { 
      argsThread->newgrid = nullptr;
      deallocateGrid(*tempgrid);
      delete[] tempgrid;
    }
  }
  total = 0;
  for (int i = 0; i < dim; i++)
    for (int j = 0; j < dim; j++)
      if ((*argsThread->grid)[i][j] == 1) total++;
  std::cout << total << '\n';

  deallocateGrid(*argsThread->grid);
  delete[] argsThread->grid;
  delete argsThread;

  using FpMilliseconds = 
          std::chrono::duration<float, std::chrono::milliseconds::period>;
  static_assert(std::chrono::treat_as_floating_point<FpMilliseconds::rep>::value, 
                     "Rep required to be floating point");
  auto stop = std::chrono::high_resolution_clock::now();
  auto f_ms = FpMilliseconds(stop - start);
  std::cout << f_ms.count()/1000;
  return 0;
}
