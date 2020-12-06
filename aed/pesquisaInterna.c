/* Gaspar Andrade – 133633
 * UC: AED2  Prof. Dr. Alvaro Luiz Fazenda
 * UNIFESP – ICT
 * Tarefa 06 - Pesquisa Interna
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int chave;
  struct No *pai;
  struct No *esq, *dir;
} tipoNo;

void desalocarArvore(tipoNo* aux) { // desalocar memoria dinamica
  if (aux == NULL)
    return;
  desalocarArvore(aux->esq);
  desalocarArvore(aux->dir);
  free(aux);
}

int getAlturaArvore(tipoNo *aux) {
  if (aux == NULL)
    return 0;
  else {
    int esqProfundidade = getAlturaArvore(aux->esq);
    int dirProfundidade = getAlturaArvore(aux->dir);

    if (esqProfundidade > dirProfundidade)
      return esqProfundidade + 1;
    else 
      return dirProfundidade + 1;
  }
}

int getTamanhoArvore(tipoNo *aux) {
  if (aux == NULL)
    return 0;
  else
    return (getTamanhoArvore(aux->esq) + 1 + getTamanhoArvore(aux->dir));
}

tipoNo* treeMinimum(tipoNo* aux) {
  while (aux->esq != NULL)
    aux = aux->esq;
  return aux;
}

void transplant(tipoNo* raiz, tipoNo* u, tipoNo* v) {
  if (u->pai == NULL)
    raiz = v;
  else if (u == u->pai->esq)
    u->pai->esq = v;
  else u->pai->dir = v;
  if (v != NULL)
    v->pai = u->pai;
  free(v);
}

void treeDelete(tipoNo* raiz, tipoNo* objetivo) { // (4) remocao
  tipoNo* y = NULL;
  if (objetivo->esq == NULL)
    transplant(raiz, objetivo, objetivo->dir);
  else if (objetivo->dir == NULL)
    transplant(raiz, objetivo, objetivo->esq);
  else { 
    y = treeMinimum(objetivo->dir);
    if (y->pai != objetivo) {
      transplant(raiz, y, y->dir);
      y->dir = objetivo->dir;
      y->dir->pai = y;
    }
    transplant(raiz, objetivo, y);
    y->esq = objetivo->esq;
    y->esq->pai = y;
  }
}

void treeInsert(tipoNo* raiz, tipoNo* z) { // (3) insercao
  tipoNo* y = NULL;
  tipoNo* x = raiz;

  while (x != NULL) {
    y = x;
    if (z->chave < x->chave) 
      x = x->esq;
    else x = x->dir;
  }
  z->pai = y;
  if (y == NULL) 
    raiz = z;
  else if (z->chave < y->chave)
    y->esq = z;
  else y->dir = z;
}

tipoNo* treeSearch(tipoNo* x, int k) { // (2) pesquisa
  if (x == NULL || k == x->chave)
    return x;
  if (k < x->chave)
    return treeSearch(x->esq, k);
  else return treeSearch(x->dir, k);
}

tipoNo* inicializarNo(int chave) { // (1) inicializacao
  tipoNo* ret = (tipoNo*) malloc(sizeof(tipoNo));

  ret->pai = NULL;
  ret->esq = NULL;
  ret->dir = NULL;
  ret->chave = chave;
  return ret;
}

int main() {
  int c, key = 0;

  tipoNo* raiz = NULL;
  while (1) {
    scanf(" %d", &c);
    if (c < 0) break;
    if (key == 0) { // primeiro elemento inserido
      raiz = inicializarNo(c); 
      key = 1;
    } else  // chama funcao de insercao 
      treeInsert(raiz, inicializarNo(c));
  } 
  scanf("%d", &c);
  int tam, altura;

  tam = getTamanhoArvore(raiz);
  altura = getAlturaArvore(raiz);
  printf("%d %d\n", tam, altura);

  tipoNo* p = NULL;
  p = treeSearch(raiz, c);
  if (p != NULL) // verifica a existencia da entrada na arvore
    if (p == raiz)
      raiz = NULL;
    else
      treeDelete(raiz, p);
  else
    if (raiz == NULL)
      raiz = inicializarNo(c);
    else {
      p = inicializarNo(c);
      treeInsert(raiz, p);
    }

  tam = getTamanhoArvore(raiz);
  altura = getAlturaArvore(raiz);
  printf("%d %d\n", tam, altura);

  // desalocar memoria
  desalocarArvore(raiz);
  free(p); free(raiz);
  return 0;
}
