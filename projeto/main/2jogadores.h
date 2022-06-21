#ifndef JOGADORES_H
#define JOGADORES_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "matdin.h"
#include "guardajogo.h"

//Jogo do par ou impar para ver quem comeca o jogo
int parimpar(int jogador_atual);

//recebe o id do jogador atual e devolve o id do jogador seguinte
int proximojogador(int jogadoratual);

//Jogo de 2 jogadores
void dois_jogadores(int jogador_atual, save guarda_info, tabul tab_principal);

//Escolhe o primeiro Tabuleiro
int primeiroTabul(int tabulescolhido);

//invoca todas as funçoes acima
void comecarJogoDois(int opcao_menu);

#endif
