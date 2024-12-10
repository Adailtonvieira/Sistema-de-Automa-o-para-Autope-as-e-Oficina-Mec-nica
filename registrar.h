#ifndef REGISTRAR_H_INCLUDED
#define REGISTRAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void registrarUsuario() {
    FILE *file = fopen("usuarios.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char usuario[MAX_USUARIO], senha[MAX_SENHA];
    int i = 0, ch;

printf("*  #####    ######    ####     ####     ####    ######   #####     #### *\n");
printf("*  ##  ##   ##       ##  ##     ##     ##  ##     ##     ##  ##   ##  ## *\n");
printf("*  ##  ##   ##       ##         ##     ##         ##     ##  ##   ##  ## *\n");
printf("*  #####    ####     ## ###     ##      ####      ##     #####    ##  ## *\n");
printf("*  ####     ##       ##  ##     ##         ##     ##     ####     ##  ## *\n");
printf("*  ## ##    ##       ##  ##     ##     ##  ##     ##     ## ##    ##  ## *\n");
printf("*  ##  ##   ######    ####     ####     ####      ##     ##  ##    #### *\n");
    printf("\n");
    printf("\n");

    printf("Digite o nome de usuario: ");
    fgets(usuario, sizeof(usuario), stdin);
    usuario[strcspn(usuario, "\n")] = 0;

    printf("Digite a senha: ");
    while( i < MAX_SENHA - 1){
        ch = getch();

        if (ch =='\r'){
            break;
        } else if (ch == '\b'){
            if (i > 0){
                i--;
                printf("\b \b");
            }
        } else {
            senha[i++] = ch;
            printf("*");
        }
    }
    senha[i] = '\0';


    fprintf(file, "%s %s\n", usuario, senha);
    fclose(file);

    printf("\nUsuario registrado com sucesso!\n");
}


#endif // REGISTRAR_H_INCLUDED