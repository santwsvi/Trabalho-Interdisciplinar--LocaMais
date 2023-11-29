#include "locacao.h"
#include "cliente.h"
#include <string.h>
#include "veiculo.h"
#define MAX_LOCACOES 100
#define ARQUIVO_LOCACOES "locacoes.dat"
#define LOCACOES_TXT "locacoes.txt"

int locacaoExiste(Locacao locacoes[], int totalLocacoes, int codigo) {
    for (int i = 0; i < totalLocacoes; i++) {
        if (locacoes[i].codigo == codigo) {
            return 1; // Loca��o com o mesmo c�digo encontrado
        }
    }
    return 0; // Nenhuma loca��o com o mesmo c�digo encontrado
}

void carregarClientes(Cliente clientes[], int *totalClientes);

void cadastrarLocacao(Locacao locacoes[], int *totalLocacoes, Cliente clientes[], int totalClientes, Veiculo veiculos[], int totalVeiculos) {
    // Verifica se h� espa�o para cadastrar mais loca��es
    if (*totalLocacoes < MAX_LOCACOES) {
        Locacao novaLocacao;
        // L� os dados da nova loca��o do usu�rio
        do {
            printf("Digite o c�digo da loca��o: ");
            scanf("%d", &novaLocacao.codigo);

            // Limpar o buffer ap�s a leitura do inteiro
            while (getchar() != '\n');

            // Verifica se a loca��o com o mesmo c�digo j� existe
            if (locacaoExiste(locacoes, *totalLocacoes, novaLocacao.codigo)) {
                printf("J� existe uma loca��o com este c�digo. Tente novamente.\n");
            }
        } while (locacaoExiste(locacoes, *totalLocacoes, novaLocacao.codigo));

        printf("Digite o nome do cliente: ");
        char nomeCliente[50];
        scanf("%s", nomeCliente);

        // Procura o cliente pelo nome
        int codigoCliente = -1;
        int nomeDoCliente = "";
        for (int i = 0; i < totalClientes; i++) {
            if (strcmp(clientes[i].nome, nomeCliente) == 0) {
                codigoCliente = clientes[i].codigo;
                nomeDoCliente = clientes[i].nome;
                break;
            }
        }

        if (codigoCliente == -1) {
            printf("Cliente n�o encontrado. Cadastre o cliente antes de fazer a loca��o.\n");
            return;
        }

        novaLocacao.codigo_cliente = codigoCliente;

        // Apresenta um menu de ve�culos dispon�veis para o cliente escolher
printf("Ve�culos dispon�veis:\n");
for (int i = 0; i < totalVeiculos; i++) {
    if (strcmp(veiculos[i].status, "dispon�vel") != 0) {
        printf("%d - %s\n", veiculos[i].codigo, veiculos[i].descricao);
    }
}

int escolhaVeiculo;
printf("Escolha o c�digo do ve�culo desejado: ");
scanf("%d", &escolhaVeiculo);

        // Verifica se o ve�culo escolhido est� dispon�vel
        int codigoVeiculoEscolhido = 0;
        for (int i = 0; i < totalVeiculos; i++) {
            if (veiculos[i].codigo == escolhaVeiculo && strcmp(veiculos[i].status, "dispon�vel") == 0 && veiculos[i].ocupantes >= 1) {
                codigoVeiculoEscolhido = escolhaVeiculo;

                break;
            }
        }



        if (codigoVeiculoEscolhido == -1) {
            printf("Ve�culo escolhido n�o est� dispon�vel ou n�o existe. Cancelando loca��o.\n");
            return;
        }

        novaLocacao.codigo_veiculo = codigoVeiculoEscolhido;

        // Continua��o do restante do c�digo...

        printf("Digite a data de retirada (DD/MM/AAAA): ");
        fgets(novaLocacao.data_retirada, sizeof(novaLocacao.data_retirada), stdin);
        novaLocacao.data_retirada[strcspn(novaLocacao.data_retirada, "\n")] = '\0'; // Remover o caractere de nova linha do final

        while (getchar() != '\n');

        printf("Digite a data de devolu��o (DD/MM/AAAA): ");
        fgets(novaLocacao.data_devolucao, sizeof(novaLocacao.data_devolucao), stdin);
        novaLocacao.data_devolucao[strcspn(novaLocacao.data_devolucao, "\n")] = '\0'; // Remover o caractere de nova linha do final

        // Restante do c�digo...

        // Procura um ve�culo dispon�vel para a loca��o
        int codigoVeiculo;
        int nomeDoVeiculo = "";
        for (int i = 0; i < totalVeiculos; i++) {
            if (strcmp(veiculos[i].status, "dispon�vel") != 0 && veiculos[i].ocupantes >= 1) {
                codigoVeiculo = veiculos[i].codigo;
                nomeDoVeiculo = veiculos[i].descricao;
                break;
            }
        }

        if (codigoVeiculo == -1) {
            printf("Nenhum ve�culo dispon�vel atende aos requisitos da loca��o.\n");
            return;
        }

        novaLocacao.codigo_veiculo = codigoVeiculo;

        printf("Deseja contratar seguro para o ve�culo? (1 - Sim / 0 - N�o): ");
        scanf("%d", &novaLocacao.seguro);

        // Calcula a quantidade de di�rias com base nas datas de retirada e devolu��o
        // (assumindo que as datas est�o em um formato adequado, sem valida��o completa neste exemplo)
        // Aqui, considerei que a quantidade de di�rias � igual ao n�mero de dias entre as datas.
        // Em uma implementa��o real, voc� precisaria lidar com datas de maneira mais sofisticada.
        int diasRetirada, mesesRetirada, anosRetirada;
        int diasDevolucao, mesesDevolucao, anosDevolucao;

        sscanf(novaLocacao.data_retirada, "%d/%d/%d", &diasRetirada, &mesesRetirada, &anosRetirada);
        sscanf(novaLocacao.data_devolucao, "%d/%d/%d", &diasDevolucao, &mesesDevolucao, &anosDevolucao);
        novaLocacao.qtd_dias = (diasDevolucao - diasRetirada) + 30 * (mesesDevolucao - mesesRetirada) + 365 * (anosDevolucao - anosRetirada);

        // Adiciona a nova loca��o ao array de loca��es
        locacoes[*totalLocacoes] = novaLocacao;
        (*totalLocacoes)++;

        // Atualiza o status do ve�culo para "alugado"
        for (int i = 0; i < totalVeiculos; i++) {
            if (veiculos[i].codigo == codigoVeiculo) {
                strcpy(veiculos[i].status, "alugado");
                break;
            }
        }

        // Grava as loca��es no arquivo
        FILE *arquivo = fopen(ARQUIVO_LOCACOES, "ab");
        if (arquivo != NULL) {
            fwrite(&novaLocacao, sizeof(Locacao), 1, arquivo);
            fclose(arquivo);
        } else {
            printf("Erro ao abrir o arquivo de loca��es.\n");
        }

        // Adiciona uma nova loca��o a um arquivo de texto
        FILE *arquivoTexto = fopen(LOCACOES_TXT, "a");
        if (arquivoTexto != NULL) {
            fprintf(arquivoTexto, "C�digo da loca��o: %d | Nome do cliente: %s | C�digo do cliente: %d | Nome do ve�culo: %s | Data de retirada: %s | Data de devolu��o: %s | Di�rias: %d | Seguro: %d |\n", novaLocacao.codigo, nomeDoCliente, novaLocacao.codigo_cliente, nomeDoVeiculo, novaLocacao.data_retirada, novaLocacao.data_devolucao, novaLocacao.qtd_dias, novaLocacao.seguro);
            fclose(arquivoTexto);
        } else {
            printf("Erro ao abrir o arquivo de texto de loca��es.\n");
        }

        printf("Loca��o cadastrada com sucesso!\n");

    } else {
        printf("Limite de loca��es atingido!\n");
    }
}

void carregarLocacoes(Locacao locacoes[], int *totalLocacoes) {
    FILE *arquivo = fopen(ARQUIVO_LOCACOES, "rb");
if (arquivo != NULL) {
while (fread(&locacoes[*totalLocacoes], sizeof(Locacao), 1, arquivo) == 1) {
(*totalLocacoes)++;
}
fclose(arquivo);
}
}

