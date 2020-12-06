/* Gaspar Andrade – 133633
o 
 * UC: AED2 Prof. Alvaro Luiz Fazenda
 * Tarefa 10 - Pesquisa Interna - Hashing com Encadeamento
 * 1o semestre de 2020
 * UNIFESP - ICT
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>

struct Elemento {
  int id;
  Elemento *prox;
};

struct Hash {
  Elemento *head;
  Hash() { head = NULL; }
};

bool pesquisa(Hash *lista, int n, int id) { // (1) pesquisa
  int pos = id % n;
  Elemento **temp = &lista[pos].head;
  while (*temp) {
    if ((*temp)->id == id)
      return true;
    temp = &(*temp)->prox;
  }
  return false;
}

void insere(Hash *lista, int n, int id) { // (2) insercao
  int pos = id % n;
  Elemento **temp = &lista[pos].head;
  while (*temp)
    temp = &(*temp)->prox;
  Elemento *inserido = new Elemento{id};
  *temp = inserido;
}

void remove(Hash *lista, int n, int id) {
  int pos = id % n;
  Elemento **temp = &lista[pos].head;
  Elemento *aux;
  if ((*temp)->id == id) { // se for o primeiro elemento
    aux = *temp;
    if ((*temp)->prox)
      *temp = (*temp)->prox;
    else {
      *temp = NULL;
      lista[pos].head = NULL;
    }
    delete aux;
    return;
  }
  while ((*temp)->prox)
    if ((*temp)->prox->id == id) {
      aux = (*temp)->prox;
      (*temp)->prox = (*temp)->prox->prox;
    }
}

void imprime(Hash *lista, const int &n) {
  Elemento *temp;
  for (int i = 0; i < n; i++) {
    printf("[%d]", i);
    temp = lista[i].head;
    while (temp) {
      printf(" %d", temp->id);
      temp = temp->prox;
    }
    printf("\n");
  }
}

int main() {
  int n, m; 
  scanf("%d", &n); // tamanho da tabela de hash
  Hash *lista = new Hash[n];

  scanf("%d", &m); // quantidade de numeros de entrada
  int temp;
  for (int i = 0; i < m; i++) {
    // realiza insercao
    scanf("%d", &temp);
    insere(lista, n, temp);
  }
  int p;
  scanf("%d", &p); // numero a ser pesquisado
  pesquisa(lista, n, p) ? remove(lista, n, p) : insere(lista, n, p);
  imprime(lista, n);
  return 0;
}
