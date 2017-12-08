#include "cenario.h"
#include <string.h>
#include <stdio.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Font.h>

//---------------------------------------------------------------------------------------------------------funções-criar----
void Criar_sprite_textura(char file[100],sfTexture ** tex, sfSprite ** spr,float escala_x, float escala_y){
    //textura
    *tex = sfTexture_createFromFile(file,NULL);

    //sprite
    *spr = sfSprite_create();
    sfSprite_setTexture(*spr,*tex,0);
    sfVector2f par = {escala_x,escala_y};
    sfSprite_setScale(*spr,par);
}



void criar_alien(Alien * alien,int x,int y){
    alien->x = x;
    alien->y = y;
    alien->alien_perto = 'n';
    alien->vivo = 's';
}

void criar_asteroids(Asteroids * asteroid, int altura,int largura, int rotacao,char tamanho){
    asteroid->x = largura;
    asteroid->y = altura;
    asteroid->vx = 2;
    asteroid->vy = 2;
    asteroid->angulo = 0;
    asteroid->rotacao = rotacao;
    asteroid->vivo = 's';
    asteroid->tamanho = tamanho;
}

void criar_nave(Nave * nave, int altura, int largura ){
    nave->x = largura / 2;
    nave->y = altura / 2;
    nave->angulo = 0;
    nave->v_angular = 10;
    nave->vivo = 's';
    nave->vx = 0;
    nave->vy = 0;
    nave->hp = 390;
    nave->mp = 390;
    nave->pontuacao = 0;
}

void criar_tiro(Tiro * tiro,float x, float y){

    tiro->x = x;
    tiro->y = y;
    tiro->exite = 'n';
    tiro->vx = 0;
    tiro->vy = 0;

}

//--------------------------------------------------------------------------------------------------funçoes-de-controle----
void controle_de_bordas(float * x, float * y,int largura,int altura){
    if (*y > altura ){
        *y = 20;
    }if (*y < 20 ){
        *y = altura;
    }if (*x > largura ){
        *x = 0;
    }if (*x < 0 ){
        *x = largura;
    }

}
//----------------------------------------------------------------------------------------------funções-de-movimentação----
void movimentar_asteroid(Asteroids * asteroids, sfSprite *sprite,int max){
    int i;
    for(i=0; i< max; i++){
        if((asteroids+i)->rotacao > 11){
            (asteroids+i)->rotacao = 0;
        }
        if ((asteroids+i)->rotacao <= 2){
            (asteroids+i)->x += (asteroids+i)->vx;
            (asteroids+i)->y -= (asteroids+i)->vy;
        }else if ((asteroids+i)->rotacao <= 5){
            (asteroids+i)->x -= (asteroids+i)->vx;
            (asteroids+i)->y -= (asteroids+i)->vy;
        }else if ((asteroids+i)->rotacao <= 8){
            (asteroids+i)->x -= (asteroids+i)->vx;
            (asteroids+i)->y += (asteroids+i)->vy;
        }else if ((asteroids+i)->rotacao <= 11)
            (asteroids+i)->x += (asteroids+i)->vx;
            (asteroids+i)->y += (asteroids+i)->vy;

        sfSprite_setRotation(sprite, (asteroids+i)->angulo);
        if ((asteroids+i)->rotacao < 5)
            (asteroids+i)->angulo += 1;
        else
            (asteroids+i)->angulo -= 1;
        if ((asteroids+i)->angulo > 360)
                (asteroids+i)->angulo = 0;
    }
}
#include <math.h>
void descobrir_movimentacao_tiro(Nave * nave, Tiro * bala){
    int velocidade = 10;


    bala->x = nave->x;
    bala->y = nave->y;
    bala->vx = velocidade * cos(nave->angulo * M_PI/180.0);
    bala->vy = velocidade * sin(nave->angulo * M_PI/180.0);
    bala->exite = 's';
    bala->angulo = nave->angulo;
}

void movimentar_bala(Tiro * bala){
    bala->x += bala->vx;
    bala->y += bala->vy;
}


void acelerar_nave(Nave * nave){
    float acc = 0.3;
    float max_acc = 2;
    if(pow((nave->vx * nave->vx)+(nave->vy * nave->vy),1/2) < max_acc){
        nave->vx += cos(nave->angulo * M_PI / 180.0) * acc;
        nave->vy += sin(nave->angulo * M_PI / 180.0) * acc;
    }else{
        nave->vx -= cos(nave->angulo * M_PI / 180.0);
        nave->vy -= sin(nave->angulo * M_PI / 180.0);
    }
}


void movimentar_nave_2(Nave * nave,sfSprite * sprite){
    if (sfKeyboard_isKeyPressed(sfKeyA))
        nave->angulo -= nave->v_angular;
    else if(sfKeyboard_isKeyPressed(sfKeyD))        
        nave->angulo += nave->v_angular;
    sfSprite_setRotation(sprite, nave->angulo + 90);

    if (sfKeyboard_isKeyPressed(sfKeyW)){
        acelerar_nave(nave);
    }
    update_nave(nave);

    //tratamento de angulo.
    if (nave->angulo > 360)
        nave->angulo = 0;
    else if(nave->angulo < 0)
        nave->angulo = 360;
}



void update_nave(Nave * nave){
    nave->x += nave->vx;
    nave->y += nave->vy;
}

