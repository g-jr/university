/* Gaspar Andrade – 133633
 * UC: AED2 Prof. Alvaro Luiz Fazenda
 * Tarefa 09 - Insercao e Remocao em Arvores Rubro-Negras
 * 1. Semestre de 2020
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>

typedef int TChave;
typedef struct {
	TChave Chave;
} TItem;

typedef struct SNo *TArvBin;

typedef struct SNo {
	TItem Item;
	TArvBin Esq, Dir;
	int cor;
  SNo(int);
} TNo;

SNo::SNo(int chave) {
  Item.Chave = chave;
  cor = 1;
  Esq = Dir = NULL;
}

int EhNegro(TArvBin No) {
	return (No == NULL) || (No->cor == 0);
}

int EhRubro(TArvBin No) {
	return (No != NULL) && (No->cor == 1);
}

void leftRotate(TArvBin &pA) {
  TArvBin pB = pA->Dir;
  pA->Dir = pB->Esq;
  pB->Esq = pA;
  pA = pB;
}

void rightRotate(TArvBin &pA) {
  TArvBin pB = pA->Esq;
  pA->Esq = pB->Dir;
  pB->Dir = pA;
  pA = pB;
}

int alturaRN(TArvBin aux) {
  if (!aux)
    return 0;
  int esq, dir;
  esq = alturaRN(aux->Esq);
  dir = alturaRN(aux->Dir);
  if (esq > dir) // retorna a ramificacao de maior altura e se o noh atual for negro add +1
    return EhNegro(aux->Esq) ? esq + 1 : esq;
  else
    return EhNegro(aux->Dir) ? dir + 1 : dir;
}

void fixRaiz(TArvBin &raiz) {
  int esq, dir;
  esq = alturaRN(raiz->Esq);
  dir = alturaRN(raiz->Dir);
  if (esq > dir) {
    raiz->Esq->cor = 0;
    raiz->cor = 1;
    rightRotate(raiz); 
  } else if (esq < dir) {
    raiz->Dir->cor = 0;
    raiz->cor = 1;
    leftRotate(raiz);
  }
}

void rbInsertFixUp(TArvBin &raiz, TArvBin &z, TArvBin &pai, TArvBin &avo) {
  TArvBin *tio = NULL;
  if (raiz && avo && EhRubro(z) && EhRubro(pai)) {
    if (pai == avo->Esq) {
      tio = &avo->Dir;
      if (*tio && EhRubro(*tio)) { // caso 1
        pai->cor = 0;
        (*tio)->cor = 0;
        avo->cor = 1;
      } else {
        if (z == pai->Dir) // caso 2
          leftRotate(pai);
      pai->cor = 0;
      avo->cor = 1;
      if (avo == raiz) rightRotate(raiz);
      else rightRotate(avo);
      }
    } else if (pai == avo->Dir) {
      tio = &avo->Esq;
      if (*tio && EhRubro(*tio)) { // caso 1
        pai->cor = 0;
        (*tio)->cor = 0;
        avo->cor = 1;
      } else {
        if (z == pai->Esq) // caso 2
          rightRotate(pai);
        pai->cor = 0;
        avo->cor = 1;
        if (avo == raiz) leftRotate(raiz);
        else leftRotate(avo);
      }
    } 
  }
  raiz->cor = 0;
}

void rbInsert(TArvBin &raiz, TArvBin &novo, TArvBin &pai, TArvBin &avo) {
  if (!pai) {
    pai = novo;
    if (pai == raiz)
      raiz->cor = 0;
    return;
  }
  if (pai->Item.Chave > novo->Item.Chave) {
    rbInsert(raiz, novo, pai->Esq, pai);
    rbInsertFixUp(raiz, pai->Esq, pai, avo);
  } else if (pai->Item.Chave < novo->Item.Chave) {
    rbInsert(raiz, novo, pai->Dir, pai);
    rbInsertFixUp(raiz, pai->Dir, pai, avo);
  }
  return;
}

TArvBin inicializacao() {
  TArvBin raiz = NULL, aux;
  int n, temp;
  scanf("%d", &n);
  while (n--) {
    scanf("%d", &temp);
    aux = new SNo{temp};
    rbInsert(raiz, aux, raiz, raiz);
  }
  return raiz;
}

void Imprime(TArvBin No) {
	if (No != NULL) {
		if (EhNegro(No))
			printf("(N%d", No->Item.Chave);
		else
			printf("(R%d", No->Item.Chave);
		Imprime(No->Esq);
		Imprime(No->Dir);
		printf(")");
	}
	else
		printf("()");
}

void removeNoFixUp(TArvBin &raiz, TArvBin &alvo, TArvBin &pai) {
  TArvBin *temp = NULL;
  if (pai) {
    if (alvo == pai->Esq) {
      temp = &pai->Dir;
      if (*temp)
        if (EhRubro(*temp)) { // caso (1)
          (*temp)->cor = 0;
          pai->cor = 1;
          if (pai == raiz) leftRotate(raiz);
          else leftRotate(pai);
          temp = &pai->Dir;
        }
        if (*temp) {
          if (EhNegro((*temp)->Esq) && EhNegro((*temp)->Dir)) // caso (2)
            (*temp)->cor = 1;
          else if (EhNegro((*temp)->Dir)) { // caso (3)
            (*temp)->Esq->cor = 0;
            (*temp)->cor = 1;
            rightRotate(*temp);
            temp = &pai->Dir;
          }
        } // caso (4)
        if (*temp)
          (*temp)->cor = pai->cor;
          pai->cor = 0;
        if ((*temp)->Dir)
          (*temp)->Dir->cor = 0;
        if (pai == raiz) leftRotate(raiz);
        else leftRotate(pai);
    } else { 
      temp = &pai->Esq;
      if (*temp)
        if (EhRubro(*temp)) { // caso (1)
          (*temp)->cor = 0;
          pai->cor = 1;
          if (pai == raiz) rightRotate(raiz);
          else rightRotate(pai);
          temp = &pai->Esq;
        }
      if (*temp) {
        if (EhNegro((*temp)->Esq) && EhNegro((*temp)->Dir)) // caso (2)
          (*temp)->cor = 1;
        else if (EhNegro((*temp)->Esq)) { // caso (3)
          (*temp)->Dir->cor = 0;
          (*temp)->cor = 1;
          leftRotate(*temp);
          temp = &pai->Esq;
        }
      } // caso (4)
      if (*temp) { 
        (*temp)->cor = pai->cor;
        pai->cor = 0;
        if ((*temp)->Esq)
        (*temp)->Esq->cor = 0;
        if (raiz == pai) rightRotate(raiz);
        else rightRotate(pai);
      }
    }
  }
  raiz->cor = 0;
}

TArvBin &sucessor(TArvBin &aux) {
  if (aux->Esq != NULL)
    return sucessor(aux->Esq);
  return aux;
}

void removeNo(TArvBin &raiz, TArvBin *alvo, TArvBin &pai) { // (4) remocao
  if (*alvo == NULL) // se o argumento passado for vazio retorna
    return;
 
  TArvBin temp = *alvo;
  if (!(*alvo)->Esq && !(*alvo)->Dir) // caso o no alvo nao tenha nenhum filho
    *alvo = NULL;
  else if ((*alvo)->Esq && (*alvo)->Dir) { // caso o no alvo tenha dois filhos
    TArvBin &temp1 = sucessor((*alvo)->Dir);
    (*alvo)->Item.Chave = temp1->Item.Chave;
    removeNo(raiz, &temp1, pai);
  } else if ((*alvo)->Esq) { // caso so tenha filho na esquerda
    *alvo = (*alvo)->Esq;
    (*alvo)->cor = temp->cor;
  }
  else if ((*alvo)->Dir) { // caso so tenha filho na direita
    *alvo = (*alvo)->Dir;
    (*alvo)->cor = temp->cor;
  }
  //delete temp;
}

void utilizarSucessor(TArvBin &raiz, TArvBin &alvo, TArvBin *aux, TArvBin *pai) {
  if (*aux == alvo) {
    return;
  }
  if ((*aux)->Item.Chave > alvo->Item.Chave) {
    utilizarSucessor(raiz, alvo, &(*aux)->Esq, aux);
    removeNoFixUp(raiz, (*aux)->Esq, *aux);
  } else {
    utilizarSucessor(raiz, alvo, &(*aux)->Dir, aux);
    removeNoFixUp(raiz, (*aux)->Dir, *aux);
  }
}

bool pesquisaNo(TArvBin &raiz, TArvBin &aux, int x, TArvBin *pai) {
  if (!aux)
    return false;

  bool temp = false;
  if (aux->Item.Chave == x) {
    if (EhNegro(aux))
      temp = true;
    removeNo(raiz, &aux, *pai);
    Imprime(raiz);
    if (*pai == raiz && (*pai)->Esq == NULL && (*pai)->Dir) {
      fixRaiz(raiz);
      TArvBin &temp1 = sucessor(raiz->Dir);
      utilizarSucessor(raiz, temp1, &raiz, NULL);
    }
    Imprime(raiz);
    if (*pai && aux && (*pai)->cor == 1) temp = false;
    return temp;
  }
  else if (aux->Item.Chave > x) {
    temp = pesquisaNo(raiz, aux->Esq, x, &aux);
    if (temp) removeNoFixUp(raiz, aux->Esq, aux);
  }
  else {
    temp = pesquisaNo(raiz, aux->Dir, x, &aux);
    if (temp) removeNoFixUp(raiz, aux->Dir, aux);
  }
  return false;
}

void libera(TArvBin &aux) {
  if (!aux)
    return;
  TArvBin temp;
  if (aux->Dir)
    libera(aux->Dir);
  if (aux->Esq)
    libera(aux->Esq);

  temp = aux;
  aux = NULL;
  delete temp;
}

int main(void) {
  TArvBin raiz;
  int valAltura;

  raiz = inicializacao();
  valAltura = alturaRN(raiz);
  printf("%d\n", valAltura);
  Imprime(raiz);
  // procedimentos
  int nohRemover;
  scanf("%d", &nohRemover);

  pesquisaNo(raiz, raiz, nohRemover, &raiz); // pesquisa o no e o remove

  valAltura = alturaRN(raiz);
  printf("\n%d\n", valAltura);
  Imprime(raiz);
  libera(raiz); // desaloca memoria da arvore
  return 0;
}
