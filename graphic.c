/**
 * \file graphic.h
 * \author Lothaire Holcvart
 * \brief bibliotheque gestion textures et affichage graphique
 */

#include "graphic.h"


void clean_texture(SDL_Texture *texture)
{
  if(NULL != texture){
      SDL_DestroyTexture(texture);
    }
}

void clean_textures(textures_t *textures)
{
  clean_texture(textures->pacmanb);
  clean_texture(textures->pacmanl);
  clean_texture(textures->pacmanr);
  clean_texture(textures->pacmanu);
  clean_texture(textures->fantome1);
  clean_texture(textures->fantome2);
  clean_texture(textures->fantome3);
  clean_texture(textures->fantome4);
  clean_texture(textures->gomme);
  clean_texture(textures->mur);
  clean_texture(textures->supgomme);
  clean_font(textures->font);
  clean_texture(textures->vie);
}

void  init_textures(SDL_Renderer *renderer, textures_t *textures)
{
  textures->pacmanb = load_imageJ("ressources/sprites/pacmanb.bmp",renderer);
  textures->pacmanl = load_imageJ("ressources/sprites/pacmanl.bmp",renderer);
  textures->pacmanr = load_imageJ("ressources/sprites/pacmanr.bmp",renderer);
  textures->pacmanu = load_imageJ("ressources/sprites/pacmanu.bmp",renderer);
  textures->fantome1 = load_imageJ("ressources/sprites/fantome1.bmp",renderer);
  textures->fantome2 = load_imageJ("ressources/sprites/fantome2.bmp",renderer);
  textures->fantome3 = load_imageJ("ressources/sprites/fantome3.bmp",renderer);
  textures->fantome4 = load_imageJ("ressources/sprites/fantome4.bmp",renderer);
  textures->mur = load_image("ressources/sprites/bloc.bmp",renderer);
  textures->gomme = load_image("ressources/sprites/gomme.bmp",renderer);
  textures->supgomme = load_image("ressources/sprites/supGom.bmp",renderer);
  textures->font = load_font("ressources/arial.ttf",14);
  textures->vie = load_image("ressources/sprites/vie.bmp",renderer);
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t * sprite)
{
    apply_texture(texture,renderer,sprite->x,sprite->y);
}

void apply_player(SDL_Renderer *renderer,SDL_Texture *texture,pacman_t *pacman)
{
  apply_texture(texture,renderer,pacman->PosX,pacman->PosY);
}

void apply_fantome(SDL_Renderer *renderer,SDL_Texture *texture,fantome_t *fantome)
{
  apply_texture(texture,renderer,fantome->PosX,fantome->PosY);
}

void clear_renderer(SDL_Renderer *renderer){
  SDL_RenderClear(renderer);
}

void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y){
  SDL_Rect dst = {0, 0, 0, 0};

  SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
  dst.x = x; dst.y=y;

  SDL_RenderCopy(renderer, texture, NULL, &dst);
}


SDL_Texture *load_image(const char path[], SDL_Renderer *renderer){
  SDL_Surface *tmp = NULL;
  SDL_Texture *texture = NULL;
  tmp = SDL_LoadBMP(path);
  if(NULL == tmp)
  {
      fprintf(stderr, "Erreur pendant chargement image BMP: %s", SDL_GetError());
      return NULL;
  }
  texture = SDL_CreateTextureFromSurface(renderer, tmp);
  SDL_FreeSurface(tmp);
  if(NULL == texture)
  {
      fprintf(stderr, "Erreur pendant creation de la texture: %s", SDL_GetError());
      return NULL;
  }
  return texture;
}

void update_screen(SDL_Renderer *renderer){
  SDL_RenderPresent(renderer);
}

void clean_sdl(SDL_Renderer *renderer,SDL_Window *window){
  if(NULL != renderer)
      SDL_DestroyRenderer(renderer);
  if(NULL != window)
      SDL_DestroyWindow(window);
  SDL_Quit();
}

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height){
  if(0 != SDL_Init(SDL_INIT_VIDEO))
  {
      fprintf(stderr, "Erreur initialisation de la SDL : %s", SDL_GetError());
      return -1;
  }
  if(0 != SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer))
  {
      fprintf(stderr, "Erreur lors de la creation de l'image et du renderer : %s", SDL_GetError());
      return -1;
  }
  return 0;
}

