#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int NUM = 4;

BANCO* criar_banco(int NUM){
  BANCO* banco = (BANCO*) malloc(sizeof(BANCO));
  banco->filas =(FILA**) malloc(sizeof(FILA*) * NUM);
  banco->caixas =(CLIENTE**) malloc(sizeof(CLIENTE*) * NUM);
  int i;
  for(i=0; i<NUM;i++){
    banco->filas[i] = criar_fila();
  }

}

FILA *criar_fila() {
  FILA *fila = (FILA *) malloc(sizeof(FILA));

  if (fila != NULL) {
    fila->primeiro_c = NULL;
    fila->ultimo_c = NULL;
    fila->tamanho = 0;
  }

  return fila;
}

int apagar_fila(FILA** fila) {
  if (fila != NULL && *fila != NULL) {
      CLIENTE *prem = (*fila)->primeiro_c;

     while(prem != NULL) {
        CLIENTE *pprox = prem->prox_c;
        //apagar_cliente(prem);
        prem = pprox;
     }

     free(*fila);
     *fila=NULL;
  }
}

CLIENTE* novo_cliente(double t_chegada, double t_atendimento){
  CLIENTE* cliente = (CLIENTE *)malloc(sizeof(CLIENTE));
  cliente->t_chegada = t_chegada;
  cliente->t_atendimento = t_atendimento;
  cliente->t_espera = 0;
  cliente->prox_c = NULL;
  return cliente;
}

double inserir_cliente_caso1(BANCO* banco, CLIENTE* cliente, double t_espera_max){
  int i, menor_tamanho = NUM+1, aux;
  for(i = 0; i < NUM; i++){
    if(banco->filas[i]->tamanho < menor_tamanho){
      menor_tamanho = banco->filas[i]->tamanho;
      aux = i;
    }
  }
  if(banco->filas[aux]->tamanho = 0){
    banco->filas[aux]->ultimo_c = cliente;
    return cliente->t_espera;
  }
  cliente->t_espera = banco->filas[aux]->ultimo_c->t_espera +banco->filas[aux]->ultimo_c->t_atendimento - (banco->filas[aux]->ultimo_c->t_chegada - cliente->t_chegada);
  banco->filas[aux]->ultimo_c->prox_c = cliente;
  banco->filas[aux]->ultimo_c = cliente;
  banco->filas[aux]->tamanho++;

  if(cliente->t_espera > t_espera_max){
    return cliente->t_espera;
  }
  return t_espera_max;
}

tempomax_caso1(double media1[]){
  
}
