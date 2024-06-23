#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_veiculo {
    char placa[20];
    char modelo[20];
    char marca[20];
    char kilometros[20];
} t_veiculo;

t_veiculo* loadbdveics(char* nomearq) {
    FILE* arquivo;
    t_veiculo *veiculos;
    int i;

    arquivo = fopen(nomearq, "r");

    veiculos = (t_veiculo*)malloc(150 * sizeof(t_veiculo));

    /* debug */
    if (veiculos == NULL) {
        printf("erro de alocação de vetor");
        return NULL;
    }

    for (i = 0; i < 150; i++) {
        char *p;

        /* Lê a placa e remove o '\n' */
        fgets(veiculos[i].placa, 150, arquivo);
        p = veiculos[i].placa;
        while (*p != '\0') {
            if (*p == '\n') {
                *p = '\0';
            }
            p++;
        }

        /* Lê o modelo e remove o '\n' */
        fgets(veiculos[i].modelo, 150, arquivo);
        p = veiculos[i].modelo;
        while (*p != '\0') {
            if (*p == '\n') {
                *p = '\0';
            }
            p++;
        }

        /* Lê a marca e remove o '\n' */
        fgets(veiculos[i].marca, 150, arquivo);
        p = veiculos[i].marca;
        while (*p != '\0') {
            if (*p == '\n') {
                *p = '\0';
            }
            p++;
        }

        /* Lê os kilometros e remove o '\n' */
        fgets(veiculos[i].kilometros, 150, arquivo);
        p = veiculos[i].kilometros;
        while (*p != '\0') {
            if (*p == '\n') {
                *p = '\0';
            }
            p++;
        }
    }
    fclose(arquivo);
    return veiculos;
}

void filtro(t_veiculo *vet, char *marca_veiculo, int tam_vet) {
    char *str2 = ".txt";
    int tamanho;
    char *str1;
    FILE *arquivo;
    int i;

    tamanho = strlen(marca_veiculo) + strlen(str2) + 1;

    /* Alocar memória para str1 */
    str1 = (char *)malloc(tamanho * sizeof(char));
    if (str1 == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    strcpy(str1, marca_veiculo);
    strcat(str1, str2);

    arquivo = fopen(str1, "wt");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(str1);
        return;
    }

    for (i = 0; i < tam_vet; i++) {
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
    char* nomearq = "bdveiculos.txt";
    t_veiculo *veiculos;

    veiculos = loadbdveics(nomearq);

    filtro(veiculos, "FIAT", 150);
    filtro(veiculos, "TOYOTA", 150);
    filtro(veiculos, "FORD", 150);
    filtro(veiculos, "RENAULT", 150);

    free(veiculos);
    veiculos = NULL;
    return 0;
}
