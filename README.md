# Estrutura-de-Dados-FIFO
Grupo composto por: Ana Luiza, Iury Araújo, Kauê Otsubo, Mayane Cristina

Este projeto implementa um simulador do algoritmo de escalonamento **FIFO (First In, First Out)**, utilizado em Sistemas Operacionais para o gerenciamento de processos.

## 📌 Objetivo
Simular a execução de processos em uma CPU utilizando o algoritmo FIFO, calculando métricas clássicas de desempenho do escalonador.

## ⚙️ Algoritmo FIFO
O FIFO executa os processos na ordem de chegada, sem preempção.  
Uma vez que um processo inicia sua execução, ele permanece na CPU até finalizar.

## 📊 Métricas Calculadas
- **Tempo de Início**
- **Tempo de Término (Completion Time)**
- **Waiting Time (Tempo de Espera)**
- **Turnaround Time**
- **Response Time**
- **Throughput (Vazão)**

## 🧠 Estruturas Utilizadas
- Struct para representar o processo
- Fila dinâmica implementada com lista encadeada
- Alocação dinâmica de memória (`malloc` e `free`)

## ▶️ Como Compilar
Utilize o compilador GCC:

```bash
gcc fifo.c -o fifo
./fifo
