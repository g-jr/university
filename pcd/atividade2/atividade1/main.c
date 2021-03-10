#include <stdio.h>
#include <pthread.h>
#include <time.h>
#define NUM_THREADS 4

struct targs{
        int id;
        //int usec;
        int i;
};

typedef struct targs targs_t;

long contador; // Variável global que se deseja incrementar
long local; // Variável local dos clientes
long response;
long request;



void cliente(void* i){
    targs_t ta = *(targs_t *)i;
	long aux = (long) i;
	long j;


	for(j = 0; j < local; j++) {
		while(response != aux){request = aux;}
		printf("Thread Cliente[%d] executando, incrementando 1 no valor do contador = %d\n",ta.id,contador);
		contador++; // seção crítica
		response = 0;
	}
	pthread_exit(NULL);
}

void servidor(void * i){
	while(1){
        printf("Thread Servidor executando\n");
		while(request == 0){}
		response = request;
		while(response != 0){}
		request = 0;
	}
	pthread_exit(NULL);
}



int main(void){

	pthread_t clients[NUM_THREADS];
	targs_t ta[NUM_THREADS]; //Estrutura com dados
	pthread_t t_server;
	clock_t tempo;
	tempo = clock();
	contador = 0;
	long i;
    long N;
	N = 1000000; // numero de interações

    request = 0;
	response = 0;
    local = N / NUM_THREADS; // numero de interações de cada thread


	pthread_create(&t_server, NULL, servidor, NULL); // Cria thread do servidor
	for(i = 1; i <= NUM_THREADS; i++){
        ta[i].id = i;
        ta[i].i = NUM_THREADS;
		pthread_create(&clients[i-1], NULL, cliente, (void*)&ta[i]); //Cria threads Clients
	}

	for(i = 0; i < NUM_THREADS; i++){
		pthread_join(clients[i], NULL); // Sincroniza, espera as threads rodarem para continuar a execução
	}

	printf("cont = %ld\n", contador);
	printf("Tempo:%f",(clock() - tempo) / (double)CLOCKS_PER_SEC);
	return 0;
}


