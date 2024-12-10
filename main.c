#include <stdio.h>
#include <string.h>
#include <conio.h>
#define MAX_USUARIO 50
#define MAX_SENHA 50
#include "login.h"
#include "registrar.h"
#include "limpartela.h"
#include "vendas.h"
#include "retirada.h"
#include "exibirestoque.h"
#include <windows.h>
#include "adicionada.h"

void menu_gerenciamento(struct PECAS_VENDIDAS *pecas, struct PECAS_RETIRADAS *pecas_retiradas, struct PECAS_ADICIONADAS *pecas_added, int *venda_pecas, int *retiradas_pecas_retiradas, int *add_pecas);

int main() {
    int opcao = 0;
    struct PECAS_VENDIDAS pecas[100];
    struct PECAS_RETIRADAS pecas_retiradas[100];
    struct PECAS_ADICIONADAS pecas_added[100];
    int venda_pecas = 0;
    int retiradas_pecas_retiradas = 0;
    int add_pecas = 0;

    do {
        printf("*   ####    ######     ##     #####    ##  ##   ##### *\n");
        printf("*  ##  ##   ##        ####    ##  ##   ##  ##   ##  ## *\n");
        printf("*  ##       ##       ##  ##   ##  ##   ##  ##   ##  ## *\n");
        printf("*  ## ###   ####     ######   #####    ##  ##   ##### *\n");
        printf("*  ##  ##   ##       ##  ##   ####     ##  ##   ## *\n");
        printf("*  ##  ##   ##       ##  ##   ## ##    ##  ##   ## *\n");
        printf("*   ####    ######   ##  ##   ##  ##    ####    ## *\n");
        printf("\n");

        printf("SEJA BEM VINDO! O QUE DESEJA FAZER?\n");
        printf("\n");
        printf("1. Registrar novo usuario\n");
        printf("2. Fazer login\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            getchar(); // Limpa o buffer
            continue;
        }

        getchar(); // Limpar buffer

        switch (opcao) {
        case 1:
            registrarUsuario();
            Sleep(1000);
            limpartela();
            break;
        case 2:
            fazerLogin(&opcao);
            Sleep(1000);
            limpartela();
            menu_gerenciamento(pecas, pecas_retiradas, pecas_added, &venda_pecas, &retiradas_pecas_retiradas, &add_pecas);
            break;
        case 3:
            printf("Saindo...\n");
            Sleep(500);
            limpartela();
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            limpartela();
        }
    } while (opcao != 3);

    return 0;
}

void menu_gerenciamento(struct PECAS_VENDIDAS *pecas, struct PECAS_RETIRADAS *pecas_retiradas, struct PECAS_ADICIONADAS *pecas_added, int *venda_pecas, int *retiradas_pecas_retiradas, int *add_pecas) {
    int opcao;

    do {
        limpartela();
        printf("*   ####    ######   #####    ######   ##  ##    ####     ####      ##     ##   ##  ######   ##  ##   ######    #### *\n");
        printf("*  ##  ##   ##       ##  ##   ##       ### ##   ##  ##     ##      ####    ### ###  ##       ### ##     ##     ##  ## *\n");
        printf("*  ##       ##       ##  ##   ##       ######   ##         ##     ##  ##   #######  ##       ######     ##     ##  ## *\n");
        printf("*  ## ###   ####     #####    ####     ######   ##         ##     ######   ## # ##  ####     ######     ##     ##  ## *\n");
        printf("*  ##  ##   ##       ####     ##       ## ###   ##         ##     ##  ##   ##   ##  ##       ## ###     ##     ##  ## *\n");
        printf("*  ##  ##   ##       ## ##    ##       ##  ##   ##  ##     ##     ##  ##   ##   ##  ##       ##  ##     ##     ##  ## *\n");
        printf("*   ####    ######   ##  ##   ######   ##  ##    ####     ####    ##  ##   ##   ##  ######   ##  ##     ##      #### *\n");

        printf("\nESCOLHA UMA OPCAO:\n");
        printf("1. Entrada de pecas\n");
        printf("2. Retirada de pecas\n");
        printf("3. Venda de pecas\n");
        printf("4. Consulta de estoque\n");
        printf("5. Gerar extrato de vendas\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            getchar(); // Limpa o buffer
            continue;
        }

        getchar(); // Limpar buffer

        switch (opcao) {
        case 1:
            do {
                registrar_add(pecas_added, add_pecas);
                printf("\nDeseja adicionar outro produto? (1 - Sim, qualquer outra tecla - Nao): \n");
                if (getch() != '1') break;
            } while (1);
            break;
        case 2:
            do {
                registrar_retiradas(pecas_retiradas, retiradas_pecas_retiradas);
                printf("\nDeseja retirar outro produto? (1 - Sim, qualquer outra tecla - Nao): \n");
                if (getch() != '1') break;
            } while (1);
            break;
        case 3:
            do {
                registrar_venda(pecas, venda_pecas);
                printf("\nDeseja vender outro produto? (1 - Sim, qualquer outra tecla - Nao): \n");
                if (getch() != '1') break;
            } while (1);
            break;
        case 4:
            exibir_estoque();
            printf("\nPressione qualquer tecla para continuar...");
            getch();
            break;
        case 5:
            gerar_extrato_vendas();
            printf("\nPressione qualquer tecla para continuar...");
            getch();
            break;
        case 6:
            printf("Voltando ao menu principal...\n");
            Sleep(500);
            return;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (1);
}
