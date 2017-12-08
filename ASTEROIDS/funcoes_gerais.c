#include "funcoes_gerais.h"
#include <stdlib.h>

//tiros--------------------------------------------------------

void criar_tiro_no_jogo(sfClock * tempo, Nave * jupter, int * tiro_qtd, Tiro * tiro, sfMusic * bala,int Max_tiros){
    if(sfKeyboard_isKeyPressed(sfKeyJ) && (sfClock_getElapsedTime(tempo).microseconds > sfMilliseconds(200).microseconds) && jupter->vivo == 's'){
        descobrir_movimentacao_tiro(jupter,tiro+*tiro_qtd);
        *tiro_qtd += 1;
        sfMusic_setVolume(bala,30);
        sfMusic_play(bala);
        sfClock_restart(tempo);
    }if(*tiro_qtd == Max_tiros)
        *tiro_qtd = 0;
}

//bordas-------------------------------------------------------

void bordas(Asteroids *asteroids, Nave *jupter, Alien *alien, int max_alien, int max_asteroids, int tamanho_tela_largura, int tamanho_tela_altura){
    int i;
    //controle de bordas para o alien
    for(i=0;i<max_alien;i++)
        controle_de_bordas(&(alien+i)->x,&(alien+i)->y,tamanho_tela_largura,tamanho_tela_altura);
    //controle de bordas para nave
    controle_de_bordas(&jupter->x,&jupter->y,tamanho_tela_largura,tamanho_tela_altura);

    //controle de bordas para asteroid
    for(i=0;i<max_asteroids;i++)
        controle_de_bordas(&(asteroids+i)->x,&(asteroids+i)->y,tamanho_tela_largura,tamanho_tela_altura);

}

//impacto-------------------------------------------------------

void impacto(Nave *jupter, Asteroids *asteroids, Tiro *tiro, Alien *alien, int max_asteroids, int max_alien,int tiro_qtd,sfMusic * explosion){
    int i,j;
    //condição de impacto com a asteroid/nave
    for(i=0;i<max_asteroids;i++){
        coli_nave_asteroid(jupter,(asteroids+i),explosion);
    }
    //colisão asteroids
    for(i = 0; i<max_asteroids; i++){
        for(j = i+1; j<max_asteroids; j++){
            if ((asteroids+i)->vivo == 's' && (asteroids+j)->vivo == 's'){
                coli_asteroid_asteroid((asteroids+i),(asteroids+j));
            }
        }
    }
    //impacto tiro/asteroid
    for(i=0;i<tiro_qtd;i++){
        for(j=0;j<max_asteroids;j++){
            coli_tiro_asteroid((tiro+i),(asteroids+j),jupter,explosion);
        }
    }
    //impacto alien/nave
    for(i=0;i<max_alien;i++)
        coli_alien_nave((alien+i),jupter);

    //impacto alien/alien
    for(i=0;i<max_alien;i++)
        for(j=i+1;j<max_alien;j++)
            coli_alien_alien((alien+i),(alien+j));

    // impacto tiro/alien
    for(i=0;i<tiro_qtd;i++){
        for(j=0;j<max_alien;j++)
            coli_tiro_alien((tiro+i),(alien+j),jupter);
    }        
}


//desenho-e-impacto-especial----------------------------------------
void desenho_especial(Nave * jupter,Especial * especial,sfSprite ** sespecial,sfMusic * audio,int max_asteroids,sfRenderWindow ** janela,Asteroids * asteroids,int max_alien,Alien * alien){
    if (sfKeyboard_isKeyPressed(sfKeyK) && jupter->mp > 0 && jupter->vivo == 's'){
        jupter->mp -= 10;
        desenhar_na_tela(janela,sespecial,especial->x,especial->y);
        sfSprite_setRotation(*sespecial,especial->especial_rotacao);
        sfMusic_play(audio);
        especial->especial_rotacao += 10;
        //impacto do especial
        int i;
        for(i=0;i<max_asteroids;i++){
          coli_especial_asteroid(especial,(asteroids+i),jupter);
        }
        for(i=0;i<max_alien;i++){
          coli_especial_alien(especial,(alien+i),jupter);
        }
    }
}

//desenhar-tiro---------------------------------------------------------
void desenho_tiro(int tiro_qtd, Tiro *tiro, sfRenderWindow **janela,Nave * jupter,sfSprite ** stiro){
    int i;
    for(i=0;i <= tiro_qtd;i++){
        if (((tiro+i)->exite == 's') && (jupter->vivo == 's')){
            movimentar_bala((tiro+i));
            desenhar_na_tela(janela,stiro,(tiro+i)->x,(tiro+i)->y);
        }
    }
}

//desenhar-nave--------------------------------------------------------
void desenhar_nave(Nave *jupter, sfRenderWindow **janela, sfSprite **sjupter){
    if (jupter->vivo == 's')
        desenhar_na_tela(janela,sjupter,jupter->x,jupter->y);
}

//desenhar-asteroids----------------------------------------------------
void desenhar_asteroids(Asteroids * asteroids,sfRenderWindow ** janela,sfSprite ** sasteroid,int max_asteroids){
    int i;
    for(i=0;i<max_asteroids;i++){
        if ((asteroids+i)->vivo == 's' && (asteroids+i)->tamanho == 'g'){
            desenhar_na_tela(janela,sasteroid,(asteroids+i)->x,(asteroids+i)->y);
        }
    }
}

//desenhar-game-over-----------------------------------------------------
void game_over(sfRenderWindow ** janela,sfSprite ** sgame_over,Nave * jupter){
    if (jupter->vivo == 'n'){
        desenhar_na_tela(janela,sgame_over,-50,0);
    }
}

//tela-inicio--------------------------------------------------------------

void tela(char * inicio,sfRenderWindow ** janela,sfSprite ** tela_de_inicio,Nave * jupter,int tamanho_tela_altura,
          int tamanho_tela_largura,int *tiro_qtd,int * alien_qtd, int * asteroids_qtd,Asteroids * asteroids,int max_asteroids){
    if (*inicio == 'n'){
        desenhar_na_tela(janela,tela_de_inicio,0,0);
    }if(sfKeyboard_isKeyPressed(sfKeySpace)){
        *inicio = 's';
        *tiro_qtd = 0;
        *alien_qtd = 2;
        *asteroids_qtd = 10;
        criar_nave(jupter,tamanho_tela_altura,tamanho_tela_largura);
        int i;
        for(i = 0; i < max_asteroids;i++)
            criar_asteroids((asteroids+i),rand()%tamanho_tela_altura,rand()%tamanho_tela_largura,rand()%11,'g');

    }
}
