#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


#define CLIENTES 10
#define VOLUNTARIOS 10


int contCliente=1;
int contVolun=1;
int contador=1;



//CRIA ROUPA
typedef struct {
    int cod;
    char modelo[10];
    int preco;
    char tamanho[2];
 
}Roupa;

//LISTA DE ROUPAS A VENDA
Roupa roupasD[50];
//LISTA DE ROUPAS PARA REPARO
Roupa roupasR [20];

pthread_mutex_t mutexDisponiveis;
pthread_mutex_t mutexReparos;
pthread_mutex_t mutexContador;




//METODO QUE CRIA UMA ROUPA COM ATRIBUTOS ALEATORIOS
Roupa criaRoupa() {
Roupa roupa;
  pthread_mutex_lock(&mutexContador);
  roupa.cod = contador;
  contador++;
  pthread_mutex_unlock(&mutexContador);
  roupa.preco = rand() % 100;
    int sort = rand() % 4;
    switch (sort)
{
   case 0:
    
    strcpy(roupa.modelo, "camisa"); 
   break;

   case 1:
     strcpy(roupa.modelo, "bermuda");
   break;

   case 2:
     strcpy(roupa.modelo, "calca");
   break;

   case 3:
     strcpy(roupa.modelo, "moletom");
   break;

   case 4:
     strcpy(roupa.modelo, "saia");
   break;
}

int sort2 = rand() % 4;
    switch (sort2)
{
   case 0:
     strcpy(roupa.tamanho, "PP");
   break;

   case 1:
     strcpy(roupa.tamanho, "P");
   break;

   case 2:
     strcpy(roupa.tamanho, "M");
   break;

   case 3:
     strcpy(roupa.tamanho, "G");
   break;

   case 4:
      strcpy(roupa.tamanho, "GG");
   break;
}
return roupa;
}

Roupa criaRoupaFalsa() {
  Roupa roupa;
  roupa.cod=0;
  return roupa;
}

//CRIA UMA LISTA DE ROUPAS E VENDA
void criaRoupasD() {
  for (int i=0; i < 20; i++) {
roupasD[i] = criaRoupa();
  }
  for (int j =20; j < 50; j++) {
    roupasD[j] = criaRoupaFalsa();
  }
}


//CRIA UMA LISTA DE ROUPAS PARA REPARO
void criaRoupasR() {
  for (int i=0; i < 10; i++) {
  roupasR[i] = criaRoupa();

 for (int j =10; j < 20; j++) {
    roupasR[j] = criaRoupaFalsa();
  }
  }
}


//REALOCA A LISTA DE ROUPAS A VENDA, APÓS ALGUMA VENDA
void realocaRoupasD() {
  pthread_mutex_lock(&mutexDisponiveis);
     for (int i = 1; i < sizeof(roupasD); i++) {
       if (roupasD[i-1].cod != 0) {
     roupasD[i-1] = roupasD[i];
       }
     }
  pthread_mutex_unlock(&mutexDisponiveis);
}

//REALOCA A LISTA DE ROUPAS EM REPARO APÓS ALGUMA TRANSFERENCIA
void realocaRoupasR() {
  pthread_mutex_lock(&mutexReparos);
     for (int i = 1; i < sizeof(roupasR); i++) {
     if (roupasR[i-1].cod == 0) {
     roupasR[i-1] = roupasR[i];
       }
}
  pthread_mutex_unlock(&mutexReparos);
}

/////////////////CLIENTESSSSSS

//CLIENTE COMPRA A ROUPA DA PRIMEIRA POSICAO
void clienteCompra() {
  pthread_mutex_lock(&mutexDisponiveis);
   printf("Cliente %d está comprando a roupa %d\n", contCliente, roupasD[0].cod);
   contCliente++;
    roupasD[0] = criaRoupaFalsa();
  pthread_mutex_unlock(&mutexDisponiveis);
   realocaRoupasD();
}

//CLIENTE DOA UMA ROUPA PARA A LISTA DE REPAROS
void clienteDoa () {
  pthread_mutex_lock(&mutexReparos);
   for (int i = 0; i < 20; i++) {
   if (roupasR[i].cod == 0 ){
  roupasR[i] = criaRoupa();
  printf("Cliente %d está doando uma roupa com o codigo %d\n", contCliente, contador);
  contCliente++;
  break;
   }
   }
  pthread_mutex_unlock(&mutexReparos); 
}

void *t_clientes (void *arg) {
  int sort = rand() %1;
  if (sort == 0) {
  clienteCompra();
  }
  else {
  clienteDoa();
  }
  pthread_exit(NULL);
}

//VOLUNTARIO MOVE UMA ROUPA DE POSICAO ALEATORIA PARA A LISTA DE DISPONIVEIS
void voluntarioMove () {
  pthread_mutex_lock(&mutexDisponiveis);
  for (int i =0; i < sizeof(roupasD);i++) {
    if (roupasD[i].cod == 0) {
      pthread_mutex_lock(&mutexReparos);
      int temp = rand() % sizeof(roupasR);
      printf("Voluntario %d está movendo a roupa %d\n", contVolun, roupasR[temp].cod);
      contVolun++;
      roupasD[i] = roupasR[temp];
      pthread_mutex_unlock(&mutexDisponiveis);
      roupasR[temp] = criaRoupaFalsa();
      realocaRoupasR();
      pthread_mutex_unlock(&mutexReparos);
    }
  }
}

//VOLUNTARIO DOA UMA ROUPA PARA A LISTA DE DISPONIVEIS
void voluntarioDoa () {
  pthread_mutex_lock(&mutexDisponiveis);
  for (int i = 0; i < 50; i++) {
   if (roupasD[i].cod == 0){
  printf("Voluntario %d está doando uma roupa %d\n", contVolun, contador);
  contVolun++;
  roupasD[i] = criaRoupa();
  break;
   }
  }
  pthread_mutex_unlock(&mutexDisponiveis);
}

//VOLUNTARIO REMOVE A ROUPA MAIS ANTIGA, DAS DISPONIVEIS
void voluntarioRemove () {
  pthread_mutex_lock(&mutexDisponiveis);
  printf("Voluntario %d está removendo a roupa %d\n", contVolun, roupasD[0].cod);
  contVolun++;
  roupasD[0].cod = 0;
   realocaRoupasD();
   pthread_mutex_unlock(&mutexDisponiveis);
}

void *y_voluntarios (void *arg) {
  
  int sort = rand() % 2;
  switch (sort) {
    case 0:
    voluntarioDoa();
    break;

    case 1:
    voluntarioMove();
    break;

    case 2:
    voluntarioRemove();
    break;
  }
  pthread_exit(NULL); 
}

int main(void) {
  printf("VAII\n");
  criaRoupasD();
  criaRoupasR();
  

  pthread_t t[CLIENTES];
	pthread_t y[VOLUNTARIOS];
	pthread_mutex_init(&mutexDisponiveis, NULL);
	pthread_mutex_init(&mutexReparos, NULL);

  for (int i = 0; i < CLIENTES + VOLUNTARIOS; i++){
	printf("Thread %d sendo criada\n",i);
		pthread_create(&t[i], NULL, t_clientes, NULL);
		pthread_create(&y[i], NULL, y_voluntarios, NULL);
	}

  printf("Aguardando término das threads\n");

	for (int i = 0; i < CLIENTES + VOLUNTARIOS; i++){
		pthread_join(t[i],NULL);
		pthread_join(y[i],NULL); 
	}

  return 0;
}