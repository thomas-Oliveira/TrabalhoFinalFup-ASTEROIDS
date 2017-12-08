#ifndef GAME_H
#define GAME_H
#include "estruturas.h"
#include <SFML/Graphics.h>



void criar_asteroids(Asteroids * asteroid, int altura,int largura,int rotacao);

void criar_nave(Nave * nave, int altura, int largura );

void criar_tiro(Tiro * tiro,float x, float y);

void movimentar_nave(Nave * nave,char dire,sfSprite *sprite);

void controle_de_bordas(float * x, float * y);

void movimentar_asteroid(Asteroids * asteroid,sfSprite *sprite);

void coli_nave_asteroid(Nave * nave,Asteroids * asteroid);

void descobrir_movimentacao_tiro(Nave * nave,Tiro * bala);

void movimentar_bala(Tiro * bala);

void coli_tiro_asteroid(Tiro * tiro,Asteroids * asteroid);

void Criar_sprite_textura(char file[100],sfTexture ** tex, sfSprite ** spr,float escla_x, float escala_y);

void coli_especial_asteroid(Especial * esp,Asteroids * asteroid);

void destroy_sprite_textura(sfTexture ** tex, sfSprite **spr);

void atualizar_especial(Especial * esp,Nave * nave);

void condicao_tiro(int * qtd,int max_tiros,int * time,int max_time);

void desenhar_nave(sfRenderWindow ** janela,sfSprite ** snave,Nave * nave);


#endif // GAME_H
