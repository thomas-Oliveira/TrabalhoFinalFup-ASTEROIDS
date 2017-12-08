#include <stdio.h>
#include <SFML/Graphics.h>
#include "funcoes_gerais.h"
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.h>
#include <stdlib.h>

int main(void){
//-------------------------------------------------------------------------------------------------------------VARIVEIS----
    srand(time(NULL));

    enum {tamanho_tela_altura = 600};
    enum {tamanho_tela_largura = 800};
    enum {max_tiros = 1000};
    enum {max_time = 10};
    enum {max_alien = 1000};
    enum {max_asteroids = 1000};

    int i;
    int tiro_qtd = 0;
    int alien_qtd = 2;
    int asteroids_qtd = 10;
    char inicio = 'n';
//----------------------------------------------------------------------------------------------------------------Tempo----
    sfClock * tempo_alien;
    tempo_alien = sfClock_create();
    sfClock * tempo_asteroids;
    tempo_asteroids = sfClock_create();
    sfClock * tempo;
    tempo = sfClock_create();

//----------------------------------------------------------------------------------------------------------------TEXTO----
    sfFont * fonte;
    fonte = sfFont_createFromFile("/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-B.ttf");
    sfText * texto;
    texto = sfText_create();
//--------------------------------------------------------------------------------------------------------trilha-sonora----
    sfMusic * Explosion;
    Explosion = sfMusic_createFromFile("../audio/Explosion.wav");
    sfMusic * musica_fundo;
    musica_fundo = sfMusic_createFromFile("../audio/musica_fundo.ogg");
    sfMusic * bala;
    bala = sfMusic_createFromFile("../audio/Laser_Shoot.wav");
    sfMusic * especial_audio;
    especial_audio = sfMusic_createFromFile("../audio/especial.wav");


//-----------------------------------------------------------------------------------------CRIAÇÃO-DE-TEXTURAS-E-SPRITE----
    //textura universal
    sfTexture * tex;

//----------------------------------------------------------------------------------------------------------------ALIEN----

    //criando alien
    Alien aliens[max_alien];
    for(i=0;i<max_alien;i++)
        criar_alien(&aliens[i],rand()%tamanho_tela_altura,rand()%tamanho_tela_largura);

    //sprite nave inimiga
    sfSprite * salien;
    Criar_sprite_textura("../imagens/alien.png",&tex,&salien,0.05,0.05);

//-------------------------------------------------------------------------------------------------------------------HP----

    //sprite HP
    sfSprite * shp;
    Criar_sprite_textura("../imagens/hp.png",&tex,&shp,0.02,0.04);

//-------------------------------------------------------------------------------------------------------------------MP----

    //Sprite MP
    sfSprite * smp;
    Criar_sprite_textura("../imagens/Mp.png",&tex,&smp,0.02,0.04);

//------------------------------------------------------------------------------------------------------------GAME-OVER----
    // sprite game over
    sfSprite * sgame_over;
    Criar_sprite_textura("../imagens/you_dead.png",&tex,&sgame_over,1,1);
//-------------------------------------------------------------------------------------------------------------ESPECIAL----

    //criando especial
    Especial especial;

    //criar sprite do especial
    sfSprite * sespecial;
    Criar_sprite_textura("../imagens/especial3.png",&tex,&sespecial,0.5,0.5);
    sfSprite_setOrigin(sespecial,(sfVector2f){447,447});

//------------------------------------------------------------------------------------------------------------ASTEROID-----

    // criar asteroid
    Asteroids asteroids[max_asteroids];
        for(i = 0; i < max_asteroids;i++)
            criar_asteroids(&asteroids[i],rand()%tamanho_tela_altura,rand()%tamanho_tela_largura,rand()%11,'g');

    //criar sprite asteroid
    sfSprite * sasteroid;
    Criar_sprite_textura("../imagens/asteroid.png",&tex,&sasteroid,0.3,0.3);
    sfSprite_setOrigin(sasteroid,(sfVector2f){64,64});

//-----------------------------------------------------------------------------------------------------------UNIVERSO------

    //adicionar sprite universo
    sfSprite * suniverso;
    Criar_sprite_textura("../imagens/universo.jpg",&tex,&suniverso,0.8,0.6);

//--------------------------------------------------------------------------------------------------------------NAVE-------

    //criar nave
    Nave jupter;
    criar_nave(&jupter,tamanho_tela_largura,tamanho_tela_altura);

    //criando sprite nave
    sfSprite * sjupter;
    Criar_sprite_textura("../imagens/nave.png",&tex,&sjupter,0.1,0.1);
    sfSprite_setOrigin(sjupter, (sfVector2f){299,200});

//--------------------------------------------------------------------------------------------------------------TIRO-------

    //criado tiro
    Tiro tiros[max_tiros];
    for(i=0;i<tiro_qtd;i++)
        criar_tiro(&tiros[i],jupter.x,jupter.y);

    //criando sprite de tiro
    sfSprite * stiro;
    Criar_sprite_textura("../imagens/tiro.png",&tex,&stiro,0.009,0.009);
    sfSprite_setOrigin(stiro,(sfVector2f){jupter.x,jupter.y});

//--------------------------------------------------------------------------------------------------------------TELA-------

    //criação da tela
    sfRenderWindow * janela;
    sfVideoMode mode = {tamanho_tela_largura,tamanho_tela_altura, 32};
    janela = sfRenderWindow_create(mode,"Ateroids",sfResize | sfClose, NULL);
    sfColor fundo = sfBlack;

    sfSprite * tela_de_inicio;
    Criar_sprite_textura("../imagens/tela_de_inicio.jpg",&tex,&tela_de_inicio,1,1);
//------------------------------------------------------------------------------------------------------MUSICA-DE-FUNDO----
    sfMusic_play(musica_fundo);
    sfMusic_setVolume(musica_fundo,30);
//-----------------------------------------------------------------------------------------------------------------LAÇO----

    //evento de abertura e fechamento de tela
    while(sfRenderWindow_isOpen(janela)){
        sfEvent close;
        while(sfRenderWindow_pollEvent(janela, &close)){
            if(close.type == sfEvtClosed){
               sfRenderWindow_close(janela);
            }

        }
        sfRenderWindow_setFramerateLimit(janela,30);
        tela(&inicio,&janela,&tela_de_inicio,&jupter,tamanho_tela_altura,tamanho_tela_largura,
             &tiro_qtd,&alien_qtd,&asteroids_qtd,&asteroids,max_asteroids);

//-------------------------------------------------------------------------------------------------------MOVIMETAR-NAVE----
        movimentar_nave_2(&jupter,sjupter);
//-----------------------------------------------------------------------------------------------------MIVIMENTAR-ALIEN----
        mover_alien(&aliens[0],&jupter,alien_qtd);
//--------------------------------------------------------------------------------------------------MOVIMENTAR-ASTEROID----
        movimentar_asteroid(&asteroids[0],sasteroid,max_asteroids);
//---------------------------------------------------------------------------------------------------CRIAR-TIRO-NO-JOGO----
        criar_tiro_no_jogo(tempo,&jupter,&tiro_qtd,tiros,bala,max_tiros);
//---------------------------------------------------------------------------------------------------------------BORDAS----
        bordas(asteroids,&jupter,aliens,alien_qtd,max_asteroids,tamanho_tela_largura,tamanho_tela_altura);
//--------------------------------------------------------------------------------------------------------------IMPACTO----
        impacto(&jupter,asteroids,tiros,aliens,asteroids_qtd,alien_qtd,tiro_qtd,Explosion);
//-----------------------------------------------------------------------------------------------------POSIÇÃO-ESPECIAL----
        atualizar_especial(&especial,&jupter);
//--------------------------------------------------------------------------------------------------------DESENHAR-TELA----
        sfRenderWindow_display(janela);
        sfRenderWindow_clear(janela, fundo);
//----------------------------------------------------------------------------------------------------DESENHAR-UNIVERSO----
        desenhar_na_tela(&janela,&suniverso,0,0);
//----------------------------------------------------------------------------------------------------------DESENHAR-MP----
        for(i=0;i<jupter.mp;i++)
            desenhar_na_tela(&janela,&smp,i+400,0);
//----------------------------------------------------------------------------------------------------------DESENHAR-HP----
        for(i=0;i<jupter.hp;i++)
            desenhar_na_tela(&janela,&shp,i+1,0);
//----------------------------------------------------------------------------------------------------DESENHAR-ESPECIAL----
        desenho_especial(&jupter,&especial,&sespecial,especial_audio,max_asteroids,&janela,asteroids,max_tiros,aliens);
//---------------------------------------------------------------------------------------------------------DESENHO-TIRO----
        desenho_tiro(tiro_qtd, tiros, &janela,&jupter,&stiro);
//--------------------------------------------------------------------------------------------------------DESENHO-ALIEN----
        for(i=0;i<alien_qtd;i++)
            desenhar_na_tela(&janela,&salien,aliens[i].x,aliens[i].y);
//--------------------------------------------------------------------------------------------------------DESENHAR-NAVE----
        desenhar_nave(&jupter,&janela,&sjupter);
//---------------------------------------------------------------------------------------------------DESENHAR-ASTEROIDS----
        desenhar_asteroids(asteroids,&janela,&sasteroid,asteroids_qtd);
//------------------------------------------------------------------------------------------------------------pontuação----
        criar_texto(jupter.pontuacao,&texto,&fonte,&janela);
//------------------------------------------------------------------------------------------------------------GAME-OVER----
        game_over(&janela,&sgame_over,&jupter);
//--------------------------------------------------------------------------------------------------------PROXIMO-NIVEL----
        if ((sfClock_getElapsedTime(tempo_asteroids).microseconds > sfMilliseconds(2000).microseconds)){
            asteroids_qtd += 1;
            sfClock_restart(tempo_asteroids);
        }if ((sfClock_getElapsedTime(tempo_alien).microseconds > sfMilliseconds(6000).microseconds)){
            alien_qtd += 1;
            sfClock_restart(tempo_alien);
        }        


    }
    sfFont_destroy(fonte);
    sfText_destroy(texto);
    sfTexture_destroy(tex);
    sfClock_destroy(tempo);
    sfMusic_destroy(Explosion);
    sfMusic_destroy(musica_fundo);
    sfMusic_destroy(bala);
    sfMusic_destroy(especial_audio);    
    sfSprite_destroy(sgame_over);
    sfSprite_destroy(stiro);
    sfSprite_destroy(sespecial);
    sfSprite_destroy(sasteroid);
    sfSprite_destroy(suniverso);
    sfSprite_destroy(sjupter);
    sfRenderWindow_destroy(janela);

    return 0;
}
