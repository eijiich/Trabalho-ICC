#include "fila.h"
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "Normal.h"
#include <stdio.h>

int NUM_C = 4;
int NUM = 20;

void main(){
	int i;
	double t_chegada = 0, t_atendimento;
	BANCO* banco = criar_banco(NUM_C);
	printf("%d ", banco->filas[0]->tamanho);
	FILA* pre_fila = criar_fila(); //Fila que receberá todos os clientes gerados
	CLIENTE* cliente_aux;

	for(i = 0; i < NUM; i++){ //Geração e inserção de clientes em uma fila
		t_chegada = t_chegada + Normal(1, 0.3); //geração de um tempo de chegada
		t_atendimento = Normal(4, 0.3); //geração de um tempo de atendimento
		cliente_aux = novo_cliente(t_chegada, t_atendimento); ////geração de um novo cliente
		insere_cliente(pre_fila, cliente_aux);
	}
	while(banco->atendidos < NUM-1){ //Enquanto todos os clientes não forem atendido a iteração não acaba
		chama_prox_cl_caso_2(banco, pre_fila, NUM_C); //No caso dois basta chamar essas duas funções já que há apenas uma unica fila
		atende_cliente(banco, NUM, NUM_C);
	}
	//Para o caso um seria chamado as funções entra_na_fila, chama_prox_cl_caso_1 e atende_cliente até que todos fossem atendidos
	temp_medio(banco, NUM); // calcula-se o tempo médio como já descrito na struct BANCO

	for(i = 0; i < NUM_C; i++){ //apaga-se os clientes e todas as filas
	 	apagar_fila(&(banco->filas[i]));
	}
	apagar_banco(&banco); //por fim apaga-se o banco
}
