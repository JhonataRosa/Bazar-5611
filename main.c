#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


#define CLIENTES 15
#define VOLUNTARIOS 10

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

//REALOCA A LISTA DE ROUPAS A VENDA APÓS ALGUMA VENDA
void realocaRoupasD() {
     for (int i = 1; i < 50; i++) {
       if (roupasD[i-1] == NULL) {
     roupasD[i-1] = roupasD[i];
       }
     }
}

//REALOCA A LISTA DE ROUPAS EM REPARO APÓS ALGUMA TRANSFERENCIA
void realocaRoupasR() {
     for (int i = 1; i < 20; i++) {
     roupasR[i-1] = roupasR[i];
     }
}

//CRIA AS ROUPAS E COLOCA NA LISTA PRA VENDAS
void criaRoupasD() {
  for (int i=0; i < 20; i++) {
  Roupa roupa;
  roupa.cod = 100+i;
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
  roupa.cod = 300+i;
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

//CLIENTE COMPRA ROUPA DA LISTA DE VENDAS
void *clienteCompra (void *arg) {
   roupasD[0] = NULL;
}

void *clienteDoa (void *arg) {
   for (int i = 0; i < 20; i++) {
   if (roupasR[i] == NULL){

   }
   
   }
}

int main(void) {
  printf("Hello World\n");
  return 0;
}