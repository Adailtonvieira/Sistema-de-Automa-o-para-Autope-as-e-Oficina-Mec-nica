#ifndef LIMPAR_TELA_H
#define LIMPAR_TELA_H

#include <stdlib.h>


void limpartela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

#endif