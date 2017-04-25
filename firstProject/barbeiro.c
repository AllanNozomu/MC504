#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "queue.h"
#define MAX 1000

sem_t mutex;
sem_t sem_cadeira;
sem_t sem_acorda_barbeiro;
sem_t sem_cadeira_atendimento;
sem_t sem_cabelo_cortado;

queue fila;
queue filaDesistencia;
volatile int cortandoCabelo;
volatile int fim = 0;
int quantidadeCadeiras;
int quantidadeClientes;

pthread_t barbeiro;
pthread_t pintor;
pthread_t cliente[1000];
int ld[1000];

void paint() {
    clear();
    // sem_wait(&mutex);
    int tamanhoFila = queue_length(fila);
    if (cortandoCabelo >= 0) {
        printw("              &    Cliente %3d está cortando o cabelo\n", cortandoCabelo);
        printw("  '''''    &&&&\n");
        printw("  |o o     |o o\n");
        printw("  | °|    || ´|\n");
        printw("-======-  |XXXX\n");
        printw("  |  |    |XXXXX\n");
        printw("  |__|    |---|X\n");
        printw("  |  |    |   |´\n");
    } else {
        printw("         Z         Barbeiro está dormindo\n");
        printw("  ''''' z\n");
        printw("  |- -\n");
        printw("  | -|    |\n");
        printw("-======-  |\n");
        printw("  |  |    |\n");
        printw("  |__|    |---|\n");
        printw("  |  |    |   |\n");
    }
        printw("\n");
    int i;
    if (tamanhoFila > 0) {
        printw("Situação da fila:\n");
        for (i = 0 ; i < tamanhoFila && i < 9; ++i) {
            printw("  &&&&  ");
        }
        printw("\n");

        for (i = 0 ; i < tamanhoFila && i < 9; ++i) {
            printw("  &&&&  ");
        }
        printw("\n");

        for (i = 0 ; i < tamanhoFila && i < 9; ++i) {
            printw("  o o|  ");
        }
        printw("\n");

        for (i = 0 ; i < tamanhoFila && i < 9; ++i) {
            printw("  |´ |  ");
        }
        printw("\n");

        for (i = 0 ; i < tamanhoFila && i < 9; ++i) {
            printw("-XXXXXX-");
        }
        printw("\n");

        for (i = 0 ; i < tamanhoFila && i < 9; ++i) {
            printw("  XXXX  ");
        }
        printw("\n");

        for (i = 0 ; i < tamanhoFila && i < 9; ++i) {
            printw("  XXXX  ");
        }
        printw("\n");

        for (i = 0 ; i < tamanhoFila && i < 9; ++i) {
            printw("  |  |  ");
        }
        printw("\n");
        for (i = 0 ; i < tamanhoFila; ++i){
            printw("| %3d   ", queue_status(fila, i));
        }
        for (; i < quantidadeCadeiras; ++i){
            printw("| XXXXX ");
        }
        printw("\n");
    }else{
        printw("Sem fila\n");
    }
    printw("\n");
    printw("Desistiram de cortar o cabelo: ");
    int tamanhoFilaDesistencia = queue_length(filaDesistencia);

    for (i = 0 ; i < tamanhoFilaDesistencia; i++){
        printw("%2d ", queue_status(filaDesistencia, i));
    }
    printw("\n");
    if (fim)
        printw("Fim do programa, pressiona qualquer tecla para voltar ao terminal...\n");
    refresh();
}
void * f_cliente(void *var) {

    int id = *(int *) var;
    if(sem_trywait(&sem_cadeira) == 0) {                        //ocupa cadeira

        sem_wait(&mutex);
        queue_add(&fila, id);
        paint();
        sem_post(&mutex);

        // printf("Cliente %d senta e espera \n", id);
        sem_wait(&sem_cadeira_atendimento);                     //aguarda barbeiro
        sem_post(&sem_cadeira);                                 //libera cadeira
        sem_post(&sem_acorda_barbeiro);                         //eh atendido
        sem_wait(&sem_cabelo_cortado);                          //espera cortar cabelo

        // printf("Cliente %d cortou o cabelo.\n", id);
        sem_post(&sem_cadeira_atendimento);                     //barbeiro liberado

    } else {
        // printf("Cliente %d desistiu de cortar o cabelo.\n", id);
        sem_wait(&mutex);
        queue_add(&filaDesistencia, id);
        paint();
        sem_post(&mutex);
    }

    pthread_exit(NULL);
}

void * f_barbeiro(void * var) {

    while(1) {
        sem_wait(&sem_acorda_barbeiro);                     //dorme enqnto nao tem cliente

        sem_wait(&mutex);
        cortandoCabelo = queue_remove(&fila);
        paint();
        sem_post(&mutex);

        // printf("Barbeiro cortando cabelo. \n");
        sleep(2);                                //cortando cabelo

        sem_wait(&mutex);
        cortandoCabelo = -1;
        paint();
        sem_post(&mutex);

        sem_post(&sem_cabelo_cortado);              //terminou de cortar
    }
    pthread_exit(NULL);
}

int main() {
    quantidadeCadeiras = 5;
    quantidadeClientes = 15;

    cortandoCabelo = -1;
    queue_init(&fila, quantidadeCadeiras);
    queue_init(&filaDesistencia, quantidadeClientes);
    sem_init(&mutex, 0, 1);
    sem_init(&sem_cadeira, 0, quantidadeCadeiras);
    sem_init(&sem_cadeira_atendimento, 0, 1);
    sem_init(&sem_cabelo_cortado, 0, 0);
    sem_init(&sem_acorda_barbeiro, 0, 0);

    int j = 0;
    int id[quantidadeClientes];

    initscr();
    paint();
    pthread_create(&barbeiro, NULL, &f_barbeiro, NULL);

    sleep(1);

    for(j = 0; j < quantidadeClientes; j++) {
        id[j] = j;

        pthread_create(&cliente[j], NULL, &f_cliente, (void *) &id[j]);
        sleep(rand()%2);
    }

    for(int i = 0; i < quantidadeClientes; i++)
        pthread_join(cliente[i], NULL);
    fim = 1;
    paint();
    getch();
    endwin();

    return 0;
}
