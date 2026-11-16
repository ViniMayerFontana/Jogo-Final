#include <ncurses.h>
#include <string.h>
#include "jogo.h"

/* Funcoes auxiliares internas (static) adaptadas do seu hudInfos.c */
static void desenharLinhaChars(int n, char c) {
    for (int i = 0; i < n; i++) {
        addch(c);
    }
}

static void desenharBarraFolego(int atual, int maxima) {
    int larguraBarra = 20; /* tamanho fixo da barra para caber bem no terminal 80x24 */
    int cheios = 0;

    if (maxima > 0) {
        cheios = (atual * larguraBarra) / maxima;
    }
    if (cheios > larguraBarra) {
        cheios = larguraBarra; /* trava no maximo se pegar bonus em R */
    }
    if (cheios < 0) {
        cheios = 0;
    }

    addch('[');
    desenharLinhaChars(cheios, '#');
    desenharLinhaChars(larguraBarra - cheios, '.');
    addch(']');
}

static void desenharPainel(Jogo *j, int linhaInicio) {
    int cristaisFaltantes = j->minimoCristais - j->cristais;

    mvprintw(linhaInicio,     0, "====================================================");
    mvprintw(linhaInicio + 1, 0, " Folego  : ");
    desenharBarraFolego(j->energia, j->energiaInicial);
    printw(" %d / %d", j->energia, j->energiaInicial);

    if (cristaisFaltantes > 0) {
        mvprintw(linhaInicio + 2, 0, " Cristais: %d de %d (faltam %d)",
                 j->cristais, j->minimoCristais, cristaisFaltantes);
    } else {
        mvprintw(linhaInicio + 2, 0, " Cristais: %d de %d (saida liberada!)",
                 j->cristais, j->minimoCristais);
    }

    mvprintw(linhaInicio + 3, 0, " Turnos  : %d  |  [Setas/WASD] Mover  [Q] Desistir", j->turnos);
    mvprintw(linhaInicio + 4, 0, "====================================================");
    mvprintw(linhaInicio + 5, 0, " Status  : %s", j->mensagem);
}

int telaCabe(Jogo *j) {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    /* Precisa da altura do mapa + 7 linhas do painel e largura minima de 54 colunas */
    int larguraNecessaria = (j->colunas > 54) ? j->colunas : 54;
    return (maxY >= j->linhas + 7 && maxX >= larguraNecessaria);
}

void desenharJogo(Jogo *j) {
    clear();

    /* Desenha a matriz do mapa caractere a caractere */
    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            if (i == j->linhaJ && k == j->colunaJ) {
                mvaddch(i, k, '@');
            } else {
                mvaddch(i, k, j->mapa[i][k]);
            }
        }
    }

    /* Desenha o seu painel estilizado logo abaixo do mapa */
    desenharPainel(j, j->linhas + 1);

    refresh();
}

int carregarMapa(const char *nomeArquivo, Jogo *j) {
    (void)nomeArquivo;

    const char *exemplo[8] = {
        "################",
        "#...#....C.....#",
        "#.#.#.##.###.#.#",
        "#.#R..#..A.C.#.#",
        "#.###.#.####.#.#",
        "#C..E...#..C.#S#",
        "#.##..#...#..C.#",
        "################"
    };

    j->linhas = 8;
    j->colunas = 16;
    j->energia = 35;
    j->energiaInicial = 35;
    j->minimoCristais = 3;
    j->linhaJ = 1;
    j->colunaJ = 1;

    for (int i = 0; i < j->linhas; i++) {
        for (int k = 0; k < j->colunas; k++) {
            j->mapa[i][k] = exemplo[i][k];
        }
    }

    return 1;
}

int movimentoValido(Jogo *j, int comando) {
    int proxL = j->linhaJ;
    int proxC = j->colunaJ;

    if (comando == KEY_UP || comando == 'w' || comando == 'W') {
        proxL--;
    } else if (comando == KEY_DOWN || comando == 's' || comando == 'S') {
        proxL++;
    } else if (comando == KEY_LEFT || comando == 'a' || comando == 'A') {
        proxC--;
    } else if (comando == KEY_RIGHT || comando == 'd' || comando == 'D') {
        proxC++;
    } else {
        return 0;
    }

    if (proxL < 0 || proxL >= j->linhas || proxC < 0 || proxC >= j->colunas) {
        return 0;
    }
    if (j->mapa[proxL][proxC] == '#') {
        return 0;
    }

    return 1;
}