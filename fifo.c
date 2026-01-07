#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int tempoChegada;
    int duracao;
    int tempoInicio;
    int tempoTermino;
    int tempoEspera;
    int turnaround;
    int tempoResposta;
} Processo;

typedef struct No {
    Processo processo;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;

Fila *criar_fila() {
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void enfileirar(Fila *f, Processo p) {
    No *novo = (No*)malloc(sizeof(No));
    novo->processo = p;
    novo->prox = NULL;

    if (f->inicio == NULL) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
}

Processo criar_processo(int id, int chegada, int duracao) {
    Processo p;
    p.id = id;
    p.tempoChegada = chegada;
    p.duracao = duracao;
    p.tempoInicio = 0;
    p.tempoTermino = 0;
    p.tempoEspera = 0;
    p.turnaround = 0;
    p.tempoResposta = 0;
    return p;
}

void simular_fifo(Fila *f) {
    if (f->inicio == NULL) return;

    No *aux = f->inicio;
    int tempoAtual = 0;

    while (aux != NULL) {
        Processo *p = &aux->processo;

        if (tempoAtual < p->tempoChegada) {
            tempoAtual = p->tempoChegada;
        }

        p->tempoInicio = tempoAtual;
        p->tempoResposta = p->tempoInicio - p->tempoChegada;
        p->tempoEspera = p->tempoInicio - p->tempoChegada;

        tempoAtual += p->duracao;

        p->tempoTermino = tempoAtual;
        p->turnaround = p->tempoTermino - p->tempoChegada;

        aux = aux->prox;
    }
}

void imprimir_relatorio(Fila *f) {
    No *aux = f->inicio;
    float somaEspera = 0, somaTurnaround = 0, somaResponse = 0;
    int totalProcessos = 0;
    int tempoFinal = 0;

    printf("\n=========================================================================\n");
    printf("                       RELATORIO FINAL - FIFO                            \n");
    printf("=========================================================================\n");
    printf("ID\tChegada\tBurst\tInicio\tFim\tEspera\tTurn.\tResp.\n");
    printf("-------------------------------------------------------------------------\n");

    while (aux != NULL) {
        Processo p = aux->processo;

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p.id, p.tempoChegada, p.duracao, p.tempoInicio,
               p.tempoTermino, p.tempoEspera, p.turnaround, p.tempoResposta);

        somaEspera += p.tempoEspera;
        somaTurnaround += p.turnaround;
        somaResponse += p.tempoResposta;
        totalProcessos++;

        if (p.tempoTermino > tempoFinal) {
            tempoFinal = p.tempoTermino;
        }

        aux = aux->prox;
    }

    printf("=========================================================================\n");
    if (totalProcessos > 0) {
        printf("METRICAS AGREGADAS:\n");
        printf("> Media Waiting Time:    %.2f\n", somaEspera / totalProcessos);
        printf("> Media Turnaround Time: %.2f\n", somaTurnaround / totalProcessos);
        printf("> Media Response Time:   %.2f\n", somaResponse / totalProcessos);
        printf("> Vazao (Throughput):    %.4f processos/unidade de tempo\n",
               (float)totalProcessos / tempoFinal);
    }
    printf("=========================================================================\n");
}

void liberar_fila(Fila *f) {
    No *aux = f->inicio;
    while (aux != NULL) {
        No *tmp = aux;
        aux = aux->prox;
        free(tmp);
    }
    free(f);
}

int main() {
    Fila *fila = criar_fila();
    int n, id, cheg, dur, i;

    printf("--- SIMULADOR FIFO ---\n");
    printf("Quantos processos deseja inserir? ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nProcesso %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &id);
        printf("Tempo de Chegada: ");
        scanf("%d", &cheg);
        printf("Duracao (Burst Time): ");
        scanf("%d", &dur);

        enfileirar(fila, criar_processo(id, cheg, dur));
    }

    simular_fifo(fila);
    imprimir_relatorio(fila);
    liberar_fila(fila);

    return 0;
}

