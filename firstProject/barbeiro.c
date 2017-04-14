#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CHAIR 10


sem_t sem_cadeira;
sem_t sem_acorda_barbeiro;
sem_t sem_cadeira_atendimento;
sem_t sem_cabelo_cortado;

pthread_t barbeiro;
pthread_t pintor;
pthread_t cliente[15];
int ld[15];

void clear() {
    for (int i = 0 ; i < 24; ++i)
        printf("\n");
}

void* paint(void *v){
    while(1){
        usleep(200);
        int queueLen;
        sem_getvalue(&sem_cadeira, &queueLen);
        queueLen = 3 - queueLen;
        if (queueLen > 0){
            printf("  ▓▓▓▓     ▓▓▓▓                                                                 ");
            printf("  ▓▓▓ ▓    ▓▓▓▓                                                                 ");
            printf("  ░█░█     ░o░o                                                                 ");
            printf("  ░░░░    █░░░░                                                                 ");
            printf("░▓▓▓▓▓▓░  █▓▓▓▓                                                                 ");
            printf("  ▓▓▓▓    █▓▓▓▓▓                                                                ");
            printf("  ▓▓▓▓    █████▓                                                                ");
            printf("  █  █    █   █░                                                                ");
        } else {
            printf("  ▓▓▓▓   Z                                                                      ");
            printf("  ▓▓▓ ▓ z                                                                       ");
            printf("  ░-░-                                                                          ");
            printf("  ░░░░    █                                                                     ");
            printf("░▓▓▓▓▓▓░  █                                                                     ");
            printf("  ▓▓▓▓    █                                                                     ");
            printf("  ▓▓▓▓    █████                                                                 ");
            printf("  █  █    █   █                                                                 ");
        }
        int i;
        queueLen -= 1;
        if (queueLen > 0){
            for (i = 0 ; i < queueLen && i < 9; ++i){
                printf("  ▓▓▓▓  ");
            }
            for (; i <10; ++i){
                printf("        ");
            }

            for (i = 0 ; i < queueLen && i < 9; ++i){
                printf("  ▓▓▓▓  ");
            }
            for (; i <10; ++i){
                printf("        ");
            }

            for (i = 0 ; i < queueLen && i < 9; ++i){
                printf("  ░o░o  ");
            }
            for (; i <10; ++i){
                printf("        ");
            }

            for (i = 0 ; i < queueLen && i < 9; ++i){
                printf("  ░░░░  ");
            }
            for (; i <10; ++i){
                printf("        ");
            }

            for (i = 0 ; i < queueLen && i < 9; ++i){
                printf("░▓▓▓▓▓▓░");
            }
            for (; i <10; ++i){
                printf("        ");
            }

            for (i = 0 ; i < queueLen && i < 9; ++i){
                printf("  ▓▓▓▓  ");
            }
            for (; i <10; ++i){
                printf("        ");
            }

            for (i = 0 ; i < queueLen && i < 9; ++i){
                printf("  ▓▓▓▓  ");
            }
            for (; i <10; ++i){
                printf("        ");
            }

            for (i = 0 ; i < queueLen && i < 9; ++i){
                printf("  █  █  ");
            }
            for (; i <10; ++i){
                printf("        ");
            }

            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                \n");
        }else{
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                ");
            printf("                                                                                \n");
        }
    }
}

    void * f_cliente(void *var) {

        int id = *(int *) var;
        if(sem_trywait(&sem_cadeira) == 0) {                        //ocupa cadeira

            // printf("Cliente %d senta e espera \n", id);
            sem_wait(&sem_cadeira_atendimento);                     //aguarda barbeiro
            sem_post(&sem_acorda_barbeiro);                                 //eh atendido
            sem_wait(&sem_cabelo_cortado);                          //espera cortar cabelo
            // printf("Cliente %d cortou o cabelo.\n", id);
            sem_post(&sem_cadeira);                                 //libera cadeira
            sem_post(&sem_cadeira_atendimento);                     //barbeiro liberado

        }
        // else
            // printf("Cliente %d desistiu de cortar o cabelo.\n", id);

        pthread_exit(NULL);
    }

    void * f_barbeiro(void * var) {

        while(1) {
            sem_wait(&sem_acorda_barbeiro);                     //dorme enqnto nao tem cliente
            // printf("Barbeiro cortando cabelo. \n");
            sleep(2);                                //cortando cabelo
            sem_post(&sem_cabelo_cortado);              //terminou de cortar
        }
        pthread_exit(NULL);
    }

    int main() {

        sem_init(&sem_cadeira, 0, 3);
        sem_init(&sem_cadeira_atendimento, 0, 1);
        sem_init(&sem_cabelo_cortado, 0, 0);

        int j = 0;

        int id[15];

        pthread_create(&barbeiro, NULL, &f_barbeiro, NULL);
        pthread_create(&pintor, NULL, &paint, NULL);

        int n_clientes = 15;

        for(j = 0; j < n_clientes; j++) {
            id[j] = j;
            pthread_create(&cliente[j], NULL, &f_cliente, (void *) &id[j]);
            sleep(rand()%5);
        }

        for(int i = 0; i < n_clientes; i++)
            pthread_join(cliente[i], NULL);

        printf("Fim \n\n");

        return 0;
    }
