#include "guardajogo.h"
#include "jogadasant.h"
#include "matdin.h"

void guardajogo(jgant t,save sve, tabul tabp, minitabuleiro mint,int jogadas_feitas, int jogador_atual, int modo_jogo, int prox_minitab)
{
    FILE* f;
    int i;

    sve.id_proximo_jogador = jogador_atual;
    sve.prox_minitab=prox_minitab;
    sve.total_jogadas = jogadas_feitas;
    if(modo_jogo==1)
        sve.modoJogo=0;
    else
        sve.modoJogo=1;

    printf("\n");



    f = fopen("jogo.bin", "wb");
    if(f==NULL)
    {
        printf("\nErro no acesso ao ficheiro!\n");
        return;
    }

    fwrite(&sve, sizeof(save), 1, f);
    fclose(f);

    printf("\nJogo guardado com sucesso!\n");
}

save retomajogo(save s)
{
    int aux;
    FILE *f;
    f = fopen("jogo.bin", "rb");
    if(f==NULL)
    {
        printf("\nErro no acesso ao ficheiro!\n");
        exit(0);
    }
    else
    {
        printf("\nFicheiro encontrado pretende retomar o jogo?\n1-Sim\t2-Nao\nOpcao: ");
        scanf("%d", &aux);
    }
    if(aux==1)
    {
        fread(&s, sizeof(save), 1, f);
        fclose(f);
        s.retorna=1;
        printf("\nSucesso: Jogo carregado!\n");
        return s;
    }
    else if(aux!=1)
    {
        s.retorna=0;
        return s;
    }

}

void texto(int id_vencedor, save sve, tabul tab)
{
    FILE *f;
    int i;
    char nome_ficheiro[30];
    printf("\nNome que deseja dar ao ficheiro: ");
    scanf("%s", &nome_ficheiro);
    strcat(nome_ficheiro, ".txt");

    f=fopen(nome_ficheiro, "w");
    if(f==NULL)
    {
        printf("\nErro no acesso ao ficheiro\n");
        return;
    }
    if(sve.modoJogo==0)
    {
        fputs("Modo de Jogo: Individual", f);
        if(id_vencedor==0)
            fprintf(f, "\nVencedor e o Jogador\tJogadas feitas: %d\n", sve.total_jogadas);
        else
            fprintf(f, "\nVencedor e o Computador \tJogadas feitas: %d\n", sve.total_jogadas);
    }
    else
    {
        fputs("Modo de Jogo: Jogador contra Jogador", f);
        fprintf(f, "\nVencedor e o Jogador %d\tJogadas feitas: %d\n", id_vencedor+1, sve.total_jogadas);
    }
    fputs("Jogo Final", f);
    fputc('\n', f);
    fputs("Tabuleiro Grande", f);
    fputc('\n', f);
    escreveJogoTabs(tab.tabuleirogrande, f);
    for(i=0; i<9; i++)
    {
        fprintf(f,"\nMinitabuleiro %d\n", i+1);
        escreveJogoTabs(tab.minitabs[i].minitabuleiros, f);
        fputc('\n', f);
    }
    fputs("Jogadas", f);
    fputc('\n', f);

    escreveJogadas(sve, f);

    fclose(f);
}

