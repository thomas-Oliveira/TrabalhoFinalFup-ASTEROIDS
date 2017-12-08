#ifndef FUNCOES_GERAIS
#define FUNCOES_GERAIS
#include "cenario.h"
#include "estruturas.h"
#include <SFML/Audio.h>
#include <SFML/Graphics.h>

void criar_tiro_no_jogo(sfClock * tempo, Nave * jupter,int * tiro_qtd,Tiro * tiro,sfMusic * bala,int Max_tiros);

void bordas(Asteroids * asteroids,Nave * jupter,Alien * alien,int max_alien,int max_asteroids,int tamanho_tela_largura,int tamanho_tela_altura);

void impacto(Nave * jupter ,Asteroids * asteroids , Tiro * tiro , Alien * alien,int max_asteroids,int max_alien,int tiro_qtd,sfMusic * explosion);

void desenho_especial(Nave * jupter,Especial * especial,sfSprite ** sespecial,sfMusic * audio,int max_asteroids,sfRenderWindow ** janela,Asteroids * asteroids,int max_alien,Alien * alien);

void desenho_tiro(int tiro_qtd,Tiro * tiro,sfRenderWindow ** janela,Nave * jupter,sfSprite ** stiro);

void desenhar_nave(Nave * jupter,sfRenderWindow ** janela, sfSprite ** sjupter);

void desenhar_asteroids(Asteroids * asteroids,sfRenderWindow ** janela,sfSprite ** sasteroid,int max_asteroids);

void game_over(sfRenderWindow ** janela,sfSprite ** sgame_over,Nave * jupter);


void tela(char * inicio,sfRenderWindow ** janela,sfSprite ** tela_de_incio,Nave * jupter,int tamanho_tela_altura,
          int tamanho_tela_largura,int *tiro_qtd,int * alien_qtd, int * asteroids_qtd,Asteroids * asteroids,int max_asteroids);

#endif // FUNCOES_GERAIS

