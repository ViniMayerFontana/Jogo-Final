// ESTRUTURA DE INTERFACE PARA ESCOLHER TECLA DE COMANDO E PRINTAR A NOVA POSIÇÃO DO PERSONAGEM

int main()
{
    Jogador j;
    char c;
    printf("Nome: ");
    scanf("%s", &j.nome);
    printf("Linhas: ");
    scanf("%d", &j.pos.linha);
    printf("Colunas: ");
    scanf("%d", &j.pos.coluna);
    ImprimeJogador(j);
    while(c != 'q'){
        printf("\ndigite seu comando (w/a/s/d ou q)");
        scanf(" %c", &c);
        moveJogador(&j, c);
        ImprimeJogador(j);
        if(c == 'q'){
                printf("\n\nFeitoria %s!", j.nome);
        }
    }
    return 0;
}