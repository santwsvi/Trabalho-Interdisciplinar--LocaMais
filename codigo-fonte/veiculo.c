


// veiculo.
#include "veiculo.h"
#include <stdio.h>
#include <string.h>

#define MAX_VEICULOS 100
#define ARQUIVO_VEICULOS "veiculos.dat"

int veiculoExiste(Veiculo veiculos[], int totalVeiculos, int codigo) {
    for (int i = 0; i < totalVeiculos; i++) {
        if (veiculos[i].codigo == codigo) {
            return 1;
        }
    }
    return 0;
}

void cadastrarVeiculo(Veiculo veiculos[], int *totalVeiculos) {
    if (*totalVeiculos < MAX_VEICULOS) {
        Veiculo novoVeiculo;

        do {
            printf("Digite o c�digo do ve�culo: ");
            scanf("%d", &novoVeiculo.codigo);

            if (veiculoExiste(veiculos, *totalVeiculos, novoVeiculo.codigo)) {
                printf("J� existe um ve�culo com este c�digo. Tente novamente.\n");
            }
        } while (veiculoExiste(veiculos, *totalVeiculos, novoVeiculo.codigo));

        while (getchar() != '\n');

        printf("Digite a descri��o do ve�culo: ");
        fgets(novoVeiculo.descricao, sizeof(novoVeiculo.descricao), stdin);
        novoVeiculo.descricao[strcspn(novoVeiculo.descricao, "\n")] = '\0';

        printf("Digite o modelo do ve�culo: ");
        fgets(novoVeiculo.modelo, sizeof(novoVeiculo.modelo), stdin);
        novoVeiculo.modelo[strcspn(novoVeiculo.modelo, "\n")] = '\0';

        printf("Digite a cor do ve�culo: ");
        fgets(novoVeiculo.cor, sizeof(novoVeiculo.cor), stdin);
        novoVeiculo.cor[strcspn(novoVeiculo.cor, "\n")] = '\0';

        printf("Digite a placa do ve�culo: ");
        fgets(novoVeiculo.placa, sizeof(novoVeiculo.placa), stdin);
        novoVeiculo.placa[strcspn(novoVeiculo.placa, "\n")] = '\0';

        printf("Digite o valor da di�ria do ve�culo: ");
        scanf("%lf", &novoVeiculo.valor_diaria);

        printf("Digite a capacidade de ocupantes do ve�culo: ");
        scanf("%d", &novoVeiculo.ocupantes);

        strcpy(novoVeiculo.status, "Dispon�vel");

        veiculos[*totalVeiculos] = novoVeiculo;
        (*totalVeiculos)++;

        // Grava os ve�culos no arquivo
        FILE *arquivo = fopen(ARQUIVO_VEICULOS, "ab");
        if (arquivo != NULL) {
            fwrite(&novoVeiculo, sizeof(Veiculo), 1, arquivo);
            fclose(arquivo);
        } else {
            printf("Erro ao abrir o arquivo de ve�culos.\n");
        }

        printf("Ve�culo cadastrado com sucesso!\n");
    } else {
        printf("Limite de ve�culos atingido!\n");
    }
}

void exibirDetalhesVeiculo(Veiculo veiculo) {
    printf("C�digo: %d | Descri��o: %s | Modelo: %s | Cor: %s | Placa: %s | Valor Di�ria: %.2f | Ocupantes: %d | Status: %s\n",
           veiculo.codigo, veiculo.descricao, veiculo.modelo, veiculo.cor, veiculo.placa, veiculo.valor_diaria, veiculo.ocupantes, veiculo.status);
}

void carregarVeiculos(Veiculo veiculos[], int *totalVeiculos) {
    FILE *arquivo = fopen(ARQUIVO_VEICULOS, "rb");
    if (arquivo != NULL) {
        while (fread(&veiculos[*totalVeiculos], sizeof(Veiculo), 1, arquivo) == 1) {
            (*totalVeiculos)++;
        }
        fclose(arquivo);
    }
}

void atualizarStatusVeiculos(Veiculo veiculos[], int totalVeiculos) {
    FILE *arquivo = fopen(ARQUIVO_VEICULOS, "wb");
    if (arquivo != NULL) {
        fwrite(veiculos, sizeof(Veiculo), totalVeiculos, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo de ve�culos.\n");
    }
}
