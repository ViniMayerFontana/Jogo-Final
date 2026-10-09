#include <stdio.h>
void linha(int n, char c);
void quadro(int altura, int largura);

int main(void){
    int altura;
    int largura;
    printf("digite altura:");
    scanf("%d", &altura);
    printf("digite largura:");
    scanf("%d", &largura);
    if(((40 > largura) && (largura > 3)) && ((20 > altura) && (altura > 3))){
        quadro(altura, largura);
    }
    else{
        printf("parametros invalidos");
        return 0;
    }
    return 0;
}

void linha(int n, char c) {
int i; /* variavel local: so existe aqui */
for (i = 0; i < n; i++)
printf("%c", c);
}

void quadro(int altura, int largura){
    linha(largura, '#'); // linha 1 ############

    for(int i; i<(altura - 2); i++){
        printf("\n");
        linha(1, '#'); // primeiro termo das linhas do meio
        linha((largura-2), '.'); // pontos do meio da linha do meio
        linha(1, '#'); // ultimo termo das linhas do meio
        printf("\n");
    }
    linha(largura, '#'); // ultima linha ############
}
