// locacoesCliente.c

#include "locacoesCliente.h"
#include "cliente.h"
#include <stdio.h>

void mostrarLocacoesCliente(Locacao locacoes[], int totalLocacoes, Cliente clientes[], int totalClientes) {
    int codigoCliente;
    int encontrou = 0;

    // Solicitar ao usu�rio o c�digo ou nome do cliente
    printf("Digite o c�digo do cliente: ");
    scanf("%d", &codigoCliente);

    // Procurar o cliente pelo c�digo
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].codigo == codigoCliente) {
            encontrou = 1;
            printf("Loca��es para o cliente %s:\n", clientes[i].nome);

            // Exibir todas as loca��es associadas a esse cliente
            for (int j = 0; j < totalLocacoes; j++) {
                if (locacoes[j].codigo_cliente == clientes[i].codigo) {
                    printf("C�digo Loca��o: %d | Data Retirada: %s | Data Devolu��o: %s | Seguro: %s | Qtd Dias: %d | C�digo Ve�culo: %d\n",
                           locacoes[j].codigo, locacoes[j].data_retirada, locacoes[j].data_devolucao,
                           (locacoes[j].seguro == 1) ? "Sim" : "N�o", locacoes[j].qtd_dias, locacoes[j].codigo_veiculo);
                }
            }

            break;  // Cliente encontrado, encerrar o loop
        }
    }

    if (!encontrou) {
        printf("Cliente n�o encontrado.\n");
    }
}
