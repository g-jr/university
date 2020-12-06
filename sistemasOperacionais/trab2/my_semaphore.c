#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>

#define PROCESSO '1'
#define RECURSO '0'
// -------------------------------------------------------- //
struct Noh {
  void *id;
  char tipo; // tipo: '0' recurso e '1' processo
  struct Noh* prox;
};
typedef struct Noh TNoh;

struct Lista {
  struct Noh *head;
  struct Lista *prox;
};
typedef struct Lista TLista;

struct Grafo {
  struct Lista **lista;
};
typedef struct Grafo TGrafo;

TGrafo* iniciarGrafo() {
  TGrafo *temp = (TGrafo*) malloc(sizeof(TGrafo));
  temp->lista = (TLista**) malloc(sizeof(TLista*));
  return temp;
}

void inserirNo(TGrafo **aux, void *val, char tipo) {
  if (!*aux) return;
  TLista **temp = (*aux)->lista;
  while (*temp)
    temp = &(*temp)->prox;
  *temp = (TLista*) malloc(sizeof(TLista));
  (*temp)->head = (TNoh*) malloc(sizeof(TNoh));
  (*temp)->head->id = val;
  (*temp)->head->tipo = tipo;
}

TNoh* pesquisarNo(TGrafo **aux, void *id) {
  if (!*aux || !*(*aux)->lista) return NULL;
  TLista **curr = (*aux)->lista;
  do {
    if ((*curr)->head->id == id) {
      return (*curr)->head;
    }
    curr = &(*curr)->prox;
  } while (*curr);
  return NULL;
}

void inserirVertice(TNoh *u, TNoh *v) {
  if (!u || !v) return; 
  if (u->tipo != v->tipo && u->prox == NULL)
    u->prox = v;
}

int verificarCiclo(TNoh *aux) {
  if (!aux) return 0;
  printf("inicio - verificacao ciclo.\n");
  if (aux->tipo == PROCESSO)
    printf("id(processo): %ld\n", *(pthread_t*)aux->id);
  else
    printf("id(recurso): %p\n", aux->id);

  TNoh *temp = aux->prox;
  while (temp) {
    if (temp->tipo == PROCESSO)
      printf("id(processo): %ld\n", *(pthread_t*)temp->id);
    else
      printf("id(recurso): %p\n", temp->id);
    if (temp->id == aux->id) {
      printf("final - clico detectado.\n");
      return 1;
    }
    temp = temp->prox;
  }
  printf("final - ciclo nao detectado.\n\n");
  return 0;
}

void removerConexao(TNoh *aux) {
  if (aux)
    aux->prox = NULL;
}

void removerNo(TGrafo **aux, void *id) {
  if (!aux) return;
  TLista *temp = NULL;
  if ((*(*aux)->lista)->head->id == id) {
    temp = *(*aux)->lista;
    if ((*(*aux)->lista)->prox)
      *(*aux)->lista = (*(*aux)->lista)->prox;
    else
      (*aux)->lista = NULL;
  } else {
    TLista **curr = &(*(*aux)->lista)->prox;
    do {
      if ((*curr)->head->id == id) {
        temp = *curr;
        if ((*curr)->prox) {
          if ((*curr)->prox)
            *curr = (*curr)->prox;
          else
            *curr = NULL;
        }
        break;
      }
      curr = &(*curr)->prox; 
    } while (*curr);
  }
  if (temp) {
    free((temp)->head);
    free(temp);
  }
}
// -------------------------------------------------------- //

TGrafo *g = NULL;
sem_t mutex;
int (*_sem_init) (sem_t *, int, unsigned int) = NULL;
int (*_sem_wait) (sem_t *) = NULL;
int (*_sem_post) (sem_t *) = NULL;

// -------------------------------------------------------- //
void downMutex() {
  _sem_wait(&mutex);
}

void upMutex() {
  _sem_post(&mutex);
}
// -------------------------------------------------------- //

int sem_init(sem_t *sem, int pshared, unsigned int value) {
  if (!_sem_init) {
    _sem_init = dlsym(RTLD_NEXT, "sem_init");
		_sem_wait = dlsym(RTLD_NEXT, "sem_wait");
    _sem_post = dlsym(RTLD_NEXT, "sem_post");
  }
  _sem_init(&mutex, 0, 1);
  downMutex();
  if (!g)
    g = iniciarGrafo();
  if (!pesquisarNo(&g, sem))
    inserirNo(&g, sem, RECURSO);
  upMutex();
  int r;
  r = _sem_init(sem, pshared, value);
  return r;
}

int sem_wait(sem_t *sem) {
  downMutex();
  pthread_t id = pthread_self();
  TNoh *u, *v;
  inserirNo(&g, &id, PROCESSO);
  u = pesquisarNo(&g, sem);
  v = pesquisarNo(&g, &id);
  inserirVertice(v, u); // add vertice de requisicao ao recurso
  if (verificarCiclo(u)) { // verificar se ocorre deadlock
    removerConexao(v); // oq fazer aqui
    removerNo(&g, v);
    upMutex();
    perror("\nDeadlock detectado.\nPrograma finalizado.");
    exit(0);
  }
  upMutex();
	int r;
	r = _sem_wait(sem);
  downMutex();
  removerConexao(v);
  inserirVertice(u, v);
  upMutex();
	return r;
}

int sem_post(sem_t *sem) {
  downMutex();
  pthread_t id = pthread_self();
  TNoh *temp = pesquisarNo(&g, sem);
  removerConexao(temp); // remove a alocacao do recurso por esse processo
  removerNo(&g, &id);
  upMutex();
  int r;
  r = _sem_post(sem);
  return r;
}
