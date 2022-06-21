#include "matdin.h"
#include "jogadasant.h"

void startGame(){
    int opcaoini;
    opcaoini=menu(opcaoini);
    do
    {
        if(opcaoini==1)
        {
            comecarJogoSolo(opcaoini);
        }
        if(opcaoini==2)
        {
            comecarJogoDois(opcaoini);
        }
        if(opcaoini==3)
        {
            retomarJogo();
        }
        opcaoini=menu(opcaoini);
    }
    while(opcaoini!=4);
    if(opcaoini==4)
    {
        exit(0);
    }
}

void libertaMat(char** p, int nLin)
{

    int i;

    for(i=0; i<nLin; i++)
        free(p[i]);
    free(p);
}

int menu(int *opcao)
{
    printf("\nTic-Tac-Toe \nMenu \n\t1 - Individual \n\t2 - 2 Jogadores \n\t3 - Carregar Jogo\n\t4 - Sair\nOpcao: ");
    scanf("%d", &opcao);
    while(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4)
    {
        printf("\nOpcao Invalida tente de novo \nOpcao: ");
        scanf("%d", &opcao);
    }
    return opcao;
}

char** criaMat(int nLin, int nCol)
{
    char **p = NULL;
    int i, j;

    p = malloc(sizeof(char*) * nLin);
    if(p == NULL)
        return NULL;

    for(i=0; i<nLin; i++)
    {
        p[i] = malloc(sizeof(char) * nCol);
        if(p[i] == NULL)
        {
            libertaMat(p, i-1);
            return NULL;
        }
        for(j=0; j<nCol; j++)
            p[i][j] = '_';
    }
    return p;
}

void setPos(char **p, int x, int y, char c)
{
    p[x][y] = c;
}

char getPos(char **p, int x, int y)
{
    return p[x][y];
}

void mostraMat(char **p, int nLin, int nCol)
{
    int i,j;

    for(i=0; i<nLin; i++)
    {
        for(j=0; j<nCol; j++)
            printf("%c\t", p[i][j]);
        putchar('\n');
    }
}

void escreveJogoTabs(char **p, FILE *f)
{
    int i, j;
    for(i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            fprintf(f,"%c\t", p[i][j]);
        fputc('\n',f);
    }
}

//apenas para matrizes de 3 x 3
int verifica(char **p, int x, int y)
{
    if(p[0][0] == p[0][1] && p[0][0] == p[0][2] && p[0][0] != '_')        //1 linha
        return 1;
    else if(p[1][0] == p[1][1] && p[1][0] == p[1][2] && p[1][0] != '_')   //2 linha
        return 1;
    else if(p[2][0] == p[2][1] && p[2][0] == p[2][2] && p[2][0] != '_')   //3 linha
        return 1;
    else if(p[0][0] == p[1][0] && p[0][0] == p[2][0] && p[0][0] != '_')   //1 coluna
        return 1;
    else if(p[0][1] == p[1][1] && p[0][1] == p[2][1] && p[0][1] != '_')   //2 coluna
        return 1;
    else if(p[0][2] == p[1][2] && p[0][2] == p[2][2] && p[0][2] != '_')   //3 coluna
        return 1;
    else if(p[0][0] == p[1][1] && p[0][0] == p[2][2] && p[0][0] != '_')   //diagonal da esquerda para a direita
        return 1;
    else if(p[0][2] == p[1][1] && p[0][2] == p[2][0] && p[0][2] != '_')   //diagonal da direita para a esquerda
        return 1;
    else
        return 0;                                       // caso nao haja sequencia retorna 0
}

//verifica se o espaço onde as coordenadas que o jogador meteu está ocupado devolve 1 se tiver livre e 0 se tiver vazio
int validaespaco(char **p, int x, int y)
{
    if(x>=0 && x<=2 && y>=0 && y<=2 && p[x][y]!='X' && p[x][y]!='0')           //&& p[x][y]!='X' && p[x][y]!='0'
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int x_tabgrande(int minitabul_atual)
{
    if(minitabul_atual==0 || minitabul_atual==1 || minitabul_atual==2)
        return 0;
    if(minitabul_atual==3 || minitabul_atual==4 || minitabul_atual==5)
        return 1;
    if(minitabul_atual==6 || minitabul_atual==7 || minitabul_atual==8)
        return 2;
}

int y_tabgrande(int minitabul_atual)
{
    if(minitabul_atual==0 || minitabul_atual==3 || minitabul_atual==6)
        return 0;
    if(minitabul_atual==1 || minitabul_atual==4 || minitabul_atual==7)
        return 1;
    if(minitabul_atual==2 || minitabul_atual==5 || minitabul_atual==8)
        return 2;
}

int proximominitab(int x, int y)
{
    if(x == 0 && y == 0)
        return 0;
    if(x == 0 && y == 1)
        return 1;
    if(x == 0 && y == 2)
        return 2;
    if(x == 1 && y == 0)
        return 3;
    if(x == 1 && y == 1)
        return 4;
    if(x == 1 && y == 2)
        return 5;
    if(x == 2 && y == 0)
        return 6;
    if(x == 2 && y == 1)
        return 7;
    if(x == 2 && y == 2)
        return 8;
}

char caracteratual(int *jatual)
{
    char x='X', O='0';
    if(jatual==0)
        return x;
    else
        return O;
}

int escolheTabul(int tabulescolhido)
{
    printf("\nQual o tabuleiro que deseja(1/9): ");
    scanf("%d", &tabulescolhido);
    while(tabulescolhido<1 && tabulescolhido>9)
    {
        scanf("%d", &tabulescolhido);
    }
    tabulescolhido=tabulescolhido-1;
    return tabulescolhido;
}

tabul criaTabuleirosDeJogo(tabul t)
{
    t.tabuleirogrande=criaMat(LINHAS,COLUNAS);
    for(int i=0; i<9; i++)
    {
        t.minitabs[i].seccaovencida=0;
        t.minitabs[i].minitabuleiros = criaMat(LINHAS, COLUNAS);
    }
    return t;
}
