#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "2jogadores.h"
#include "matdin.h"
#include "1vcpu.h"
#include "utils.h"
#include "jogadasant.h"
#include "guardajogo.h"

retomarJogo()
{
    jgant lista=NULL;
    tabul tabuleiroprincipal;
    minitabuleiro minitabuls;
    save save_game;
    save_game=retomajogo(save_game);

    //valor que é dado apos ser verificado q o ficheiro existe e o jogador queira continuar

    if(save_game.retorna==1)
    {
        tabuleiroprincipal=preencheJogoGuardado(save_game, tabuleiroprincipal, lista);
        for(int i=0; i<9; i++)
        {
            printf("\nTabuleiro %d\n", i+1);
            mostraMat(tabuleiroprincipal.minitabs[i].minitabuleiros,LINHAS,COLUNAS);
        }
        if(save_game.modoJogo==0)//contra pc
        {

            jogoContraPc(save_game.id_proximo_jogador, save_game, tabuleiroprincipal, proximominitab);
        }
        else if(save_game.modoJogo==1)//1v1
        {
            dois_jogadores(save_game.id_proximo_jogador, save_game, tabuleiroprincipal);
        }
    }
}
