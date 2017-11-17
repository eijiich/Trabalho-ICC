#ifndef FILA_H
#define FILA_H


typedef struct cliente{
  int t_chegada;
  int t_atendimento;
  int t_espera;
  struct cliente* prox_c;
} CLIENTE;

typedef struct fila{
  CLIENTE* ultimo_c;
  CLIENTE* primeiro_c;
  int tamanho;
} FILA;

typedef struct banco{
  FILA** filas;
  CLIENTE** caixas;
}BANCO;

FILA* criar_fila();
int apagar_fila(FILA**);
CLIENTE* novo_cliente(double, double);
double inserir_cliente_caso1();
void inserir_cliente_caso2();
int chamar_proximo_cliente();
double tempomed_caso1();
double tempomed_caso2();
double tempomax_caso2();

#endif
