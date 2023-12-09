// relatorio.c

#include "relatorio.h"
#include "cliente.h"
#include "veiculo.h"
#include "locacao.h"
#include <stdio.h>

void gerarRelatorio(Cliente clientes[], int totalClientes, Veiculo veiculos[], int totalVeiculos, Locacao locacoes[], int totalLocacoes) {
    // Gerar relat�rio de clientes
    printf("Relat�rio de Clientes:\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("C�digo: %d | Nome: %s | Endere�o: %s | Telefone: %s\n", clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
    }

    // Gerar relat�rio de ve�culos
    printf("\nRelat�rio de Ve�culos:\n");
    for (int i = 0; i < totalVeiculos; i++) {
        printf("C�digo: %d | Descri��o: %s | Modelo: %s | Cor: %s | Placa: %s | Valor Di�ria: %.2f | Ocupantes: %d | Status: %s\n", veiculos[i].codigo, veiculos[i].descricao, veiculos[i].modelo, veiculos[i].cor, veiculos[i].placa, veiculos[i].valor_diaria, veiculos[i].ocupantes, veiculos[i].status);
    }

    // Gerar relat�rio de loca��es
    printf("\nRelat�rio de Loca��es:\n");
    for (int i = 0; i < totalLocacoes; i++) {
        printf("C�digo: %d | Data Retirada: %s | Data Devolu��o: %s | Seguro: %s | Qtd Dias: %d | C�digo Cliente: %d | C�digo Ve�culo: %d\n", locacoes[i].codigo, locacoes[i].data_retirada, locacoes[i].data_devolucao, (locacoes[i].seguro == 1) ? "Sim" : "N�o", locacoes[i].qtd_dias, locacoes[i].codigo_cliente, locacoes[i].codigo_veiculo);
    }
}

