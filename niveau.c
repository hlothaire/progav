/**
 * \file niveau.c
 * \author Lothaire Holcvart 
 * \brief bibliotheque gestion niveau
 */

#include"niveau.h"

#define nblig 20
#define nbcol 20

char** allouer_tab_2D(int n, int m){
    char** tab = malloc(n * sizeof(char*));
    for(int i =0; i<n; i++){
        tab[i] = malloc(m * sizeof(char*));
    }
     for(int i =0; i<n; i++){
          for(int j =0; j<m; j++){
              tab[i][j] = ' ';
          }
     }
     return tab;
}

void desallouer_tab_2D(char** tab, int n){
    for(int i = 0; i<n; i++){
        free(tab[i]);
    }
}

char** lire_fichier(const char* nomFichier){
  FILE* fichier = fopen(nomFichier, "r");
  if (fichier == NULL){
    printf("Impossible d'ouvrir le fichier text : %s",nomFichier);
  } else {

    char ch[nblig*nbcol];
    char** tab = allouer_tab_2D(nblig,nbcol);

    int i = 0;
    while (fgets(ch, nblig*nbcol, fichier) != NULL){
      for(int j = 0; j< nbcol ; j++){
          tab[i][j] = ch[j];
      }
      i++;
    }
    fclose(fichier);
    return tab;
  }
}

void nb_element(char** tab,world_t *world)
{
  world->nb_gomme = 0;
  world->nb_supgomme = 0;
  world->nb_mur = 0;
  for(int i =0;i<nblig;i++){
    for(int j= 0;j<nbcol;j++){
      if(tab[i][j] == '1'){
        world->nb_gomme ++;
      }
      if(tab[i][j] == '2'){
        world->nb_mur ++;
      }
      if(tab[i][j] == '3'){
        world->nb_supgomme ++;
      }
    }
  }
}

void create_level(char** tab,world_t *world)
{
  int gomme = 0;
  int mur = 0;
  int supgomme = 0;
  for(int i = 0;i<nblig;i++){
    for(int j = 0;j<nbcol;j++){
      int x = i*32;
      int y = j*32;
      switch(tab[i][j])
      {
        case '1':
            init_gomme(world,x,y,gomme);
            gomme ++;
            break;
        case '2':
            init_mur(world,x,y,mur);
            mur ++;
            break;
        case '3':
            init_supgomme(world,x,y,supgomme);
            supgomme ++;
            break;
      }
    }
  }
}
