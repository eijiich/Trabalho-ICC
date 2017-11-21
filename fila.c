#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

BANCO* criar_banco(int NUM_C){ //struct para guardar os caixas, e variáveis importantes
  BANCO* banco = (BANCO*) malloc(sizeof(BANCO));
  banco->filas =(FILA**) malloc(sizeof(FILA*) * NUM_C);
  banco->caixas =(CLIENTE**) malloc(sizeof(CLIENTE*) * NUM_C);
  banco->temp_med = 0; //variável que guarda o tempo de espera médio
  banco->temp_max = 0; //variável que guarda o tempo de espera máximo
  banco->atendidos = 0; //variável que guarda o número de pessoas já atendidas
  banco->tempo_global = 0; //variável que guarda o tempo atual;
  int i;
  for(i=0; i<NUM_C;i++){                    //Essa iteração cria o numero de filas para o caso de "NUM_C"(número) de filas
    banco->filas[i] = criar_fila(NUM_C);
  }
  for(i=0; i<NUM_C;i++){                    //Essa iteração cria o numero de caixas a atender os clientes
      banco->caixas[i] = NULL;
  }
  return banco;
}

FILA *criar_fila() {                           //Criação de uma fila vazia esperando pelos clientes
  FILA *fila = (FILA *) malloc(sizeof(FILA));

  if (fila != NULL) {
    fila->primeiro_c = NULL;
    fila->ultimo_c = NULL;
    fila->tamanho = 0;
  }

  return fila;
}

int apagar_fila(FILA** fila) {              //funçao que vai removendo os clientes até que seja possível remover a filas liberando toda a memória gasta nela
  if (fila != NULL && *fila != NULL) {
      CLIENTE *prem = (*fila)->primeiro_c;

     while(prem != NULL) {                //enquanto houver algum cliente ele será removido
        CLIENTE *pprox = prem->prox_c;
        apagar_cliente(&prem);
        prem = pprox;
     }

     free(*fila);
     *fila=NULL;
     return 1;
  }
  return 0;
}

int apagar_cliente(CLIENTE** cliente){        //Libera a memória reservada para os tempos do cliente
    if(cliente != NULL && *cliente != NULL){
        free(*cliente);
        *cliente =  NULL;
        return 1;
    }
    return 0;
}

int apagar_banco(BANCO** banco){            //Quando não houver mais filas e clientes pode-se liberar a memoria alocada para o banco
    if(banco != NULL && *banco != NULL){
        free(*banco);
        *banco =  NULL;
        return 1;
    }
    return 0;
}


CLIENTE* novo_cliente(double t_chegada, double t_atendimento){ //A partir dos tempos de chegada e atendimentos gerados pelo código
                                                               //presente na Normal.c são atribuidos tais valores para o cliente gerado
  CLIENTE* cliente = (CLIENTE *)malloc(sizeof(CLIENTE));
  cliente->t_chegada = t_chegada;
  cliente->t_atendimento = t_atendimento;
  cliente->t_espera = 0;
  cliente->t_em_fila = 0;
  cliente->prox_c = NULL;
  return cliente;
}

void insere_cliente(FILA* fila, CLIENTE* cliente){ //Função que insere todos os clientes em uma fila, tal fila
    if(fila->tamanho == 0){                        //armazena os clientes em ordem de chegada, assim sabe-se
        fila->primeiro_c = cliente;                //quando o cliente entra no caixa no segundo caso, ou qual fila
        fila->ultimo_c = cliente;                  //ele entrará no primeiro caso
        fila->tamanho = 1;
        return;
    }
    fila->ultimo_c->prox_c = cliente;//ultimmo cliente aponta para o novo cliente
    fila->ultimo_c = cliente;//o novo cliente é adicionado
    fila->tamanho++;//aumenta o tamanho da fila
}

void entrar_na_fila(BANCO* banco, FILA* fila, int NUM_C){ //Função responsável por calcular em qual fila o cliente entrará
    int i, j, k;
    double menor_tempo; //variável que recebera o menor tempo global em que ocorrerá uma nova ação
    for(i = 0; i < NUM_C; i++){ //iteração que procura um caixa vazio, ou com um cliente já atendido, mas que não há ninguém na fila, nesse caso é necessário que o tempo global aumente até que possa ocorrer uma nova ação
        if((banco->caixas[i] == NULL || banco->caixas[i]->t_atendimento == 0) && banco->filas[i]->tamanho == 0){
            fila->primeiro_c->t_chegada = menor_tempo; //Procura-se a ação que ocorrerá primeiro, a entrada de um novo cliente ou o atendimento de outro
            for(j = 0; j < NUM_C; j++){ //Iteração que procura o cliente em caixa e não atendido que terminará de ser atendido primeiro
                if(banco->caixas[j] != NULL){
                    if(banco->caixas[j]->t_atendimento + banco->tempo_global < menor_tempo){
                        menor_tempo = banco->caixas[j]->t_atendimento + banco->tempo_global;
                    }
                }
            }
            int aux = banco->tempo_global; //variável auxiliar que guarda o tempo global antes da próxima ação
            banco->tempo_global = menor_tempo;
            for(j=0; j<NUM_C;j++){ //É necessário que o tempo transcorrido seja decrementado dos outros clientes em atendimento no caixa por meio dessa iteração
                if(banco->caixas[j] != NULL){
                    banco->caixas[j]->t_atendimento = menor_tempo - aux;
                    if(banco->caixas[j]->t_atendimento < 0){
                        banco->caixas[j]->t_atendimento = 0;
                    }
                }
            }
        }
    }
    while (banco->tempo_global >= fila->primeiro_c->t_chegada) { //Enquanto houver clientes cujo valor do tempo de chegada é menor que o tempo global, eles deverão ser encaminhados para a fila com menor tamanho
        double menor_tamanho = 10000;
        for(i = 0; i < NUM_C; i++){ //Iteração que procura a menor fila
            if(banco->filas[i]->tamanho < menor_tamanho){
                menor_tamanho = banco->filas[i]->tamanho;
                k = i;
            }
        }
        banco->filas[k]->ultimo_c = fila->primeiro_c; //A menor fila recebe o que chegou
        banco->filas[k]->tamanho++;
        fila->primeiro_c = fila->primeiro_c->prox_c; //O primeiro da fila de chegada passa ser o cliente que chegaria após aquele que acabou de entrar em uma fila

    }
}

