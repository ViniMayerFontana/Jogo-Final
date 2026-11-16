#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include "jogo.h"

#define ARQUIVO_MAPA "mapas/mapa1.txt"

int main(void) {
    Jogo jogo;
    int comando, resultado, jogarDeNovo;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    do {
        if (!carregarMapa(ARQUIVO_MAPA, &jogo)) {
            endwin();
            printf("Erro ao carregar %s: %s.\n", ARQUIVO_MAPA, jogo.mensagem);
            return 1;
        }

        if (!telaCabe(&jogo)) {
            endwin();
            printf("Terminal pequeno para este mapa: aumente a janela.\n");
            return 1;
        }

        jogo.cristais = 0;
        jogo.turnos = 0;
        jogo.mensagem[0] = '\0';
        resultado = EM_ANDAMENTO;

        while (resultado == EM_ANDAMENTO) {
            desenharJogo(&jogo);
            comando = getch();
            jogo.mensagem[0] = '\0';

            if (comando == 'q' || comando == 'Q') {
                resultado = DESISTENCIA;
            } else if (movimentoValido(&jogo, comando)) {
                moverJogador(&jogo.linhaJ, &jogo.colunaJ, comando);
                jogo.energia--;
                jogo.turnos++;
                processarCasa(&jogo);

                if (chegouNaSaida(&jogo)) {
                    if (jogo.cristais >= jogo.minimoCristais) {
                        resultado = VITORIA;
                    } else {
                        snprintf(jogo.mensagem, TAM_MSG,
                                 "Faltam %d cristal(is) para sair!",
                                 jogo.minimoCristais - jogo.cristais);
                    }
                }

                if (resultado == EM_ANDAMENTO && jogo.energia <= 0) {
                    resultado = DERROTA;
                }
            } else {
                strcpy(jogo.mensagem, "Movimento invalido!");
            }
        }

        jogarDeNovo = mostrarFimDeJogo(&jogo, resultado);
    } while (jogarDeNovo);

    endwin();
    return 0;
}