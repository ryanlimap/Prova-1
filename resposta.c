#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_veiculo {
    char placa[20];
    char modelo[20];
    char marca[20];
    char kilometros[20];
}t_veiculo;

// Função para ler o arquivo e retornar um vetor dinâmico de t_veiculo
t_veiculo* loadbdveics(const char* nomearq) {
    FILE* arquivo = fopen(nomearq, "r");

    t_veiculo *veiculos = (t_veiculo*)malloc(150 * sizeof(t_veiculo));

    //debug
    if (veiculos == NULL) {
        printf("erro de alocação de vetor");
    }

    for (int i = 0; i < 150; i++) {
        fgets(veiculos[i].placa, 150, arquivo);
        veiculos[i].placa[strcspn(veiculos[i].placa, "\n")] = '\0';
        fgets(veiculos[i].modelo, 150, arquivo);
        veiculos[i].modelo[strcspn(veiculos[i].modelo, "\n")] = '\0';
        fgets(veiculos[i].marca, 150, arquivo);
        veiculos[i].marca[strcspn(veiculos[i].marca, "\n")] = '\0';
        fgets(veiculos[i].kilometros, 150, arquivo);
        veiculos[i].kilometros[strcspn(veiculos[i].kilometros, "\n")] = '\0';
    }
    fclose(arquivo);
    return veiculos;
}

void filtro(t_veiculo *vet, char *marca_veiculo, int tam_vet) {
    char *str2 = ".txt";

    // Calcular o tamanho necessário para str1
    size_t tamanho = strlen(marca_veiculo) + strlen(str2) + 1;

    // Alocar memória para str1
    char *str1 = (char *)malloc(tamanho * sizeof(char));
    if (str1 == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    // Copiar marca_veiculo para str1
    strcpy(str1, marca_veiculo);

    // Concatenar str2 a str1
    strcat(str1, str2);

    // Abrir o arquivo
    FILE *arquivo = fopen(str1, "wt");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(str1);
        return;
    }

    for (int i = 0; i < tam_vet; i++) {
        if (strcmp(vet[i].marca, marca_veiculo) == 0) {
            fprintf(arquivo, "%s,", vet[i].placa);
            fprintf(arquivo, "%s,", vet[i].modelo);
            fprintf(arquivo, "%s,", vet[i].marca);
            fprintf(arquivo, "%s\n", vet[i].kilometros);
        }
    }
    fclose(arquivo);
    free(str1);
}

int main() {
    const char* nomearq = "bdveiculos.txt";

    t_veiculo *veiculos = loadbdveics(nomearq);

    filtro(veiculos, "FIAT", 150);
    filtro(veiculos, "TOYOTA", 150);
    filtro(veiculos, "FORD", 150);
    filtro(veiculos, "RENAULT", 150);

    free(veiculos);
    veiculos = NULL;
    return 0;
}