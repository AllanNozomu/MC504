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
  for (int i = 0 ; i < 10 ; ++i)
  {
    fila_adiciona(i);
  }
  for (int i = 0 ; i < 5 ; ++i)
  {
    fila_remove();
  }
  for (int i = 0 ; i < 10 ; ++i)
  {
    fila_adiciona(i);
  }
  for (int i = 0 ; i < 11 ; ++i)
  {
    fila_remove();
  }

  return 0;
}