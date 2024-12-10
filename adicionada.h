#ifndef ADICIONADA_H
#define ADICIONADA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PECAS_ADICIONADAS {
    char nome[50];
    int quantidade;
    float preco;
    float valor;
};

void registrar_add(struct PECAS_ADICIONADAS *pecas_added, int *add_pecas) {
    FILE *estoque = fopen("estoque.txt", "r");
    FILE *temp = fopen("temp_estoque.txt", "w");
    FILE *file = fopen("add_pecas.txt", "a");

    //Verificar erros de abertura de arquivos
    if (!estoque) {
        perror("Erro ao abrir estoque.txt");
        if (temp) fclose(temp);
        if (file) fclose(file);
        return;
    }

    if (!temp) {
        perror("Erro ao abrir temp_estoque.txt");
        fclose(estoque);
        if (file) fclose(file);
        return;
    }

    if (!file) {
        perror("Erro ao abrir add_pecas.txt");
        fclose(estoque);
        fclose(temp);
        return;
    }

    //dados ao usuário
    printf("Digite o nome da peca: ");
    fgets(pecas_added[*add_pecas].nome, sizeof(pecas_added[*add_pecas].nome), stdin);
    pecas_added[*add_pecas].nome[strcspn(pecas_added[*add_pecas].nome, "\n")] = 0; // Remover \n

    printf("Digite o valor de custo: ");
    if (scanf("%f", &pecas_added[*add_pecas].preco) != 1) {
        printf("Erro ao ler o preco.\n");
        fclose(estoque);
        fclose(temp);
        fclose(file);
        return;
    }

    printf("Digite o valor de venda: ");
    if (scanf("%f", &pecas_added[*add_pecas].valor) != 1) {
        printf("Erro ao ler o valor.\n");
        fclose(estoque);
        fclose(temp);
        fclose(file);
        return;
    }

    printf("Digite a quantidade adicionada: ");
    if (scanf("%d", &pecas_added[*add_pecas].quantidade) != 1) {
        printf("Erro ao ler a quantidade.\n");
        fclose(estoque);
        fclose(temp);
        fclose(file);
        return;
    }
    printf("\t\t\nProduto adicionado com sucesso!\n");

    getchar();

    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), estoque)) {
        char nome_estoque[50];
        int quantidade_estoque;
        float preco_unitario, valor_unitario;

        if (sscanf(linha, " %49[^|] | %f | %f | %d ", nome_estoque, &preco_unitario, &valor_unitario, &quantidade_estoque) == 4) {
            if (strcmp(nome_estoque, pecas_added[*add_pecas].nome) == 0) {
                quantidade_estoque += pecas_added[*add_pecas].quantidade;
                printf("Entrada registrada: %s (Quantidade adicionada: %d, Total: %d)\n",
                       pecas_added[*add_pecas].nome, pecas_added[*add_pecas].quantidade, quantidade_estoque);
                fprintf(temp, "%-25s | %-10.2f | %-10.2f | %-4d\n",
                        nome_estoque, preco_unitario, valor_unitario, quantidade_estoque);
                encontrado = 1;
            } else {
                fprintf(temp, "%-25s | %-10.2f | %-10.2f | %-4d\n",
                        nome_estoque, preco_unitario, valor_unitario, quantidade_estoque);
            }
        }
    }

    // Adicionar nova peça, se não encontrada
    if (!encontrado) {
        fprintf(temp, "%-25s | %-10.2f | %-10.2f | %-4d\n",
                pecas_added[*add_pecas].nome, pecas_added[*add_pecas].preco,
                pecas_added[*add_pecas].valor, pecas_added[*add_pecas].quantidade);
    }

    fclose(estoque);
    fclose(temp);
    fclose(file);

    // Substituir o arquivo original pelo atualizado
    if (remove("estoque.txt") != 0) {
        perror("Erro ao remover estoque.txt");
    }
    if (rename("temp_estoque.txt", "estoque.txt") != 0) {
        perror("Erro ao renomear temp_estoque.txt");
    }

    (*add_pecas)++;
}
#endif // ADICIONADA_H
