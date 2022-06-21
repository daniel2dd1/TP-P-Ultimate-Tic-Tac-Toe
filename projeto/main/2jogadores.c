#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "2jogadores.h"
#include "matdin.h"
#include "1vcpu.h"
#include "utils.h"
#include "jogadasant.h"
#include "guardajogo.h"

#define JOGADASMAX 81

void comecarJogoDois(int opcao_menu)
{
    save s;
    s.retorna=0;
    s.modoJogo=opcao_menu;
    tabul tab;
    int jogador_atual=parimpar(jogador_atual);
    dois_jogadores(jogador_atual, s, tab);
}

int parimpar(int jogador_atual)
{
    int auxiliar, valor1, valor2, jogador1, jogador2;
    printf("\n0 - Par ou 1 - Impar\nJogador 1: ");
    scanf("%d", &jogador1);
    while(jogador1!=0 && jogador1!=1)
    {
        printf("\nValor invalido insira novamente: ");
        scanf("%d", &jogador1);
    }
    if(jogador1==0)
        jogador2=1;
    else
        jogador2=0;
    printf("\nJogador 1 insira um numero aleatorio: ");
    scanf("%d", &valor1);
    while(valor1<0)
    {
        printf("\nIntroduza de novo: ");
        scanf("%d", &valor1);
    }
    printf("\nJogador 2 insira um numero aleatorio: ");
    scanf("%d", &valor2);
    while(valor2<0)
    {
        printf("\nIntroduza de novo: ");
        scanf("%d", &valor2);
    }
    auxiliar=valor1+valor2;
    while(auxiliar!=1 && auxiliar!=0)
        auxiliar=auxiliar%2;

    //devolve o numero 0 se j1 e 1 se j2
    if(auxiliar==1 && jogador1==1)
        return 0;
    else if(auxiliar==1 && jogador2==1)
        return 1;
    else if(auxiliar==0 && jogador1==0)
        return 0;
    else if(auxiliar==0 && jogador2==0)
        return 1;
}

////////////////Proximo Jogador
int proximojogador(int jogadoratual)       //jogador atual se for 0 é o j1 se for 1 é o j2
{
    if(jogadoratual==1)
        return 0;
    else
        return 1;
}

int primeiroTabul(int tabulescolhido)
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