SDL_Texture *load_imageJ(const char path[], SDL_Renderer *renderer){
  SDL_Surface *tmp = NULL;
  SDL_Texture *texture = NULL;
  tmp = SDL_LoadBMP(path);
  if(NULL == tmp)
  {
      fprintf(stderr, "Erreur pendant chargement image BMP: %s", SDL_GetError());
      return NULL;
  }
  SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 0, 0, 0));
  texture = SDL_CreateTextureFromSurface(renderer, tmp);
  SDL_FreeSurface(tmp);
  if(NULL == texture)
  {
      fprintf(stderr, "Erreur pendant creation de la texture: %s", SDL_GetError());
      return NULL;
  }
  return texture;
}

void apply_mur(SDL_Renderer *renderer, SDL_Texture *textures, world_t* world)
{
  for(int i=0;i<world->nb_mur;i++){
    if(world->mur[i]->is_visible ==0){
      apply_texture(textures,renderer,world->mur[i]->y,world->mur[i]->x);
    }
  }
}

void apply_gomme(SDL_Renderer *renderer, SDL_Texture *textures, world_t* world)
{
  for(int i=0;i<world->nb_gomme;i++){
    if(world->gomme[i]->is_visible ==0){
      apply_texture(textures,renderer,world->gomme[i]->y,world->gomme[i]->x);
    }
  }
}

void apply_supgomme(SDL_Renderer *renderer, SDL_Texture *textures, world_t* world)
{
  for(int i=0;i<world->nb_supgomme;i++){
    if(world->supgomme[i]->is_visible ==0){
      apply_texture(textures,renderer,world->supgomme[i]->y,world->supgomme[i]->x);
    }
  }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures)
{
  char  conv[20] = "";
  sprintf(conv, "score = %d", world->score);
  clear_renderer(renderer);
  apply_mur(renderer,textures->mur,world);
  apply_gomme(renderer,textures->gomme,world);
  apply_supgomme(renderer,textures->supgomme,world);
  if(world->joueur->is_visible == 0){
    switch(world->joueur->ori)
    {
      case 1:
          apply_player(renderer,textures->pacmanu,world->joueur);
          break;
      case 2:
          apply_player(renderer,textures->pacmanb,world->joueur);
          break;
      case 3:
          apply_player(renderer,textures->pacmanl,world->joueur);
          break;
      case 4:
          apply_player(renderer,textures->pacmanr,world->joueur);
          break;
    }

  }
  if(world->fantome1->is_visible == 0){
      apply_fantome(renderer,textures->fantome1,world->fantome1);
  }
  if(world->fantome2->is_visible == 0){
      apply_fantome(renderer,textures->fantome2,world->fantome2);
  }
  if(world->fantome3->is_visible == 0){
      apply_fantome(renderer,textures->fantome3,world->fantome3);
  }
  if(world->fantome4->is_visible == 0){
      apply_fantome(renderer,textures->fantome4,world->fantome4);
  }
  if(world->gameover == 0){
    apply_text(renderer,10,520,80,30,conv,textures->font);
  }
  if(world->gameover == 1){
    apply_text(renderer,100,260,160,70,conv,textures->font);
  }
  print_life(renderer,textures->vie,world);
  SDL_RenderPresent(renderer);
}

void init_ttf()
{
  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
  }
}

TTF_Font * load_font(const char *path, int font_size)
{
  TTF_Font *font = TTF_OpenFont(path, font_size);
  if(font == NULL){
    fprintf(stderr, "Erreur pendant chargement font: %s\n", SDL_GetError());
  }
  return font;
}

void apply_text(SDL_Renderer *renderer,int x, int y, int w, int h, const char *text, TTF_Font *font)
{
  SDL_Color color = { 255, 255, 255 };
  SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Rect dstrect2 = {x, y, w, h};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect2);

}

void clean_font(TTF_Font * font)
{
  TTF_CloseFont(font);
}

void print_life(SDL_Renderer *renderer,SDL_Texture *textures, world_t* world)
{
  int x = 200;
  int y = 530;
  for(int i = 0; i<world->joueur->NbVie;i++){
    apply_texture(textures,renderer,x,y);
    x += 15;
  }
}
