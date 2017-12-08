#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <SFML/Graphics.h>

typedef struct {
    char vivo;
    int hp,mp;
    float x,y;
    float vx,vy;
    float angulo,v_angular;
    int pontuacao;
}Nave;

typedef struct {
    char vivo;
    int angulo;
    int rotacao;
    float x,y;
    float vx,vy;
    char tamanho;
}Asteroids;

typedef struct{
    int angulo;
    char exite;
    float x,y;
    float vx,vy;
}Tiro;

typedef struct{
    int especial_rotacao;
    float x,y;
}Especial;

typedef struct{
    float x,y;
    char alien_perto;
    char vivo;
}Alien;

#endif // ESTRUTURAS_H
