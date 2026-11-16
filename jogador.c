#include <ncurses.h>
#include "jogo.h"

void moverJogador(int *linha, int *coluna, int comando) {
    if (comando == KEY_UP || comando == 'w' || comando == 'W') {
        (*linha)--;
    } else if (comando == KEY_DOWN || comando == 's' || comando == 'S') {
        (*linha)++;
    } else if (comando == KEY_LEFT || comando == 'a' || comando == 'A') {
        (*coluna)--;
    } else if (comando == KEY_RIGHT || comando == 'd' || comando == 'D') {
        (*coluna)++;
    }
}