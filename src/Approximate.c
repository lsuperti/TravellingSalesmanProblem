#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h> // Adicionando a biblioteca limits.h

#define SIZE 29  // Tamanho da matriz de adjacência


void readAdjacencyMatrix(int adjacencyMatrix[SIZE][SIZE]) {
    FILE *file = fopen("C:\\temp\\wp-github\\caxeiroviajante\\lib\\tsp5_27603.txt", "r");
    if (file == NULL) {
        perror("C:\\temp\\wp-github\\caxeiroviajante\\lib\\tsp5_27603.txt");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fscanf(file, "%d", &adjacencyMatrix[i][j]);
        }
    }

    fclose(file);
}


void printMatrix(int adjacencyMatrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

int minKey(int key[], bool mstSet[], int size) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < size; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int ** graph, int size) {
    printf("Aresta \tPeso\n");
    for (int i = 1; i < size; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}

void calculateMST(int ** graph, int size) {
    // Intellisense does not support VLAs, so we define the size as placeholder constant expression.
    #ifdef __INTELLISENSE__
        #define size 1
    #endif
    
    int parent[size];
    int key[size];
    bool mstSet[size];

    for (int i = 0; i < size; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < size - 1; count++) {
        int u = minKey(key, mstSet, size);
        mstSet[u] = true;

        for (int v = 0; v < size; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    //printMST(parent, graph, size);

    #ifdef __INTELLISENSE__
        #undef size
    #endif
}

int calculateCost(int parent[], int ** adjacencyMatrix, int size) {
    int cost = 0;
    for (int i = 1; i < size; i++) {
        cost += adjacencyMatrix[i][parent[i]];
    }
    return cost;
}

// Função para percorrer a MST e formar um caminho aproximado (DFS)
void DFS(int v, int parent[], bool visited[], int ** adjacencyMatrix, int size) {
    visited[v] = true;

    for (int i = 0; i < size; i++) {
        if (adjacencyMatrix[v][i] && !visited[i]) {
            //printf("%d -> %d\n", v, i); // Aqui você pode fazer algo com o nó visitado, como adicionar ao caminho
            parent[i] = v;
            DFS(i, parent, visited, adjacencyMatrix, size);
        }
    }
}


int Approximate( int ** matrix, int size ) {
    // Intellisense does not support VLAs, so we define the size as placeholder constant expression.
    #ifdef __INTELLISENSE__
        #define size 1
    #endif
    
    bool  visited[size];
    int   parent[size];
    
    calculateMST( matrix, size );

    DFS( 0, parent, visited, matrix, size );

    return calculateCost( parent, matrix, size );

    #ifdef __INTELLISENSE__
        #undef size
    #endif
}

/*
int main() {

    // inicio do codigo que calcula a MST
    int adjacencyMatrix[SIZE][SIZE];

    readAdjacencyMatrix(adjacencyMatrix);

    printf("Matriz lida:\n");
    printMatrix(adjacencyMatrix);

    printf("\nCalculando a Árvore Geradora Mínima (MST):\n");
    calculateMST(adjacencyMatrix, SIZE);
    //final do código que calcula a MST

    // Agora você pode prosseguir para calcular o caminho aproximado.
    bool visited[SIZE];
    int parent[SIZE];

    for (int i = 0; i < SIZE; i++) {
        visited[i] = false;
    }

    printf("\nCaminho Aproximado (DFS na MST):\n");
    // Chama a DFS a partir do nó inicial (por exemplo, o nó 0)
    DFS(0, parent, visited, adjacencyMatrix);
    
    int cost = calculateCost(parent, adjacencyMatrix);
    printf("\nCusto total do caminho aproximado: %d\n", cost);

    return 0;
}
*/