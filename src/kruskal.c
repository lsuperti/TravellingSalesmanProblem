#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 20

typedef struct Graph {
    int numVertices;
    int weights[MAX_VERTICES][MAX_VERTICES];
} Graph;

typedef struct Edge {
    int src;
    int dest;
    int weight;
} Edge;

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

int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void unionSet(int parent[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    parent[xroot] = yroot;
}

void generateMST(Graph* graph) {
    int parent[MAX_VERTICES];
    for (int i = 0; i < graph->numVertices; i++) {
        parent[i] = i;
    }

    Edge edges[MAX_VERTICES * MAX_VERTICES];
    int edgeCount = 0;

    // Obtém todas as arestas do grafo e armazena no array edges
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = i + 1; j < graph->numVertices; j++) {
            if (graph->weights[i][j] > 0) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = graph->weights[i][j];
                edgeCount++;
            }
        }
    }

    // Ordena as arestas em ordem crescente de peso
    qsort(edges, edgeCount, sizeof(Edge), compareEdges);

    // Constrói a Árvore Geradora Mínima
    printf("\nÁrvore Geradora Mínima (AGM):\n");
    for (int i = 0; i < edgeCount; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int srcParent = find(parent, src);
        int destParent = find(parent, dest);

        if (srcParent != destParent) {
            printf("Aresta %d - %d\tPeso: %d\n", src, dest, edges[i].weight);
            unionSet(parent, srcParent, destParent);
        }
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
