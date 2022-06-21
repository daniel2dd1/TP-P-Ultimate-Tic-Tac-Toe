#ifndef VCPU_H
#define VCPU_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "matdin.h"
#include "guardajogo.h"

//Par ou Impar com o computador para ver quem comeca
int comecasolo(int resultado);

//Escolhe o primeiro tabuleiro
int primeiroTabulVcpu(int tabulescolhido, int vencedor);

//Jogo contra o Computador
void jogoContraPc(int jogador_atual, save guarda_info, tabul tab_principal, int proximo_minitab);

//chama funcao acima
void comecarJogoSolo(int opcao_menu);

#endif
