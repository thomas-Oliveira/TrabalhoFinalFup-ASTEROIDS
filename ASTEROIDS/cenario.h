#ifndef CENARIO_H
#define CENARIO_H
#include "estruturas.h"
#include "funcoes_gerais.h"
#include <SFML/Audio.h>

void criar_asteroids(Asteroids * asteroid, int altura,int largura,int rotacao,char tamanho);

void criar_nave(Nave * nave, int altura, int largura );

void criar_tiro(Tiro * tiro,float x, float y);

void controle_de_bordas(float * x, float * y,int largura,int altura);

void movimentar_asteroid(Asteroids * asteroid,sfSprite *sprite,int max);

void coli_nave_asteroid(Nave * nave,Asteroids * asteroid,sfMusic * explosion);

void descobrir_movimentacao_tiro(Nave * nave,Tiro * bala);

void movimentar_bala(Tiro * bala);

void coli_tiro_asteroid(Tiro * tiro,Asteroids * asteroid,Nave * nave,sfMusic * explosion);

void Criar_sprite_textura(char file[100],sfTexture ** tex, sfSprite ** spr,float escla_x, float escala_y);

void coli_especial_asteroid(Especial * esp,Asteroids * asteroid,Nave * nave);

void atualizar_especial(Especial * esp,Nave * nave);

void condicao_tiro(int * qtd,int max_tiros,int * time,int max_time);

void desenhar_na_tela(sfRenderWindow ** janela,sfSprite ** sprite,int x, int y);

void acelerar_nave(Nave * nave);

void movimentar_nave_2(Nave * nave,sfSprite * sprite);

void update_nave(Nave * nave);

void vitoria(sfRenderWindow ** janela,sfSprite ** sprite,int max_asteroids, Asteroids * asteroid[100]);

void coli_asteroid_asteroid(Asteroids * asteroid1,Asteroids * asteroid);

void mover_alien(Alien * alien,Nave * nave,int max);

void criar_alien(Alien * alien,int x,int y);

void coli_alien_nave(Alien * alien,Nave * nave);

void coli_alien_alien(Alien * alien,Alien * alien2);

void coli_alien_asteroid(Alien * alien,Asteroids * asteroid);

void coli_tiro_alien(Tiro * tiro,Alien * alien,Nave * nave);

void criar_texto(int escore,sfText ** Texto,sfFont ** fonte, sfRenderWindow ** janela);

void coli_especial_alien(Especial * esp,Alien * alien,Nave * nave);

#endif // CENARIO_H
