#ifndef RETIRADA_H
#define RETIRADA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PECAS_RETIRADAS {
    char descricao[100];
    int quantidade;
    float valor_de_venda_de_compra;
    float valor_de_venda;
};

void listar_pecas_disponiveis() {
    FILE *file = fopen("estoque.txt", "r");
    char linha[256];
    int contador = 1; // Numero da peca

    if (file == NULL) {
        perror("Erro ao abrir o arquivo estoque.txt");
        return;
    }

    printf("Pecas disponiveis no estoque:\n");
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("%-4s | %-25s | %14s | %13s | %4s\n", "NUM", "NOME", "VALOR DE COMPRA", "VALOR DE VENDA", "QUANTIDADE");
    printf("-----------------------------------------------------------------------------------------------------\n");

    // Ler e exibir linhas do arquivo
    while (fgets(linha, sizeof(linha), file)) {
        char nome[100];
        float valor_de_venda_de_compra, valor_de_venda;
        int quantidade;

        if (sscanf(linha, " %99[^|] | %f | %f | %d ", nome, &valor_de_venda_de_compra, &valor_de_venda, &quantidade) == 4) {
            printf("%-4d | %-25s | %14.2f | %13.2f | %4d\n", contador, nome, valor_de_venda_de_compra, valor_de_venda, quantidade);
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

void registrar_retiradas(struct PECAS_RETIRADAS *pecas_retiradas, int *retiradas_pecas_retiradas) {
    listar_pecas_disponiveis();

    int escolha;
    printf("\nEscolha o numero da peca que deseja retirar: ");
    scanf("%d", &escolha);
    getchar(); // Limpar buffer do teclado

    FILE *estoque = fopen("estoque.txt", "r");
    FILE *temp = fopen("temp_estoque.txt", "w");
    FILE *file = fopen("retiradas_pecas_retiradas.txt", "a");

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
        char nome_estoque[100];
        int quantidade_estoque;
        float valor_de_venda_de_compra, valor_de_venda_de_venda;

        if (sscanf(linha, " %99[^|] | %f | %f | %d ", nome_estoque, &valor_de_venda_de_compra, &valor_de_venda_de_venda, &quantidade_estoque) == 4) {
            if (contador == escolha) {
                if (quantidade_estoque == 0) {
                    printf("A peca nao possui unidades em estoque e sera removida do cadastro de produtos.\n");
                    encontrado = 1; // Marcar como encontrada para evitar erro
                } else {
                    printf("\nVoce escolheu a peca: %s\n", nome_estoque);
                    printf("Digite a quantidade a ser retirada: ");
                    scanf("%d", &pecas_retiradas[*retiradas_pecas_retiradas].quantidade);
                    getchar();

                    if (quantidade_estoque >= pecas_retiradas[*retiradas_pecas_retiradas].quantidade) {
                        quantidade_estoque -= pecas_retiradas[*retiradas_pecas_retiradas].quantidade;

                        printf("Retirada registrada: %s \n (Quantidade retirada: %d, Restante: %d)\n",
                               nome_estoque,
                               pecas_retiradas[*retiradas_pecas_retiradas].quantidade,
                               quantidade_estoque);

                        fprintf(file, "%s | %.2f | %.2f | %d\n",
                                nome_estoque,
                                valor_de_venda_de_compra,
                                valor_de_venda_de_venda,
                                pecas_retiradas[*retiradas_pecas_retiradas].quantidade);
                        encontrado = 1;

                        // Se ainda ha quantidade no estoque, escreva no arquivo temporario
                        if (quantidade_estoque > 0) {
                            fprintf(temp, "%-25s | %14.2f | %13.2f | %4d\n", nome_estoque, valor_de_venda_de_compra, valor_de_venda_de_venda, quantidade_estoque);
                        } else {
                            printf("A peca foi removida completamente do estoque.\n");
                        }
                    } else {
                        printf("Quantidade insuficiente no estoque.\n");
                    }
                }
            } else {
                // Copiar linhas nao alteradas para o arquivo temporario
                fprintf(temp, "%-25s | %14.2f | %13.2f | %4d\n", nome_estoque, valor_de_venda_de_compra, valor_de_venda_de_venda, quantidade_estoque);
            }

            contador++;
        }
    }

    if (!encontrado) {
        printf("A peca escolhida nao foi encontrada ou ocorreu um erro.\n");
    }

    fclose(estoque);
    fclose(temp);
    fclose(file);

    remove("estoque.txt");
    rename("temp_estoque.txt", "estoque.txt");
}

#endif // RETIRADA_H
