#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

queue fila;

void fila_adiciona(int val){
  if (queue_is_full(fila)){
    printf("A fila está cheia\n");
    return;
  }
  printf("%d entrou na fila\n", val);
  queue_add(&fila, val);
}

void fila_remove(){
  if (queue_is_empty(fila)){
    printf("A fila está vazia\n");
    return;
  }
  int val = queue_remove(&fila);
  printf("%d saiu na fila\n", val);

}

int main()
{
  queue_init(&fila, 10);
  fila_adiciona(0);
  printf("Tamanho da lista %d\n", queue_length(fila));
  printf("Elemento da lista %d\n", queue_status(fila, 0));
  for (int i = 0 ; i < 10 ; ++i)
  {
    fila_adiciona(i);
  }
  printf("Tamanho da lista %d\n", queue_length(fila));
  for (int i = 0 ; i < 5 ; ++i)
  {
    printf("Elemento em %d da lista %d\n",i, queue_status(fila, i));
  }
  for (int i = 0 ; i < 5 ; ++i)
  {
    fila_remove();
  }
   printf("Tamanho da lista %d\n", queue_length(fila));
  for (int i = 0 ; i < 10 ; ++i)
  {
    fila_adiciona(i);
  }
  for (int i = 0 ; i < 5 ; ++i)
  {
    printf("Elemento em %d da lista %d\n",i, queue_status(fila, i));
  }
   printf("Tamanho da lista %d\n", queue_length(fila));
  for (int i = 0 ; i < 11 ; ++i)
  {
    fila_remove();
  }
   printf("Tamanho da lista %d\n", queue_length(fila));

  return 0;
}
