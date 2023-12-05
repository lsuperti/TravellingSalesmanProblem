#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 20
#define INFINITY 99999

typedef struct Graph {
    int numVertices;
    int weights[MAX_VERTICES][MAX_VERTICES];
} Graph;

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    // Inicializa a matriz de pesos com zero
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph->weights[i][j] = 0;
        }
    }
    
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    if (src >= 0 && src < graph->numVertices && dest >= 0 && dest < graph->numVertices) {
        graph->weights[src][dest] = weight;
        graph->weights[dest][src] = weight; // Assume-se que o grafo é não-direcionado
    } else {
        printf("Erro: Vértices inválidos!\n");
    }
}

void displayGraph(Graph* graph) {
    printf("Dados armazenados no grafo:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("Peso da aresta entre vértices %d e %d: %d\n", i, j, graph->weights[i][j]);
        }
    }
}

int findMinKey(int key[], bool mstSet[], int numVertices) {
    int minKey = INFINITY;
    int minIndex = -1;
    for (int v = 0; v < numVertices; v++) {
        if (mstSet[v] == false && key[v] < minKey) {
            minKey = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void generateMST(Graph* graph) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool mstSet[MAX_VERTICES];

    // Inicializa todas as chaves como INFINITY e mstSet como false
    for (int i = 0; i < graph->numVertices; i++) {
        key[i] = INFINITY;
        mstSet[i] = false;
    }

    // Primeiro vértice é escolhido como raiz
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graph->numVertices - 1; count++) {
        int u = findMinKey(key, mstSet, graph->numVertices);
        mstSet[u] = true;

        for (int v = 0; v < graph->numVertices; v++) {
            if (graph->weights[u][v] && mstSet[v] == false && graph->weights[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph->weights[u][v];
            }
        }
    }

    // Mostra a Árvore Geradora Mínima
    printf("\nÁrvore Geradora Mínima (AGM):\n");
    for (int i = 1; i < graph->numVertices; i++) {
        printf("Aresta %d - %d\tPeso: %d\n", parent[i], i, graph->weights[i][parent[i]]);
    }
}

int main() {
    int numVertices;
    printf("Digite o número de vértices (até %d): ", MAX_VERTICES);
    scanf("%d", &numVertices);

    if (numVertices > 0 && numVertices <= MAX_VERTICES) {
        Graph* graph = createGraph(numVertices);

        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                int weight;
                printf("Digite o peso da aresta entre os vértices %d e %d: ", i, j);
                scanf("%d", &weight);
                addEdge(graph, i, j, weight);
            }
        }

        displayGraph(graph);
        generateMST(graph);
    } else {
        printf("Número inválido de vértices!\n");
    }

    return 0;
}
