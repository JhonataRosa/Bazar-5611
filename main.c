#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


#define CLIENTES 10
#define VOLUNTARIOS 10

int contCliente;
int contVolun;
int contador;



//CRIA ROUPA
typedef struct {
    int cod;
    char modelo;
    int preco;
    char tamanho;
 
}Roupa;

//LISTA DE ROUPAS A VENDA
Roupa *roupasD[50];
//LISTA DE ROUPAS PARA REPARO
Roupa *roupasR [20];

pthread_mutex_t mutexDisponiveis;
pthread_mutex_t mutexReparos;



//REALOCA A LISTA DE ROUPAS A VENDA APÓS ALGUMA VENDA
void realocaRoupasD() {
     for (int i = 1; i < sizeof(roupasD); i++) {
       if (roupasD[i-1] == NULL) {
     roupasD[i-1] = roupasD[i];
       }
     }
}

//REALOCA A LISTA DE ROUPAS EM REPARO APÓS ALGUMA TRANSFERENCIA
void realocaRoupasR() {
     for (int i = 1; i < sizeof(roupasR); i++) {
     roupasR[i-1] = roupasR[i];
     }
}

//CRIA AS ROUPAS E COLOCA NA LISTA PRA VENDAS
void criaRoupasD() {
  for (int i=0; i < 20; i++) {
  Roupa roupa;
  roupa.cod = contador;
  contador++;
  roupa.preco = rand() % 100;
    int sort = rand() % 4;
    switch (sort)
{
   case 0:
     roupa.modelo = "camisa";
   break;

   case 1:
     roupa.modelo = "bermuda";
   break;

   case 2:
     roupa.modelo = "calca";
   break;

   case 3:
     roupa.modelo = "moletom";
   break;

   case 4:
     roupa.modelo = "saia";
   break;
}

int sort2 = rand() % 4;
    switch (sort2)
{
   case 0:
     roupa.tamanho = "PP";
   break;

   case 1:
     roupa.tamanho = "P";
   break;

   case 2:
     roupa.tamanho = "M";
   break;

   case 3:
     roupa.tamanho = "G";
   break;

   case 4:
     roupa.tamanho = "GG";
   break;
}

*roupasD[i] = roupa;
  }

  for (int j =20; j < 50; j++) {
    roupasD[j] = NULL;
  }
}

//CRIA AS ROUPAS E COLOCA NA LISTA PRA REPAROS
void criaRoupasR() {
  for (int i=0; i < 10; i++) {
  Roupa roupa;
  roupa.cod = contador;
  contador++;
  roupa.preco = rand() % 100;
    int sort = rand() % 4;
    switch (sort)
{
   case 0:
     roupa.modelo = "camisa";
   break;

   case 1:
     roupa.modelo = "bermuda";
   break;

   case 2:
     roupa.modelo = "calca";
   break;

   case 3:
     roupa.modelo = "moletom";
   break;

   case 4:
     roupa.modelo = "saia";
   break;
}

int sort2 = rand() % 4;
    switch (sort2)
{
   case 0:
     roupa.tamanho = "PP";
   break;

   case 1:
     roupa.tamanho = "P";
   break;

   case 2:
     roupa.tamanho = "M";
   break;

   case 3:
     roupa.tamanho = "G";
   break;

   case 4:
     roupa.tamanho = "GG";
   break;
}

*roupasR[i] = roupa;

 for (int j =10; j < 20; j++) {
    roupasR[j] = NULL;
  }
  }
}

/////////////////CLIENTESSSSSS

void clienteCompra () {
   printf("Cliente %d está comprando a roupa %d\n", contCliente, roupasD[0]->cod);
   roupasD[0] = NULL;
   realocaRoupasD();
}

void clienteDoa () {
   for (int i = 0; i < 20; i++) {
   if (roupasR[i] == NULL){
  Roupa roupa;
  roupa.cod = contador;
  contador++;
  roupa.preco = rand() % 100;
    int sort = rand() % 4;
    switch (sort)
{
   case 0:
     roupa.modelo = "camisa";
   break;

   case 1:
     roupa.modelo = "bermuda";
   break;

   case 2:
     roupa.modelo = "calca";
   break;

   case 3:
     roupa.modelo = "moletom";
   break;

   case 4:
     roupa.modelo = "saia";
   break;
}

int sort2 = rand() % 4;
    switch (sort2)
{
   case 0:
     roupa.tamanho = "PP";
   break;

   case 1:
     roupa.tamanho = "P";
   break;

   case 2:
     roupa.tamanho = "M";
   break;

   case 3:
     roupa.tamanho = "G";
   break;

   case 4:
     roupa.tamanho = "GG";
   break;
}
  *roupasR[i] = roupa;
  printf("Cliente %d está doando uma roupa com o codigo %d\n", contCliente, contador);
  break;
   }
   }
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

void voluntarioMove () {
  
  for (int i =0; i < sizeof(roupasD);i++) {
    if (roupasD[i] == NULL) {
      int temp = rand() % sizeof(roupasR);
      printf("Voluntario %d está movendo a roupa %d\n", contVolun, roupasR[temp]->cod);
      roupasD[i] = roupasR[temp];
      roupasR[temp] = NULL;
      realocaRoupasR();
    }
  }
}

void voluntarioDoa () {
  for (int i = 0; i < 50; i++) {
   if (roupasD[i] == NULL){
  printf("Voluntario %d está doando uma roupa %d\n", contVolun, contador);
  Roupa roupa;
  roupa.cod = contador;
  contador++;
  roupa.preco = rand() % 100;
    int sort = rand() % 4;
    switch (sort)
{
   case 0:
     roupa.modelo = "camisa";
   break;

   case 1:
     roupa.modelo = "bermuda";
   break;

   case 2:
     roupa.modelo = "calca";
   break;

   case 3:
     roupa.modelo = "moletom";
   break;

   case 4:
     roupa.modelo = "saia";
   break;
}

int sort2 = rand() % 4;
    switch (sort2)
{
   case 0:
     roupa.tamanho = "PP";
   break;

   case 1:
     roupa.tamanho = "P";
   break;

   case 2:
     roupa.tamanho = "M";
   break;

   case 3:
     roupa.tamanho = "G";
   break;

   case 4:
     roupa.tamanho = "GG";
   break;
}
  *roupasD[i] = roupa;
  break;
   }
  }
}

void voluntarioRemove () {
  printf("Voluntario %d está removendo a roupa %d\n", contVolun, roupasD[0]->cod);
  roupasD[0] = NULL;
   realocaRoupasD();
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
  printf("Hello World\n");

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