void mover_alien(Alien * alien, Nave * nave,int max){
    int velocidade = 2;
    int i;
    for (i=0;i<max;i++){
        if ((alien+i)->vivo == 's'){
            if ((alien+i)->alien_perto == 'n'){
                if ((alien+i)->x < nave->x){
                    (alien+i)->x += velocidade;
                }else if((alien+i)->x > nave->x){
                    (alien+i)->x -= velocidade;
                }if ((alien+i)->y < nave->y){
                    (alien+i)->y += velocidade;
                }else if ((alien+i)->y > nave->y){
                    (alien+i)->y -= velocidade;
                }
             }
        }
    }

}

void atualizar_especial(Especial * esp,Nave * nave){
    esp->x = nave->x;
    esp->y = nave->y;

}



//---------------------------------------------------------------------------------------------------funções-de-colisão----

void coli_nave_asteroid(Nave * nave,Asteroids * asteroid,sfMusic * explosion){
    if (asteroid->vivo == 's'){
        if (((nave->x >= asteroid->x-20)  &&
             (nave->x <= asteroid->x+20)) &&
             ((nave->y >= asteroid->y-15) &&
             (nave->y <= asteroid->y+15)) && nave->vivo == 's'){
            if (nave->hp <= 0){
                nave->vivo = 'n';                
                sfMusic_play(explosion);
            }
             else
                nave->hp -= 10;
        }
    }
}



void coli_tiro_asteroid(Tiro * tiro,Asteroids * asteroid,Nave * nave,sfMusic * explosion){
    if(((tiro->x >= asteroid->x-20)  &&
        (tiro->x <= asteroid->x+20)) &&
        ((tiro->y >= asteroid->y-20) &&
        (tiro->y <= asteroid->y+20))){
        sfMusic_play(explosion);
        nave->pontuacao += 1;
        asteroid->vivo = 'n';
        tiro->exite = 'n';
        asteroid->x = 0;
        asteroid->y = 0;
        tiro->x = -100;
        tiro->y = -100;
    }
}



void coli_asteroid_asteroid(Asteroids * asteroid1,Asteroids * asteroid){
    if(((asteroid1->x >= asteroid->x-20)  &&
        (asteroid1->x <= asteroid->x+20)) &&
        ((asteroid1->y >= asteroid->y-20) &&
        (asteroid1->y <= asteroid->y+20))){
        asteroid->rotacao += 1;
        asteroid1->rotacao += 1;

   }
}




void coli_especial_asteroid(Especial * esp,Asteroids * asteroid,Nave * nave){

    if(((asteroid->x >= esp->x-100)  &&
        (asteroid->x <= esp->x+100)) &&
        ((asteroid->y >= esp->y-100) &&
        (asteroid->y <=  esp->y+100))){
        nave->pontuacao += 1;
        asteroid->vivo = 'n';
        asteroid->x = -10;
        asteroid->y = -10;
   }
}

void coli_alien_nave(Alien * alien,Nave * nave){

    if(((nave->x >= alien->x-20)  &&
        (nave->x <= alien->x+20)) &&
        ((nave->y >= alien->y-20) &&
        (nave->y <=  alien->y+20))){
        if (nave->hp <= 0)
            nave->vivo = 'n';
         else
            nave->mp -= 1;
            nave->hp -= 1;
   }
}

void coli_alien_alien(Alien * alien,Alien * alien2){

    if(((alien2->x >= alien->x-50)  &&
        (alien2->x <= alien->x+50)) &&
        ((alien2->y >= alien->y-50) &&
        (alien2->y <= alien->y+50))){
        alien2->alien_perto = 's';
        alien->x += 1;
        alien->y += 1;
        alien2->x -= 1;
        alien2->y -= 1;
    }else{
        alien2->alien_perto = 'n';
    }
}


void coli_tiro_alien(Tiro * tiro,Alien * alien,Nave * nave){
    if(((tiro->x >= alien->x-20)  &&
        (tiro->x <= alien->x+20)) &&
        ((tiro->y >= alien->y-20) &&
        (tiro->y <= alien->y+20))){
        nave->pontuacao += 1;
        tiro->exite = 'n';
        alien->x = 0;
        alien->y = 0;
        tiro->x = 0;
        tiro->y = 0;
   }
}


void coli_especial_alien(Especial * esp,Alien * alien,Nave * nave){

    if(((alien->x >= esp->x-100)  &&
        (alien->x <= esp->x+100)) &&
        ((alien->y >= esp->y-100) &&
        (alien->y <=  esp->y+100))){
        nave->pontuacao += 1;
        alien->x = 0;
        alien->y = 0;
   }
}



//-------------------------------------------------------------------------------------------------------função-desenho----

void desenhar_na_tela(sfRenderWindow ** janela,sfSprite ** sprite,int x, int y){
    sfSprite_setPosition(*sprite,(sfVector2f){x,y});
    sfRenderWindow_drawSprite(*janela, *sprite,NULL);
}




//----------------------------------------------------------------------------------------------------------------texto----


void criar_texto(int escore,sfText ** Texto,sfFont ** fonte, sfRenderWindow ** janela){
    char texto[100];
    sprintf(texto,"escore: %d",escore);
    sfText_setString(*Texto,texto);
    sfText_setFont(*Texto,*fonte);
    sfVector2f par = {0,580};
    sfText_setPosition(*Texto,par);
    sfText_setCharacterSize(*Texto,11);
    sfText_setColor(*Texto,sfWhite);
    sfRenderWindow_drawText(*janela,*Texto,NULL);
}
