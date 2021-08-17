/********************************************
 Problema 3
 Tuning do cavalo
 Tempo Limite: 0,5s (C/C++)
 Autor: Gaspar Andrade  RA: 133633
 UC: Projeto e Analise de Algortimos
 Prof. Dr. Reginaldo Kuroshu
 ********************************************/
#include <cstring> // memset
#include <cstdio> // printf and scanf

#define N 10 // max matrix size, defined by the given problem

const int moves[][9] = {{ 2, 1, -1, -2, -2, -1, 1, 2, 2},
                        { 1, 2, 2, 1, -1, -2, -2, -1, 1}};

struct Graph {
  bool visited[N][N];
  int max, all_pos;

  void set_positions(int);
  void search(int, int, int);
};

bool isValid(int x, int y) {
  if (x < 0 || y < 0 || x >= N || y >= N) return false;
  return true;
}
void Graph::search(int x, int y, int pos) {
  this->visited[x][y] = pos;

  if (pos > this->all_pos) // base case
    return;

  if (pos > this->max) // set new value to max
    this->max = pos;

  for (int i = 0; i < 8; i++) {
    int newX = x + moves[0][i];
    int newY = y + moves[1][i];

    if (isValid(newX, newY) && !this->visited[newX][newY]) 
      this->search(newX, newY, pos+1);
  }
  this->visited[x][y] = 0;
}

void Graph::set_positions(int n) {
  int tmp[2];
  int count = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &tmp[0], &tmp[1]);
    while (tmp[1] > 0) {
      this->visited[i][tmp[0]++] = 0; // set possible positions to false
      tmp[1]--;
      count++;
    }
  }
  this->all_pos = count;
}

int main() {
  Graph *g = new Graph{};
  memset(g->visited, 1, sizeof(g->visited)); // set all positions to true

  int n;
  scanf("%d", &n);

  g->set_positions(n);
  g->search(0, 0, 1);
  printf("%d\n", g->all_pos-g->max);

	return 0;
}
