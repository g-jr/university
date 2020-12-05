/* Gaspar Andrade – 133633
 * UC: AED2  Prof Dr. Alvaro Luiz Fazenda
 * Tarefa 07 - Pesquisa Interna - Rotacoes AVL
 */
#include <iostream>
#include <stack>
#include <cstdio>
#include <cstdlib>

typedef int TChave;

typedef struct {
	TChave Chave;
  int fb;
} TItem; 

typedef struct SNo *TArvBin;

typedef struct SNo {
	TItem Item;
	TArvBin Esq, Dir;
} TNo;

TArvBin Carrega() {
	char c;
	TArvBin No;
	scanf("%c", &c);
	if (c == '(') {
		scanf("%c", &c);
		if (c == 'C') {
			No = (TArvBin) malloc(sizeof(TNo));
			scanf("%d", &No->Item.Chave);
			No->Esq = Carrega();
			No->Dir = Carrega();
			scanf("%c", &c);
		}
		else if (c == ')')
			No = NULL;
	}
	return No;
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

// (1) Altura: retorna a altura de um dado no
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

// (3) ArvoreAVL: verifica se uma arvore eh ou nao AVL
bool arvoreAVL(TArvBin aux) { 
  if (aux == NULL)
    return 0;

  TArvBin temp = aux;
  std::stack<TArvBin> s;
  int temp2 = 0;
  while (temp != NULL || s.empty() == false) {
    while (temp != NULL) {
      s.push(temp);
      temp = temp->Esq;
    }
    temp = s.top();
    s.pop();
    temp2 = temp->Item.fb;
    if (std::abs(temp2) > 1)
      return false;
    temp = temp->Dir;
  }
  return true;
}

// (4) LL, RR, LR, RL: executa uma rotacao em um dado noh
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

// (5) BalancaNo: verifica um dado noh e efetua o seu balanceamento, caso necessario
void balancaNo(TArvBin &aux) {
  if (std::abs(aux->Item.fb) < 1)
    return;
  if (aux->Item.fb < -1) { // pode ser RR ou RL
    if (aux->Dir->Item.fb < 0) {
      std::cout << "RR\n";
      RR(aux);
    } else {
      std::cout << "RL\n"; 
      RL(aux);
    }
  }
  else {
    if (aux->Esq->Item.fb > 0) {
      std::cout << "LL\n";
      LL(aux);
    } else {
      LR(aux);
      std::cout << "LR\n";
    }
  }
}

int main() {
	TArvBin Raiz;
	TItem x;
  int alturaArvore;
	Raiz = Carrega(); //le arvore binaria inicial com parenteses aninhados
  alturaArvore = altura(Raiz); // pega altura atual da arvore
  printf("%d\n", alturaArvore - 1); // imprime altura atual
	Imprime(Raiz); //imprime arvore inicial
  printf("\n");
  
  // procedimentos para atualizar a arvore
  atualizaFb(Raiz);
  if (arvoreAVL(Raiz) == false) { // caso a arvore nao esteja balanceada
    balancaNo(Raiz);
  }

  alturaArvore = altura(Raiz); // pega altura da arvore balanceada
  printf("%d\n", alturaArvore - 1); // imprime arvore final balanceada
	Imprime(Raiz); //imprime arvore inicial
	return 0;
}
