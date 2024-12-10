#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include"limpartela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void fazerLogin(int *p) {
    FILE *file;
    char usuario[MAX_USUARIO], senha[MAX_SENHA];
    char usuario_input[MAX_USUARIO], senha_input[MAX_SENHA];
    int login_valido = 0;
    int ch;

    while (!login_valido) {
        file = fopen("usuarios.txt", "r");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        printf("\n  ####     #####     ####    ####    ##   ##\n");
        printf("  ##      ##   ##   ##  ##    ##     ###  ##\n");
        printf("  ##      ##   ##  ##         ##     #### ##\n");
        printf("  ##      ##   ##  ##         ##     ## ####\n");
        printf("  ##   #  ##   ##  ##  ###    ##     ##  ###\n");
        printf("  ##  ##  ##   ##   ##  ##    ##     ##   ##\n");
        printf("  ######   #####     #####   ####    ##   ##\n");
        printf("\n");
        printf("Digite o nome de usuario: ");
        fgets(usuario_input, sizeof(usuario_input), stdin);
        usuario_input[strcspn(usuario_input, "\n")] = 0;

        printf("Digite a senha: ");
        int i = 0;
        while (i < MAX_SENHA - 1) {
            ch = getch();

            if (ch == '\r') {
                break; // Enter pressionado
            } else if (ch == '\b') {
                if (i > 0) {
                    i--;
                    printf("\b \b"); // Apagar o último caractere visível
                }
            } else {
                senha_input[i++] = ch;
                printf("*"); // Exibir asterisco ao invés do caractere
            }
        }

        senha_input[i] = '\0';
        printf("\n");

        // Verificar credenciais
        while (fscanf(file, "%s %s", usuario, senha) != EOF) {
            if (strcmp(usuario_input, usuario) == 0 && strcmp(senha_input, senha) == 0) {
                login_valido = 1;
                break;
            }
        }

        if (login_valido) {
            printf("\nLogin bem-sucedido!\n");
            *p = 5;
        } else {
            printf("\nUsuario ou senha incorretos! Tente novamente.\n\n");
        }
        

        fclose(file);
    }
}

#endif
