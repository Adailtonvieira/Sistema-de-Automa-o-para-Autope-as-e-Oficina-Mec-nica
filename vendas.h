#ifndef VENDAS_H
#define VENDAS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para pecas vendidas
struct PECAS_VENDIDAS {
    char descricao[100];
    int quantidade;
    float valor_de_venda_de_compra; // valor_de_venda_de_compra de custo
    float valor_de_venda; // valor_de_venda_de_compra de venda
};

// Funcao para remover espacos antes e depois de uma string
void trim2(char *str) {
    char *end;

    // Remover espacos do inicio
    while (*str == ' ') str++;

    // Remover espacos do final
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;

    // Terminar a string corretamente
    *(end + 1) = '\0';
}

// Funcao para listar pecas disponiveis para venda
void listar_pecas_disponiveis_venda() {
    FILE *file = fopen("estoque.txt", "r");
    char linha[256];
    int contador = 1; // Numero da peca

    if (file == NULL) {
        perror("Erro ao abrir o arquivo estoque.txt");
        return;
    }

    printf("Pecas disponiveis para venda:\n");
    printf("-------------------------------------------------------------\n");
    printf("%-5s | %-25s | %15s | %15s | %10s\n", "CODIGO", "NOME", "VALOR DE CUSTO", "VALOR DE VENDA", "QUANTIDADE");
    printf("-------------------------------------------------------------\n");

    // Ler e exibir linhas do arquivo
    while (fgets(linha, sizeof(linha), file)) {
        char nome[100];
        float valor_de_venda_de_compra, valor_de_venda;
        int quantidade;

        // Verificar se a linha esta no formato esperado
        if (sscanf(linha, " %99[^|] | %f | %f | %d ", nome, &valor_de_venda_de_compra, &valor_de_venda, &quantidade) == 4) {
            trim2(nome); // Garantir que o nome esta limpo
            printf("%-5d | %-25s | %15.2f | %15.2f | %10d\n", contador, nome, valor_de_venda_de_compra, valor_de_venda, quantidade);
            contador++;
        } else {
            printf("Erro ao processar linha: %s", linha);
        }
    }

    fclose(file);

    if (contador == 1) {
        printf("Nenhuma peca disponivel no estoque.\n");
    }
}

// Funcao para registrar vendas
void registrar_venda(struct PECAS_VENDIDAS *pecas, int *venda_pecas) {
    listar_pecas_disponiveis_venda();

    int escolha;
    printf("\nDigite o codigo da peca que deseja vender: ");
    scanf("%d", &escolha);
    getchar(); // Limpar buffer do teclado

    FILE *estoque = fopen("estoque.txt", "r");
    FILE *temp = fopen("temp_estoque.txt", "w");
    FILE *file = fopen("venda_pecas.txt", "a");

    if (!estoque || !temp || !file) {
        perror("Erro ao abrir um dos arquivos necessarios.");
        if (estoque) fclose(estoque);
        if (temp) fclose(temp);
        if (file) fclose(file);
        return;
    }

    char linha[256];
    int contador = 1;
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), estoque)) {
        char descricao_estoque[100];
        int quantidade_estoque;
        float valor_de_venda_de_compra_unitario, valor_de_venda_unitario;

        if (sscanf(linha, " %99[^|] | %f | %f | %d ", descricao_estoque, &valor_de_venda_de_compra_unitario, &valor_de_venda_unitario, &quantidade_estoque) == 4) {
            trim2(descricao_estoque); // Limpar espacos extras do nome

            if (contador == escolha) {
                printf("\nVoce escolheu a peca: %s\n", descricao_estoque);
                printf("Digite a quantidade a ser vendida: ");
                scanf("%d", &pecas[*venda_pecas].quantidade);
                getchar();

                if (quantidade_estoque >= pecas[*venda_pecas].quantidade) {
                    quantidade_estoque -= pecas[*venda_pecas].quantidade;

                    // Calcular a renda como diferenca entre valor_de_venda de venda e custo
                    float custo_total = valor_de_venda_de_compra_unitario * pecas[*venda_pecas].quantidade;
                    float venda_total = valor_de_venda_unitario * pecas[*venda_pecas].quantidade;
                    float renda = venda_total - custo_total;

                    printf("Venda registrada: %s\nQuantidade Vendida: %d\nRestante no Estoque: %d\nLucro: R$ %.2f\n",
                           descricao_estoque,
                           pecas[*venda_pecas].quantidade,
                           quantidade_estoque,
                           renda);

                    fprintf(file, "%s | %.2f | %.2f | %d | %.2f\n",
                            descricao_estoque,
                            valor_de_venda_de_compra_unitario,
                            valor_de_venda_unitario,
                            pecas[*venda_pecas].quantidade,
                            renda);
                    encontrado = 1;
                } else {
                    printf("Quantidade insuficiente no estoque para a peca: %s.\n", descricao_estoque);
                }
            }

            fprintf(temp, "%-25s | %10.2f | %10.2f | %10d\n", descricao_estoque, valor_de_venda_de_compra_unitario, valor_de_venda_unitario, quantidade_estoque);
            contador++;
        }
    }

    if (!encontrado) {
        printf("A peca escolhida nao foi encontrada ou nao ha unidades suficientes no estoque.\n");
    }

    fclose(estoque);
    fclose(temp);
    fclose(file);

    remove("estoque.txt");
    rename("temp_estoque.txt", "estoque.txt");
}

// Funcao para gerar extrato de vendas
void gerar_extrato_vendas() {
    FILE *file = fopen("venda_pecas.txt", "r");
    char linha[256];
    float renda_total = 0.0;

    if (file == NULL) {
        perror("Erro ao abrir o arquivo venda_pecas.txt");
        return;
    }

    printf("\nExtrato de vendas:\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("%-25s | %14s | %13s | %4s | %10s\n", "NOME", "VALOR DE CUSTO", "VALOR DE VENDA", "QTD", "LUCRO");
    printf("------------------------------------------------------------------------------------------------\n");

    // Ler e exibir linhas do arquivo
    while (fgets(linha, sizeof(linha), file)) {
        char nome[100];
        float valor_de_venda_de_compra, valor_de_venda, lucro;
        int quantidade;

        if (sscanf(linha, " %99[^|] | %f | %f | %d | %f ", nome, &valor_de_venda_de_compra, &valor_de_venda, &quantidade, &lucro) == 5) {
            trim2(nome);
            printf("%-25s | %14.2f | %14.2f | %5d | %10.2f\n", nome, valor_de_venda_de_compra, valor_de_venda, quantidade, lucro);
            renda_total += lucro;
        }
    }

    printf("-------------------------------------------------------------\n");
    printf("\t\tRenda total ate o momento: R$ %.2f\n\n", renda_total);

    fclose(file);
}

#endif // VENDAS_H
