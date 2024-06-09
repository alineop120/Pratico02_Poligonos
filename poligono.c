#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Estrutura para representar um ponto
typedef struct {
    double x; // Coordenada x do ponto
    double y; // Coordenada y do ponto
} Ponto;

// Função para calcular a área do triângulo formado pelos pontos A, B e C
float AreaTriangulo(Ponto A, Ponto B, Ponto C) {
    return fabs((A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y)) / 2.0);
}

// Função para calcular a área do polígono
double AreaPoligono(Ponto vertices[], int n) {
    double area = 0.0;

    // Verifica se o polígono tem menos de 3 lados
    if (n < 3) {
        printf("Poligono deve ter pelo menos 3 lados.\n");
        return 0.0;
    }

    // Calcula a área do polígono
    Ponto pontoFixo = vertices[0]; // Fixamos o primeiro ponto
    for (int i = 1; i < n - 1; i++) {
        area += AreaTriangulo(pontoFixo, vertices[i], vertices[i+1]);
    }

    return area;
}

// Função para ler os vértices do polígono de um arquivo
Ponto* LerVerticesArquivo(const char* nomeArquivo, int* numVertices) {
    FILE *arquivo;
    int i;
    Ponto *vertices;

    // Abre o arquivo para leitura
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo '%s'. Verifique se o arquivo existe.\n", nomeArquivo);
        return NULL;
    }

    // Lê o número de vértices do polígono do arquivo
    fscanf(arquivo, "%d", numVertices);

    // Verifica se há pelo menos 3 vértices
    if (*numVertices < 3) {
        printf("Poligono deve ter pelo menos 3 lados.\n");
        fclose(arquivo);
        return NULL;
    }

    // Aloca memória para armazenar os vértices
    vertices = (Ponto *)malloc(*numVertices * sizeof(Ponto));

    // Lê as coordenadas dos vértices do arquivo
    for (i = 0; i < *numVertices; i++) {
        fscanf(arquivo, "%lf %lf", &vertices[i].x, &vertices[i].y);
    }

    fclose(arquivo); // Fecha o arquivo

    return vertices;
}

int main() {
    int numVertices;
    double area;

    // Ler os vértices do polígono de um arquivo
    Ponto *vertices = LerVerticesArquivo("poligono.txt", &numVertices);
    if (vertices == NULL) {
        return 1; // Encerra o programa em caso de erro na leitura do arquivo
    }

    // Calcula a área do polígono
    area = AreaPoligono(vertices, numVertices);

    // Imprime a área do polígono
    printf("A area do poligono e %.0lf\n", area);

    // Libera a memória alocada para os vértices
    free(vertices);

    return 0;
}