void chama_prox_cl_caso_1(BANCO* banco, int NUM_C){ //Chama o cliente "i" para o caixa "i"
    int i;
    CLIENTE* remove_cliente; //Variável auxiliar que ajuda na remoção dos clientes que acabarem de ser atendidos
    for(i = 0; i < NUM_C; i++){ //Iteração para chamar o próximo cliente da fila
        if(banco->caixas[i] == NULL && banco->filas[i]->tamanho > 0){ //Caso em que o caixa está vazio e há alguém na fila
            banco->caixas[i] = banco->filas[i]->primeiro_c;
            banco->caixas[i]->prox_c = NULL;
            banco->filas[i]->primeiro_c = banco->filas[i]->primeiro_c->prox_c;
            banco->filas[i]->tamanho--;

        }
        else if(banco->caixas[i]->t_atendimento == 0 && banco->filas[i]->tamanho > 0){ //Caso em que o cliente no caixa acabou de ser atendido e há alguém na fila
            remove_cliente = banco->caixas[i];
            banco->caixas[i] = banco->filas[i]->primeiro_c;
            banco->caixas[i]->prox_c = NULL;
            apagar_cliente(&(remove_cliente));
            banco->filas[i]->primeiro_c = banco->filas[i]->primeiro_c->prox_c;
            banco->filas[i]->tamanho--;
        }
        banco->caixas[i]->t_espera = banco->tempo_global - banco->caixas[i]->t_chegada; //Como o cliente entrou no caixa pode-se calcular seu tempo de espera
        banco->t_espera_total+= banco->caixas[i]->t_espera; //O tempo de espera é a diferença entre o tempo de chegada e o atual, esse tempo também será usado no calculo do tempo de espera médio
        if(banco->caixas[i]->t_espera > banco->temp_max) //Assim como no cáculo do tempo máximo de espera
            banco->temp_max = banco->caixas[i]->t_espera;
    }
}

void chama_prox_cl_caso_2(BANCO* banco, FILA* fila, int NUM_C){ //No caso dois só há uma fila para NUM_C caixas
    int i;
    CLIENTE* remove_cliente; //Variável de remoção semelhante a anterior
    for(i = 0; i < NUM_C; i++){ //Iteração para chamar o próximo cliente da fila
        if(banco->caixas[i] == NULL && fila->tamanho > 0){ //Caso em que o caixa está vazio e há alguém na fila
            banco->caixas[i] = fila->primeiro_c;
            fila->primeiro_c = fila->primeiro_c->prox_c;
        }
        else if(banco->caixas[i]->t_atendimento == 0 && fila->tamanho > 0){ //Caso em que o cliente no caixa acabou de ser atendido e há alguém na fila
            remove_cliente = banco->caixas[i];
            banco->caixas[i] = fila->primeiro_c;
            apagar_cliente(&(remove_cliente));
            banco->atendidos++;
            if(fila->primeiro_c->prox_c != NULL)
                fila->primeiro_c = fila->primeiro_c->prox_c;
        }
        banco->caixas[i]->t_espera = banco->tempo_global - banco->caixas[i]->t_chegada; //Semelhante ao caso anterior
        banco->t_espera_total+= banco->caixas[i]->t_espera;
        if(banco->caixas[i]->t_espera > banco->temp_max){
            banco->temp_max = banco->caixas[i]->t_espera;
}

void atende_cliente(BANCO* banco, int NUM, int NUM_C){
    int i;
    double menor_tempo = 10000;//(o correto seria ser que o menor tempo começace como o maior tempo possível que é igual a média mais sigma)
    for(i = 0; i < NUM_C; i++){                                    //Essa iteração procura o caixa que vai terminar de atender o cliente primeiro
        if(banco->caixas[i] != NULL){
            if(banco->caixas[i]->t_atendimento < menor_tempo){
                menor_tempo = banco->caixas[i]->t_atendimento;
                if(banco->caixas[i]->t_atendimento < 0){
                    banco->caixas[i]->t_atendimento = 0;
                }
            }
        }
        else{
            menor_tempo = 0; //Se algum caixa tiver vazio alguém já poderá usa-lo
        }
    }

    banco->tempo_global = banco->tempo_global + menor_tempo; //O menor tempo encontrado de atendimento é adicionado a um tempo global
    for(i = 0; i < NUM_C; i++){
        if(banco->caixas[i] != NULL){
            banco->caixas[i]->t_atendimento = banco->caixas[i]->t_atendimento - menor_tempo;
        }
    }
}

void  temp_medio(BANCO* banco, int NUM){           //calcula o tempo de espera medio pela soma de todos os tempos de espera dividido pelo numero de pessoas atendidas
    banco->temp_med =  banco->t_espera_total/NUM;
}
