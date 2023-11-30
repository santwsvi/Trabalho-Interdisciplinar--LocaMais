#include "cliente.h"
#include <string.h>
#define MAX_CLIENTES 100
#define ARQUIVO_CLIENTES "clientes.dat"
#define CLIENTES_TXT "clientes.txt"

// Fun��o para verificar se um cliente com o mesmo c�digo j� existe
int clienteExiste(Cliente clientes[], int totalClientes, int codigo) {
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].codigo == codigo) {
            return 1; // Cliente com o mesmo c�digo encontrado
        }
    }
    return 0; // Nenhum cliente com o mesmo c�digo encontrado
}

// Fun��o para cadastrar um cliente
void cadastrarCliente(Cliente clientes[], int *totalClientes) {
    // Verifica se h� espa�o para cadastrar mais clientes
    if (*totalClientes < MAX_CLIENTES) {
        Cliente novoCliente;

        // L� os dados do novo cliente do usu�rio
        do {
            printf("Digite o c�digo do cliente: ");
            scanf("%d", &novoCliente.codigo);

            // Verifica se o cliente com o mesmo c�digo j� existe
            if (clienteExiste(clientes, *totalClientes, novoCliente.codigo)) {
                printf("J� existe um cliente com este c�digo. Tente novamente.\n");
            }
        } while (clienteExiste(clientes, *totalClientes, novoCliente.codigo));

        printf("Digite o nome do cliente: ");
        scanf("%s", novoCliente.nome);

        // Limpando o buffer do teclado antes de ler o endere�o
        while (getchar() != '\n');

        printf("Digite o endere�o do cliente: ");
        fgets(novoCliente.endereco, sizeof(novoCliente.endereco), stdin);
        novoCliente.endereco[strcspn(novoCliente.endereco, "\n")] = '\0';  // Remover o caractere de nova linha do final

        printf("Digite o telefone do cliente: ");
        scanf("%s", novoCliente.telefone);

        // Adiciona o novo cliente ao array de clientes
        clientes[*totalClientes] = novoCliente;
        (*totalClientes)++;

           // Grava os clientes no arquivo
    FILE *arquivo = fopen(ARQUIVO_CLIENTES, "ab");
    if (arquivo != NULL) {
        fwrite(&novoCliente, sizeof(Cliente), 1, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo de clientes.\n");
    }

    // Adiciona o novo cliente ao arquivo de texto
    FILE *arquivoTexto = fopen(CLIENTES_TXT, "a");
    if (arquivoTexto != NULL) {
        fprintf(arquivoTexto, "C�digo: %d | Nome: %s | Endere�o: %s | Telefone: %s\n", novoCliente.codigo, novoCliente.nome, novoCliente.endereco, novoCliente.telefone);
        fclose(arquivoTexto);
    } else {
        printf("Erro ao abrir o arquivo de texto de clientes.\n");
    }

    printf("Cliente cadastrado com sucesso!\n");


    }
}


void carregarClientes(Cliente clientes[], int *totalClientes) {
    FILE *arquivo = fopen(ARQUIVO_CLIENTES, "rb");
if (arquivo != NULL) {
while (fread(&clientes[*totalClientes], sizeof(Cliente), 1, arquivo) == 1) {
(*totalClientes)++;
}
fclose(arquivo);
}
}
