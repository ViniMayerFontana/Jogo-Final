#include <stdio.h>

void linha(int n, char c);
void barra(int Energia_atual, int Energia_maxima);
void painel(int Energia_atual, int Energia_maxima, int cristais_coletados, int cristais_minimos, int turnos);

int main(void){
    int Energia_maxima;
    int Energia_atual;
    int cristais_coletados;
    int cristais_minimos;
    int turnos;

    printf("digite a Energia maxima: ");
    scanf("%d", &Energia_maxima);
    printf("digite a Energia atual: ");
    scanf("%d", &Energia_atual);
    printf("digite os cristais coletados: ");
    scanf("%d", &cristais_coletados);
    printf("digite os cristais minimos: ");
    scanf("%d", &cristais_minimos);
    printf("digite os turnos: ");
    scanf("%d", &turnos);
    if (
        ((Energia_maxima < 1) || (Energia_maxima > 30)) || ((Energia_atual < 0) || (Energia_atual > Energia_maxima)) || (cristais_coletados < 0) || (cristais_minimos < 1) || (turnos < 0)) {
            printf("Valores invalidos!");
            return 0;
        }
    else{
        painel(Energia_atual, Energia_maxima, cristais_coletados, cristais_minimos, turnos);
    }
    return 0;
}

void linha(int n, char c) {
int i; /* variavel local: so existe aqui */
for (i = 0; i < n; i++)
printf("%c", c);
}

void barra(int Energia_atual, int Energia_maxima){
    linha(1, '['); // abertura colchetes
    linha(Energia_atual, '#'); // pontos de energia atual 
    linha((Energia_maxima - Energia_atual), '.'); // pontos vazios de energia (que faltaram pra ficar full)
    linha(1, ']'); // fechamento dos colchetes
}

void painel(int Energia_atual, int Energia_maxima, int cristais_coletados, int cristais_minimos, int turnos){
    int cristais_faltantes = (cristais_minimos - cristais_coletados);
    printf(" ==================================\n");
    printf("  Energia : ");
    barra(Energia_atual, Energia_maxima);
    printf("   %d / %d \n", Energia_atual, Energia_maxima);
    printf("  Cristais: %d de %d (faltam %d)\n", cristais_coletados, cristais_minimos, cristais_faltantes);
    printf("  Turnos  : %d\n", turnos);
    printf(" ==================================\n");
}
