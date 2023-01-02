/**
 * \file niveau.h
 * \author Lothaire Holcvart
 * \brief bibliotheque gestion niveau
 */
#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jeu.h"

/**
 * \brief allocation memoire d'un tableau 2D
 * \param n nombre de ligne
 * \param m nombre de collone
*/
char** allouer_tab_2D(int n, int m);


/**
 * \brief fonction qui libere un tableau 2D
 * \param tab tableau
 * \param n nombre de ligne
*/
void desallouer_tab_2D(char** tab, int n);

/**
 * \brief lecture d'un fichier text et copie des caractéres dans un tableau 2D
 * \param nomFichier nom du fichier
 * \return tab  tableau 2D
*/
char** lire_fichier(const char* nomFichier);

void nb_element(char** tab,world_t *world);

/**
 * \brief fonction qui gere l'affichage du niveau en fonction du tableau
 * \param tab tableau
 * \param bloc
 * \param vide
 * \param gomme
 * \param renderer
*/
void create_level(char** tab,world_t *world);
