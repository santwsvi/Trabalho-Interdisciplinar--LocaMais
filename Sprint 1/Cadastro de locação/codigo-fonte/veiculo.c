#include "veiculo.h"
#include <string.h>

#define MAX_VEICULOS 100
#define ARQUIVO_VEICULOS "veiculos.dat"
#define VEICULOS_TXT "veiculos.txt"


int veiculoExiste(Veiculo veiculos[], int totalVeiculos, int codigo) {
        for (int i = 0; i < totalVeiculos; i++) {
        if (veiculos[i].codigo == codigo) {
            return 1; // Ve�culo com o mesmo c�digo encontrado
        }
    }
    return 0; // Nenhum ve�culo com o mesmo c�digo encontrado
}

void cadastrarVeiculo(Veiculo veiculos[], int *totalVeiculos) {
      // Verifica se h� espa�o para cadastrar mais ve�culos
    if (*totalVeiculos < MAX_VEICULOS) {
        Veiculo novoVeiculo;

        // L� os dados do novo ve�culo do usu�rio
        do {
            printf("Digite o c�digo do ve�culo: ");
            scanf("%d", &novoVeiculo.codigo);

            // Verifica se o ve�culo com o mesmo c�digo j� existe
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
        scanf("%s", novoVeiculo.cor);
        printf("Digite a placa do ve�culo: ");
        scanf("%s", novoVeiculo.placa);
        printf("Digite o valor da di�ria do ve�culo: ");
        scanf("%f", &novoVeiculo.valor_diaria);
        printf("Digite a capacidade de ocupantes do ve�culo: ");
        scanf("%d", &novoVeiculo.ocupantes);
        printf("Digite o status do ve�culo (alugado, dispon�vel, em manuten��o): ");
        scanf("%s", novoVeiculo.status);

        // Adiciona o novo ve�culo ao array de ve�culos
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

            // Adiciona o novo cliente ao arquivo de texto
    FILE *arquivoTexto = fopen(VEICULOS_TXT, "a");
    if (arquivoTexto != NULL) {
        fprintf(arquivoTexto, "C�digo do veiculo: %d | Descri��o : %s | Modelo : %s | Cor : %s | Placa: %s | Valor di�ria: %d | Quantidade de ocupantes: %d | Status: % s |\n", novoVeiculo.codigo, novoVeiculo.descricao, novoVeiculo.modelo, novoVeiculo.cor, novoVeiculo.placa, novoVeiculo.valor_diaria, novoVeiculo.ocupantes, novoVeiculo.status);
        fclose(arquivoTexto);
    } else {
        printf("Erro ao abrir o arquivo de texto de veiculos.\n");
    }

        printf("Ve�culo cadastrado com sucesso!\n");
        }

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

