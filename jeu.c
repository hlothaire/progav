/**
 * \file jeu.h
 * \author Lothaire Holcvart
 * \brief Gestion du jeu, pacman et des fantomes
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include "jeu.h"

#define SPRITE_SIZE 32
#define SPRITE_HEIGHT 32
#define PACMAN_HEIGHT 30
#define XdepartJ 160
#define YdepartJ 160
#define XdepartF1 32
#define YdepartF1 32
#define XdepartF2 32
#define YdepartF2 448
#define XdepartF3 448
#define YdepartF3 448
#define XdepartF4 448
#define YdepartF4 32


void init_pacman(pacman_t* pacman,int PosX, int PosY)
{
    pacman->PosX = PosX;
    pacman->PosY = PosY;
    pacman->NbVie = 3;
    pacman->is_visible = 0;
    pacman->ori = 4;
}

void init_fantome(fantome_t* fantome,int PosX, int PosY, int Difficulte)
{
    fantome->PosX = PosX;
    fantome->PosY = PosY;
    fantome->Difficulte = Difficulte;
    fantome->is_visible = 0;
}

void init_sprite(sprite_t* sprite,int x,int y,int id)
{
  sprite->x = x;
  sprite->y = y;
  sprite->id = id ;
  sprite->is_visible = 0;
}

void init_data(world_t* world)
{
  world->gameover = 0;
  world->joueur = malloc(5*sizeof(int));
  world->fantome1 = malloc(4*sizeof(int));
  world->fantome2 = malloc(4*sizeof(int));
  world->fantome3 = malloc(4*sizeof(int));
  world->fantome4 = malloc(4*sizeof(int));
  world->mur = (sprite_t**)malloc(world->nb_mur*sizeof(sprite_t*));
  for(int j =0; j<world->nb_mur; j++){
      world->mur[j] = malloc(4*sizeof(int));
  }
  world->gomme = (sprite_t**)malloc(world->nb_gomme*sizeof(sprite_t*));
  for(int i =0; i<world->nb_gomme; i++){
      world->gomme[i] = malloc(4*sizeof(int));
  }
  world->supgomme = (sprite_t**)malloc(world->nb_supgomme*sizeof(sprite_t*));
  for(int l = 0; l<world->nb_supgomme; l++){
    world->supgomme[l] = malloc(4*sizeof(int));
  }
  init_pacman(world->joueur,XdepartJ,YdepartJ);
  init_fantome(world->fantome1,XdepartF1,YdepartF1,1);
  init_fantome(world->fantome2,XdepartF2,YdepartF2,4);
  init_fantome(world->fantome3,XdepartF3,YdepartF3,3);
  init_fantome(world->fantome4,XdepartF4,YdepartF4,4);
}

void clean_data(world_t* world)
{
  free(world->joueur);
  free(world->fantome1);
  free(world->fantome2);
  free(world->fantome3);
  free(world->fantome4);
  free(world->mur);
  free(world->gomme);
  free(world->supgomme);
}

void set_visible(sprite_t* sprite)
{
    sprite->is_visible = 0;
}

void set_invisible(sprite_t* sprite)
{
    sprite->is_visible = 1;
}

void set_all_invisible(world_t* world)
{
  for(int i=0; i<world->nb_gomme; i++){
    set_invisible(world->gomme[i]);
  }
  for(int j=0; j<world->nb_mur; j++){
    set_invisible(world->mur[j]);
  }
  for(int l=0; l<world->nb_supgomme; l++){
    set_invisible(world->supgomme[l]);
  }
  world->joueur->is_visible = 1;
  world->fantome1->is_visible = 1;
  world->fantome2->is_visible = 1;
  world->fantome3->is_visible = 1;
  world->fantome4->is_visible = 1;
}

int is_game_over(world_t *world)
{
    return world->gameover;
}

void handle_events(SDL_Event *event,world_t *world)
{
  while( SDL_PollEvent( event ) ) {
    if( event->type == SDL_QUIT ) {
      world->gameover = 1;
    }
    if(event->type == SDL_KEYDOWN){
      if(event->key.keysym.sym == SDLK_ESCAPE){
        world->gameover = 1;
      }
      switch(event->key.keysym.sym)
      {
        case SDLK_z:
            move_fantomes(world);
            if(collision_fantomes(world) == 0){
                if(collision_wall(world->joueur->PosX, (world->joueur->PosY - SPRITE_SIZE),world) == 0){
                    world->joueur->PosY -= SPRITE_SIZE;
                    world->joueur->ori = 1;
                    collision_fantomes(world);
                    break;
                }
            }
            collision_fantomes(world);
            break;
        case SDLK_s:
            move_fantomes(world);
            if(collision_fantomes(world) == 0){
                if(collision_wall(world->joueur->PosX, (world->joueur->PosY + SPRITE_SIZE),world) == 0){
                    world->joueur->PosY += SPRITE_SIZE;
                    world->joueur->ori = 2;
                    collision_fantomes(world);
                    break;
                }
            }
            collision_fantomes(world);
            break;
        case SDLK_q:
            move_fantomes(world);
            if(collision_fantomes(world) == 0){
                if(collision_wall(world->joueur->PosX - SPRITE_SIZE,world->joueur->PosY,world) == 0){
                    world->joueur->PosX -= SPRITE_SIZE;
                    world->joueur->ori = 3;
                    collision_fantomes(world);
                    break;
                }
            }
            collision_fantomes(world);
            break;

        case SDLK_d:
            move_fantomes(world);
            if(collision_fantomes(world) == 0){
                if(collision_wall(world->joueur->PosX + SPRITE_SIZE,world->joueur->PosY,world) == 0){
                    world->joueur->PosX += SPRITE_SIZE;
                    world->joueur->ori = 4;
                    collision_fantomes(world);
                    break;
                }
            }
            collision_fantomes(world);
            break;
        }
      }
    }
  }

void init_mur(world_t *world,int x,int y,int index)
 {
   init_sprite(world->mur[index],x,y,2);
 }

void init_gomme(world_t *world,int x,int y,int index)
  {
    init_sprite(world->gomme[index],x,y,1);
  }

void init_supgomme(world_t *world,int x,int y,int index)
  {
    init_sprite(world->supgomme[index],x,y,1);
  }

int collision(int x, int y,sprite_t *sprite)
{
  int d;
  d = sqrt(pow((x - sprite->y), 2) + pow((y - sprite->x), 2));
  if(d<=(PACMAN_HEIGHT + SPRITE_HEIGHT)/2){
      return 1;
  }
  return 0;
}

int collision_wall(int x,int y,world_t *world)
{
  for(int i=0;i<world->nb_mur;i++){
    if(collision(x,y,world->mur[i]) == 1){
      return 1;
    }
  } return 0;
}

void collision_gomme(world_t *world)
{
  for(int i=0;i<world->nb_gomme;i++){
    if((collision(world->joueur->PosX,world->joueur->PosY,world->gomme[i]) == 1) && world->gomme[i]->is_visible == 0){
      set_invisible(world->gomme[i]);
      world->score += 150;
    }
  }
}

void collision_supgomme(world_t *world)
{
  for(int i=0;i<world->nb_supgomme;i++){
    if((collision(world->joueur->PosX,world->joueur->PosY,world->supgomme[i]) == 1) && world->supgomme[i]->is_visible == 0){
      set_invisible(world->supgomme[i]);
      world->score += 3000;
    }
  }
}

int collision_fantome(world_t *world, fantome_t *fantome)
{
    if(world->joueur->PosX == fantome->PosX && world->joueur->PosY == fantome->PosY){
        world->joueur->PosX = XdepartJ;
        world->joueur->PosY = YdepartJ;

        world->fantome1->PosX = XdepartF1;
        world->fantome1->PosY = YdepartF1;

        world->fantome2->PosX = XdepartF2;
        world->fantome2->PosY = YdepartF2;

        world->fantome3->PosX = XdepartF3;
        world->fantome3->PosY = YdepartF3;

        world->fantome4->PosX = XdepartF4;
        world->fantome4->PosY = YdepartF4;

        world->joueur->NbVie += -1;
        world->score += -150;
        if(world->joueur->NbVie <= 0){
            world->gameover = 1;
        }
        return 1;
    }
    return 0;
}

int collision_fantomes(world_t *world)
{
    if(collision_fantome(world, world->fantome1) == 1){
        return 1;
    }
    if(collision_fantome(world, world->fantome2) == 1){
        return 1;
    }
    if(collision_fantome(world, world->fantome3) == 1){
        return 1;
    }
    if(collision_fantome(world, world->fantome4) == 1){
        return 1;
    }
    return 0;
}

void update_data(world_t *world)
{
  collision_gomme(world);
  collision_supgomme(world);
}

void move_fantomes(world_t *world)
{
    move_fantome(world, world->fantome1);
    move_fantome(world, world->fantome2);
    move_fantome(world, world->fantome3);
    move_fantome(world, world->fantome4);
}

void move_fantome(world_t *world, fantome_t *fantome)
{
    int PosXJ = world->joueur->PosX;
    int PosYJ = world->joueur->PosY;
    int PosXF = fantome->PosX;
    int PosYF = fantome->PosY;
    //difference de position
    int DX = abs(PosXF - PosXJ);
    int DY = abs(PosYF - PosYJ);

    int direction;
    switch(fantome->Difficulte)
    {
        case 1:
            //Si la distance en X est plus grande qu'en Y, alors on bouge sur X
            if(DX > DY){
                //Si F est plus a droite
                if(PosXF > PosXJ){
                    //detection collision gauche
                    if(collision_wall((PosXF - SPRITE_SIZE), PosYF,world) == 0)
                    {
                        fantome->PosX -= SPRITE_SIZE;
                    }else{
                        if(collision_wall(PosXF, (PosYF - SPRITE_SIZE),world) == 0){
                            fantome->PosY -= SPRITE_SIZE;
                        }else{
                            fantome->PosY += SPRITE_SIZE;
                        }
                    }
                }else{
                    //dectection collision droite
                    if(collision_wall((PosXF + SPRITE_SIZE), PosYF,world) == 0){
                        fantome->PosX += SPRITE_SIZE;
                    }else{
                        if(collision_wall(PosXF, (PosYF - SPRITE_SIZE),world) == 0){
                            fantome->PosY -= SPRITE_SIZE;
                        }else{
                            fantome->PosY += SPRITE_SIZE;
                        }
                    }
                }
            }else{
                if(PosYF >= PosYJ){
                    //dectection collision haut
                    if(collision_wall(PosXF, (PosYF - SPRITE_SIZE),world) == 0){
                        fantome->PosY -= SPRITE_SIZE;
                    }else{
                        if(collision_wall((PosXF + SPRITE_SIZE), PosYF,world) == 0){
                            fantome->PosX += SPRITE_SIZE;
                        }else{
                            fantome->PosX -=SPRITE_SIZE;
                        }
                    }
                }else{
                    //Detection collision bas
                    if(collision_wall(PosXF, (PosYF + SPRITE_SIZE),world) == 0){
                        fantome->PosY += SPRITE_SIZE;
                    }else{
                        if(collision_wall((PosXF - SPRITE_SIZE), PosYF,world) == 0){
                            fantome->PosX -= SPRITE_SIZE;
                        }else{
                            fantome->PosX +=SPRITE_SIZE;
                        }
                    }
                }
            }
            break;
        //case 2: a definir
        case 3:
            direction = rand() % 10 + 1;
            if(direction > 5){
                if(collision_wall((PosXF + SPRITE_SIZE), PosYF,world) == 0){
                        fantome->PosX += SPRITE_SIZE;
                    }else{
                        if(collision_wall(PosXF, (PosYF - SPRITE_SIZE),world) == 0){
                            fantome->PosY -= SPRITE_SIZE;
                        }else{
                            fantome->PosY += SPRITE_SIZE;
                        }
                    }

            }else{
                if(collision_wall((PosXF - SPRITE_SIZE), PosYF,world) == 0){
                        fantome->PosX -= SPRITE_SIZE;
                    }else{
                        if(collision_wall(PosXF, (PosYF + SPRITE_SIZE),world) == 0){
                            fantome->PosY += SPRITE_SIZE;
                        }else{
                            fantome->PosY -= SPRITE_SIZE;
                        }
                    }
            }
            break;

        default:
            direction = rand() % 4 + 1;
            switch(direction){
                //haut
                case 1:
                    if(collision_wall(PosXF, (PosYF - SPRITE_SIZE),world) == 0){
                        fantome->PosY -= SPRITE_SIZE;
                    }else{
                        if(collision_wall((PosXF + SPRITE_SIZE), PosYF,world) == 0){
                            fantome->PosX += SPRITE_SIZE;
                        }else{
                            fantome->PosX -=SPRITE_SIZE;
                        }
                    }
                    break;
                //bas
                case 2:
                    if(collision_wall(PosXF, (PosYF + SPRITE_SIZE),world) == 0){
                        fantome->PosY += SPRITE_SIZE;
                    }else{
                        if(collision_wall((PosXF - SPRITE_SIZE), PosYF,world) == 0){
                            fantome->PosX -= SPRITE_SIZE;
                        }else{
                            fantome->PosX +=SPRITE_SIZE;
                        }
                    }
                    break;
                //droite
                case 3:
                    if(collision_wall((PosXF + SPRITE_SIZE), PosYF,world) == 0){
                        fantome->PosX += SPRITE_SIZE;
                    }else{
                        if(collision_wall(PosXF, (PosYF - SPRITE_SIZE),world) == 0){
                            fantome->PosY -= SPRITE_SIZE;
                        }else{
                            fantome->PosY += SPRITE_SIZE;
                        }
                    }
                    break;
                //gauche
                case 4:
                    if(collision_wall((PosXF - SPRITE_SIZE), PosYF,world) == 0)
                    {
                        fantome->PosX -= SPRITE_SIZE;
                    }else{
                        if(collision_wall(PosXF, (PosYF + SPRITE_SIZE),world) == 0){
                            fantome->PosY += SPRITE_SIZE;
                        }else{
                            fantome->PosY -= SPRITE_SIZE;
                        }
                    }
                    break;
            }

    }
}
