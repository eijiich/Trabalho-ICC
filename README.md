Trabalho de implementação – Filas
Você deve escrever um programa de computador que vai simmular uma agência bancária em dois
modelos diferentes. No primeiro modelo, a agência possui N caixas para atendimento aos clientes e
uma fila única para os N caixas. No segundo modelo, a agência possui os mesmos N caixas mas
cada caixa possui a sua própria fila. Assim, no segundo modelo, o cliente, ao chegar na agência
escolhe a menor das N filas e é nela que fica esperando, até ser atendido.
O objetivo é medir, para cada um dos modelos, o tempo médio e o tempo máximo que um cliente
espera na fila para ser atendido.
Cada cliente que chega à agência tem um tempo de chegada e um tempo de serviço, ou seja, o
tempo que ele vai gastar sendo atendido no caixa. Esses dois valores seguem uma distribuição
normal. Para gerar esses valores com distribuição normal, utilize a função fornecida pelo professor.
Vários parâmetros podem ser alterados para analisar-se o comportamento dos dois modelos. Por
exemplo:
– número de caixas disponível na gência;
– número total de clientes a serem atendidos, ou seja, com quantos clientes o sistema vai ser
simulado;
– média e desvio padrão do intervalo de chegada dos clientes. Por exemplo, pode-se
estabelecer que, em média,um cliente chega à agência a cada 2 minutos, com desvio padrão
de 1 minuto;
– o mesmo vale para o tempo de atendimento do cliente. Pode-se estabelecer que, em média, o
tempo de atendimento de um cliente é de 4 minutos, com desvio de 1,5 minuto.
Execute os seus modelos com diferentes valores para esses parâmetros e examine qual modelo é o
melhor para cada situação. Crie diferentes combinações com os seguintes parâmetros:
• Número de caixas na agência: 1, 4 e 8
• Númeo de clientes: 1, 10, 100 e 500
• Tempo e devio padrão de chegada: (1.0, 0.5) e (4.0, 2.5)
• Tempo médio e desvio de atendimento no caixa: (4.0, 2.5) e (1.0, 0.5)
Além do programa, fartamente comentado, você deve entregar um documento, descrevendo a sua
implementação.
