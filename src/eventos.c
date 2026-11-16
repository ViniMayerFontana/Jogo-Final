#include "jogo.h"
#include <string.h>

void processarCasa(Jogo *j) {
    switch (j->mapa[j->linhaJ][j->colunaJ]){

        case 'C':
            j->cristais++;
            j->mapa[j->linhaJ][j->colunaJ] = '.';
            strcpy(j->mensagem, "Cristal coletado! (+1 cristal)");
        break;

        case 'R':
            j->energia += 5;
            j->mapa[j->linhaJ][j->colunaJ] = '.';
            strcpy(j->mensagem, "Recuperacao! (+5 de folego)");
        break;

        case 'A':
            if (j->energia > 2){
                j->energia -= 3;
            }
            else{
                j->energia = 0;
            }
            strcpy(j->mensagem, "Armadilha! (-3 de folego)");
            j->mapa[j->linhaJ][j->colunaJ] = '.';
        break;

        case 'E':
            j->cristais++;
            j->energia += 5;
            strcpy(j->mensagem, "Evento especial! (+1 cristal e +5 de folego)");
            j->mapa[j->linhaJ][j->colunaJ] = '.';
        break;
        
        default:
        break;
    }
}

int chegouNaSaida(Jogo *j) {
    (void)j;
    return 0;
}

int mostrarFimDeJogo(Jogo *j, int resultado) {
    (void)j;
    (void)resultado;
    return 0;
}