tabul preencheJogoGuardado(save s,tabul tab,jgant t)
{
    int ganhou=0, aux=0, jogador_atual;
    tab.tabuleirogrande=criaMat(LINHAS,COLUNAS);
    for(int i=0; i<9; i++)
    {
        tab.minitabs[i].minitabuleiros=criaMat(LINHAS,COLUNAS);
        tab.minitabs[i].seccaovencida=0;
    }

    for(int j=0; j<s.total_jogadas; j++)
    {
        int ganhou=0, aux;
        aux=s.minitabsinfo[j].n_minitab; //id de minitab
        setPos(tab.minitabs[aux].minitabuleiros, s.minitabsinfo[j].x, s.minitabsinfo[j].y, s.minitabsinfo[j].car);
        ganhou=verifica(tab.minitabs[s.minitabsinfo[j].n_minitab].minitabuleiros,LINHAS,COLUNAS);
        if(ganhou==1)
        {
            setPos(tab.tabuleirogrande,s.minitabsinfo[j].xtabgrande,s.minitabsinfo[j].ytabgrande,s.minitabsinfo[j].car);
            tab.minitabs[s.minitabsinfo[j].n_minitab].seccaovencida=1;
            if(s.minitabsinfo[j].car=='X')

                jogador_atual==0;

            else
                jogador_atual==1;
            t=inserejogada(t, tab.minitabs[aux].minitabuleiros, j+1, s.minitabsinfo[j].n_minitab, jogador_atual, s.minitabsinfo[j].x, s.minitabsinfo[j].y);
        }
        if(s.modoJogo==0)
        {
            if(s.minitabsinfo[j].car=='X')

                jogador_atual==0;

            else
                jogador_atual==1;
        }
        else if(s.modoJogo==1)
        {
            if(s.minitabsinfo[j].car=='X')
                jogador_atual==0;
            else
                jogador_atual==1;
        }
    }

    return tab;
}

void escreveJogadas(save s, FILE *f)
{
    int ganhou=0, aux=0, max_jogadas;
    max_jogadas=s.total_jogadas;
    tabul tab;
    tab=criaTabuleirosDeJogo(tab);
    for(int j=0; j<max_jogadas; j++)
    {
        int ganhou=0, aux;
        aux=s.minitabsinfo[j].n_minitab; //id de minitab
        setPos(tab.minitabs[aux].minitabuleiros,s.minitabsinfo[j].x,s.minitabsinfo[j].y,s.minitabsinfo[j].car);

        ganhou=verifica(tab.minitabs[aux].minitabuleiros, 3, 3);
        if(ganhou==1)
        {
            setPos(tab.tabuleirogrande,s.minitabsinfo[j].xtabgrande,s.minitabsinfo[j].ytabgrande,s.minitabsinfo[j].car);
            tab.minitabs[aux].seccaovencida=1;
        }
        if(s.modoJogo==0)
        {
            if(s.minitabsinfo[j].car=='X')
            {
                fprintf(f,"\nJogador fez a Jogada %d\tMinitabuleiro %d\tx: %d\ty:%d\n",j+1, aux+1, s.minitabsinfo[j].x+1, s.minitabsinfo[j].y+1);
            }
            else
                fprintf(f,"\Computador fez a Jogada %d\tMinitabuleiro %d\tx: %d\ty:%d\n",j+1, aux+1, s.minitabsinfo[j].x+1, s.minitabsinfo[j].y+1);
        }
        else if(s.modoJogo==1)
        {
            if(s.minitabsinfo[j].car=='X')
                fprintf(f,"\nJogador 1 fez a Jogada %d\tMinitabuleiro %d\tx: %d\ty:%d\n",j+1, aux+1, s.minitabsinfo[j].x+1, s.minitabsinfo[j].y+1);
            else
                fprintf(f,"\nJogador 2 fez a Jogada %d\tMinitabuleiro %d\tx: %d\ty:%d\n",j+1, aux+1, s.minitabsinfo[j].x+1, s.minitabsinfo[j].y+1);
        }
        escreveJogoTabs(tab.minitabs[aux].minitabuleiros, f);
        if(ganhou==1)
        {
            fprintf(f,"\nGanhou o minitabuleiro %d\nTabuleiro Principal\n", aux+1);
            escreveJogoTabs(tab.tabuleirogrande, f);
        }
        fputc('\n', f);
    }
}

save guardaCoordenadas(save s, int c1, int c2, int c1grande, int c2grande, int nminit, int njogada, char c)
{
    int aux;
    aux=njogada-1;
    s.minitabsinfo[aux].n_minitab=nminit;
    s.minitabsinfo[aux].x=c1;
    s.minitabsinfo[aux].y=c2;
    s.minitabsinfo[aux].xtabgrande=c1grande;
    s.minitabsinfo[aux].ytabgrande=c2grande;
    s.minitabsinfo[aux].car=c;
    return s;
}

