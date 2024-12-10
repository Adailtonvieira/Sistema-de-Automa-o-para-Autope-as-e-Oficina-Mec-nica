#ifndef EXIBIRESTOQUE_H
#define EXIBIRESTOQUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//remover espaços antes e depois de uma string
void trim(char *str) {
    char *end;

    //início
    while (*str == ' ') str++;

    //final
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;

    //Terminar a string corretamente
    *(end + 1) = '\0';
}

void exibir_estoque() {
    FILE *file;
    char linha[256];

    //Abrir arquivo estoque.txt
    file = fopen("estoque.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("\n\n");
    printf("######    ####    ######    ####     ####    ##  ##   ######\n");
    printf("##       ##  ##     ##     ##  ##   ##  ##   ##  ##   ##\n");
    printf("##       ##         ##     ##  ##   ##  ##   ##  ##   ##\n");
    printf("####      ####      ##     ##  ##   ##  ##   ##  ##   ####\n");
    printf("##           ##     ##     ##  ##   ##  ##   ##  ##   ##\n");
    printf("##       ##  ##     ##     ##  ##    ####    ##  ##   ##\n");
    printf("######    ####      ##      ####       ###    ####    ######\n");
    printf("\n\n");

    printf("%-25s | %10s | %10s | %4s\n", "NOME", "VALOR DE CUSTO", "VALORDE VENDA", "QUANTIDADE");
    printf("------------------------------------------------------------------------------------\n");

    //Leitura arquivo
    while (fgets(linha, sizeof(linha), file) != NULL) {
        char nome[100] = {0};
        float valor_de_venda_de_custo = 0.0, valor_de_venda = 0.0;
        int quantidade = 0;

        if (sscanf(linha, " %99[^|] | %f | %f | %d ", nome, &valor_de_venda_de_custo, &valor_de_venda, &quantidade) == 4) {
            //Limpar espaços ao redor do nome
            trim(nome);

            //linha formatada
            printf("%-25s | %14.2f | %13.2f | %4d\n", nome, valor_de_venda_de_custo, valor_de_venda, quantidade);
        } else {
            printf("Linha invalida ou mal formatada: %s", linha);
        }
    }

    fclose(file);
}

#endif