void dois_jogadores(int jogador_atual, save guarda_info, tabul tab_principal)
{
    int c1, c2, resposta, minitabul_atual, finaldejogo=0, num_jogadas=0, valida_espaco, seccao_vencida=0, rever_jogadas;
    //coordenadas que serviram de auxilia para marcar cajo haja algum minitabuleiro completo
    int xtabgrande, ytabgrande;

    //Jogador X Computador - O
    char j_atual;

    //////
    tabul tab;
    tab=tab_principal;
    if(guarda_info.retorna!=1)
    {
        tab=criaTabuleirosDeJogo(tab);

        printf("\nTabuleiro Principal\n");
        mostraMat(tab.minitabs[minitabul_atual].minitabuleiros,LINHAS,COLUNAS);
        printf("\nJogador %d comeca\n", jogador_atual+1);

        printf("\nTabuleiro Principal\n");
        mostraMat(tab.minitabs[minitabul_atual].minitabuleiros,LINHAS,COLUNAS);
        //primeiro tabuleiro
        minitabul_atual=primeiroTabul(minitabul_atual);
    }
    else
    {
        jogador_atual=guarda_info.id_proximo_jogador;
        minitabul_atual=guarda_info.prox_minitab;
        num_jogadas=guarda_info.total_jogadas;
    }

    jgant lista=NULL;
    minitabuleiro minitabuls;

    do
    {
        xtabgrande=x_tabgrande(minitabul_atual);
        ytabgrande=y_tabgrande(minitabul_atual);

        if(num_jogadas>0)
        {
            printf("\nDeseja rever jogadas anteriores?\t1-Sim\t2-Nao\nResposta: ");
            scanf("%d", &rever_jogadas);
            if(rever_jogadas==1)
                deseja_rever_jogadas(lista, num_jogadas);
            if(guarda_info.retorna==0)
                jogador_atual=proximojogador(jogador_atual);
        }
        guarda_info.retorna=0;
        int guarda;
        printf("\nPretende Guardar Jogo?\t1-Sim\t2-Nao\n");
        scanf("%d", &guarda);
        if(guarda==1)
        {
            guardajogo(lista, guarda_info, tab, minitabuls, num_jogadas, jogador_atual, 2, minitabul_atual);
        }
        for(int i=0; i<9; i++)
        {
            printf("\nTabuleiro %d\n", i+1);
            mostraMat(tab.minitabs[i].minitabuleiros,LINHAS,COLUNAS);
        }
        printf("\nTabueleiro Principal\n");
        mostraMat(tab.tabuleirogrande,LINHAS,COLUNAS);
        printf("\nTabueleiro Atual %d\n", minitabul_atual+1);
        mostraMat(tab.minitabs[minitabul_atual].minitabuleiros,LINHAS,COLUNAS);
        do
        {
            printf("\nJogador %d digite coordenadas(1/3): ", jogador_atual+1);
            scanf("%d %d", &c1, &c2);

            c1=c1-1;
            c2=c2-1;
            valida_espaco=validaespaco(tab.minitabs[minitabul_atual].minitabuleiros, c1, c2);
            if(valida_espaco==0)
                printf("\nCoordenadas invalidas!\n");
        }
        while(valida_espaco!=1);  //se valida espaço for 1 e porque as coordenadas que o utilizador digitou sao validas
        num_jogadas++;
        j_atual=caracteratual(jogador_atual);
        setPos(tab.minitabs[minitabul_atual].minitabuleiros,c1,c2,j_atual);

        seccao_vencida=verifica(tab.minitabs[minitabul_atual].minitabuleiros,LINHAS,COLUNAS);
        if(seccao_vencida==1)
        {
            printf("\n\nMinitabuleiro %d Ganho!!\n", minitabul_atual+1);
            setPos(tab.tabuleirogrande,xtabgrande,ytabgrande,j_atual);
            tab.minitabs[minitabul_atual].seccaovencida=1;
        }

        //em caso do mini tabuleiro estar cheio ou seja empate no minitabuleiro
        int aux_ver=0;
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                valida_espaco=validaespaco(tab.minitabs[minitabul_atual].minitabuleiros, j, k);
                if(valida_espaco==0)
                {
                    aux_ver++;
                }
            }
        }
        if(aux_ver==9)
            tab.minitabs[minitabul_atual].seccaovencida=1;

        finaldejogo=verifica(tab.tabuleirogrande,LINHAS,COLUNAS);

        guarda_info=guardaCoordenadas(guarda_info, c1, c2, xtabgrande, ytabgrande,  minitabul_atual, num_jogadas, j_atual);

        //lista ligada com informacoes de cada jogada
        lista=inserejogada(lista, tab.minitabs[minitabul_atual].minitabuleiros, num_jogadas, minitabul_atual, jogador_atual, c1, c2);

        minitabul_atual=proximominitab(c1, c2);

        do
        {
            if(tab.minitabs[minitabul_atual].seccaovencida==1)
                minitabul_atual=minitabul_atual+1;
            if(minitabul_atual>8)
                minitabul_atual=0;
        }
        while(tab.minitabs[minitabul_atual].seccaovencida==1);
        guarda_info.total_jogadas = num_jogadas;
    }
    while(finaldejogo!=1 && num_jogadas!=JOGADASMAX);  //jogo acaba caso seja feita a sequencia de seccoes no tabuleiro principal ou cajo de empate
    if(finaldejogo == 1)
        printf("\nJogador %d venceu!!\n", jogador_atual+1);
    else
        printf("\nJogo termina em empate!!\n");

    remove_tudo(lista);

    texto(jogador_atual, guarda_info, tab);
}




