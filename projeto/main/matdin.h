// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022

#ifndef MATDIN_H
#define MATDIN_H

#include <stdlib.h>
#include <stdio.h>

//estruturas do tabuleiro de jogo
typedef struct tabuleirogrande tabul;

typedef struct minit minitabuleiro;

struct minit
{
    char *minitabuleiros;       //minitabuleiros
    int seccaovencida;          //� 1 caso o minitabuleiro tenho sido vencido ou em caso de empate
};

struct tabuleirogrande
{
    char *tabuleirogrande;      //tabuleiro principal
    minitabuleiro minitabs[9];  //array com os 9 tabuleiros
};

//start
void startGame();

// Liberta uma matriz din�mica de caracteres com nLin linhas
void libertaMat(char** p, int nLin);

// Cria uma matriz din�mica de caracteres  com nLin linhas e nCol colunas
// Devolve endere�o inicial da matriz
char** criaMat(int nLin, int nCol);

// Imprime o conte�do de uma matriz din�mica de caracteres
void mostraMat(char **p, int nLin, int nCol);

// Coloca o caracter c na posi��o (x, y) de uma matriz din�mica de caracteres
void setPos(char **p, int x, int y, char c);

// Obt�m o caracter armazenado na posi��o (x, y) de uma matriz de caracteres
char getPos(char **p, int x, int y);

//verifica��es de linhas
int verifica(char **p, int x, int y);

//proxima jogada recebe as coordenadas dos valores atuais e devolve o valor do tabuleiro correspondente pertencente no array
int proximominitab(int x, int y);

//valida��o de espa�o se o utilizador pode ou n�o inserir aquelas coordenadas
int validaespaco(char **p, int x, int y);

//menu inicial
int menu(int *opcao);

//devolve o caratual
char caracteratual(int *jatual);

//Antes da primeira jogada o jogador que venceu o par ou impar tem direito a escolher um minitabuleiro que deseja comecar
int escolheTabul(int tabulescolhido);

//funcao do tipo tabul que cria todos os tabuleiros de jogo necessarios e devolve os para essa estrutura
tabul criaTabuleirosDeJogo(tabul t);

//funcoes auxiliares para saber as coordenadas do tabuleiro grande
int x_tabgrande(int minitabul_atual);
int y_tabgrande(int minitabul_atual);

//escreve os minitabuleiros e tabuleiros em formato de ficheiro de texto
void escreveJogoTabs(char **p, FILE *f);

#endif
