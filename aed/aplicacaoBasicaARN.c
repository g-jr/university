#include <stdio.h>
#include <stdlib.h>

typedef int TChave;

typedef struct {
	TChave Chave;
	/* outros compomentes */
} TItem; 

typedef struct SNo *TArvBin;

typedef struct SNo {
	TItem Item;
	TArvBin Esq, Dir;
} TNo;

int altura(TArvBin aux) { 
  int esq, dir;
  if (aux == NULL)
    return 0;
  esq = altura(aux->Esq);
  dir = altura(aux->Dir);

  if (esq > dir)
    return esq + 1;
  else
    return dir + 1;
}

// (2) FB: retorna of fator de balanceamento de um dado noh
int getFb(TArvBin aux) {   
  int ret = altura(aux->Esq) - altura(aux->Dir);
  return ret;
}

void atualizaFb(TArvBin aux) {
  if (aux == NULL)
    return;
  atualizaFb(aux->Esq);
  atualizaFb(aux->Dir);
  aux->Item.fb = getFb(aux);
}

void RR(TArvBin &pA) {
  TArvBin pB = pA->Dir;
  pA->Dir = pB->Esq;
  pB->Esq = pA;
  pA = pB;
}

void LL(TArvBin &pA) {
  TArvBin pB = pA->Esq;
  pA->Esq = pB->Dir;
  pB->Dir = pA;
  pA = pB;
}
void LR(TArvBin &pA) {
  TArvBin pB = pA->Esq;
  TArvBin pC = pB->Dir;
  pB->Dir = pC->Esq;
  pC->Esq = pB;
  pA->Esq = pC->Dir;
  pC->Dir = pA;
  pA = pC;
}
void RL(TArvBin &pA) {
  TArvBin pB = pA->Dir;
  TArvBin pC = pB->Esq;
  pB->Esq = pC->Dir;
  pC->Dir = pB;
  pA->Dir = pC->Esq;
  pC->Esq = pA;
  pA = pC;
}

void insere(TArvBin Raiz, TArvBin Elem) {
  TArvBin aux;
  if (Raiz->Item.Chave > Elem->Item.Chave) {
    if (Raiz->Esq) {
      insere(Raiz->Esq, Elem);
    }
    else 
      Raiz->Esq = Elem;
  } else {
    if (Raiz 
  }
}

TArvBin inicializa() {
  int n, temp;
  scanf("%d", &n);
  while (n--) {
    scanf("%d", &temp);
  }
}

void Imprime(TArvBin No) {
	if (No != NULL) {
		printf("(C%d", No->Item.Chave);
		Imprime(No->Esq);
		Imprime(No->Dir);
		printf(")");
	}
	else
		printf("()");
}

// (1) inicializacao

// (2) pesquisa

// (3) insercao

// (4) remocao

int main() {
	TArvBin Raiz;
	TItem x;
  Raiz = inicializa();

	Imprime(Raiz); //imprime arvore final balanceada
  // criar funcao para desalocar
	return 0;
}
