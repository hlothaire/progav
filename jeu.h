/**
 * \file jeu.h
 * \author Lothaire Holcvart
 * \brief Gestion du jeu, pacman et des fantomes
 */
#include <SDL2/SDL.h>


/**
* \brief Structure de pacman = composee de:
* \param PosX represente une Postion X
* \param PosY represente une Postion Y
* \param NbVie represente le nombre de vie
* \param is_visible represente son statue visible ou non
* \param ori represente son orientation
*/
typedef struct pacman {
	int PosX;
	int PosY;
	int NbVie;
	int is_visible;
	int ori;
} pacman_t;

/**
* \brief Structure de fantome = composee de:
* \param PosX represente une Postion X
* \param PosY represente une Postion Y
* \param Difficulte represente sa Difficulte:
* \param is_visible represente son statue visible ou non
* 1 = deplacement difficile / 4 = deplacement facile
*/
typedef struct fantome {
	int PosX;
	int PosY;
	int Difficulte;
   	int is_visible;
} fantome_t;

/**
* \brief Structure d un sprite = composee de:
* \param PosX represente une Postion X
* \param PosY represente une Postion Y
* \param id represente son id
* \param is_visible represente son statue visible ou non
*/
typedef struct sprite {
	int x;
	int y;
	int id;
	int is_visible;
} sprite_t;


/**
* \brief Structure d un monde world = composee de:
* \param joueur represente un joueur de type pacman_t
* \param fantome1 represente le fantome 1 du monde
* \param fantome2 represente le fantome 2 du monde
* \param fantome3 represente le fantome 3 du monde
* \param fantome4 represente le fantome 4 du monde
* \param **mur un tableau de sprite pour les murs
* \param **gomme tableau de sprite pour les gommes
* \param gameover booleen de fin de jeu
* \param score score du joueur
* \param nb_mur nombre de mur
* \param nb_gomme nombre de gomme
*/
typedef struct world{
	pacman_t *joueur;
  fantome_t *fantome1;
  fantome_t *fantome2;
  fantome_t *fantome3;
  fantome_t *fantome4;
	sprite_t **mur;
	sprite_t **gomme;
	sprite_t **supgomme;
	int gameover;
	int score;
	int nb_mur;
	int nb_supgomme;
	int nb_gomme;
} world_t;

/**
* \brief Fonction d'initialisation
 * Initialise le joueur (structure pacman_t) aux coordonnes indiquees
 * \param pacman joueur
 * \param PosX position X du joueur
 * \param PosY position Y du joueur
 */
void init_pacman(pacman_t* pacman,int PosX, int PosY);

/**
* \brief Fonction d'initialisation
 * Initialise le fantome  aux coordonnes indiquees avec la difficulte demandee
 * \param fantome fantome
 * \param PosX position X du fantome
 * \param PosY position Y du fantome
 * \param Difficulte Difficulte du fantome
 */
void init_fantome(fantome_t* fantome, int PosX, int PosY, int Difficulte);

/**
* \brief Fonction d'initialisation
 * Initialise un sprite avec ses coordonnes x et y ainsi que son id
 * \param sprite sprite
 * \param x Position X du sprite
 * \param y Position Y du sprite
 * \param id ID du sprite
 */
void init_sprite(sprite_t* sprite,int x,int y,int id);

/**
* \brief Fonction d'initialisation
 * Initialise les donnees d un monde
 * \param world Monde a initialiser
 */
void init_data(world_t* world);

/**
* \brief Fonction de liberation
 * Libere l espace memoire alloue au monde
 * \param world Monde a liberer
 */
void clean_data(world_t* world);

/**
* \brief Fonction de gestion
 * Modifie la visibilite d un sprite
 * \param sprite Sprite a modifier
 */
void set_visible(sprite_t* sprite);

/**
* \brief Fonction de gestion
 * Modifie la visibilite d un sprite
 * \param sprite Sprite a modifier
 */
void set_invisible(sprite_t* sprite);

/**
* \brief Fonction de gestion
 * Modifie la visibilite de tout les sprites
 * \param sprite Sprite a modifier
 */
void set_all_invisible(world_t* world);

/**
* \brief Fonction de gestion
 * Gère le game over
 * \param world Monde a modifier
 * \return 0 si la partie n est pas terminee, 1 sinon
 */
int is_game_over(world_t *world);

/**
* \brief Fonction de gestion
 * Gère les evenements
 * \param event Evenements a gerer
 * \param wolrd Monde a modifier
 */
void handle_events(SDL_Event *event,world_t *world);

/**
* \brief Fonction d'initialisation
 * Initialise les murs du monde aux coordonnes indiquees
 * \param world Monde a modifier
 * \param x Position X du mur
 * \param y Position Y du mur
 * \param index ID du mur
 */
void init_mur(world_t *world,int x,int y, int index);

/**
* \brief Fonction d'initialisation
 * Initialise les gommes du monde aux coordonnes indiquees
 * \param x Position X de la gomme
 * \param y Position Y de la gomme
 * \param index ID de la gomme
 */
void init_gomme(world_t *world,int x,int y, int index);

/**
* \brief Fonction d'initialisation
 * Initialise les super gommes du monde aux coordonnes indiquees
 * \param x Position X de la gomme
 * \param y Position Y de la gomme
 * \param index ID de la gomme
 */
void init_supgomme(world_t *world,int x,int y, int index);

/**
* \brief Fonction de gestion
 * Gère les collisions avec les sprites
 * \param x Position X du sprite
 * \param y Position Y du sprite
 * \param sprite Sprite a modifier
 * \return Renvoie 1 en cas de collision
 */
int collision(int x, int y,sprite_t *sprite);

/**
 * \brief Fonction de gestion: Gère les collisions avec les murs
 * \param x Position X du mur
 * \param y Position Y du mur
 * \param world Monde a modifier
 * \return Renvoie 1 en cas de collision
 */
int collision_wall(int x,int y,world_t *world);

/**
 * \brief Fonction de gestion: Gère les collisions avec les gommes
 * \param x Position X de la gomme
 * \param y Position Y de la gomme
 * \param world Monde a modifier
 */
void collision_gomme(world_t *world);

/**
 * \brief Fonction de gestion: Gère les collisions avec les supgommes
 * \param world Monde a modifier
 */
void collision_supgomme(world_t *world);

/**
* \brief Fonction de gestion
 * Gère les collisions avec un fantome
 * \param world Monde auxquelle appartient le fantome
 * \param fantome Fantome a regarder
 * \return Renvoie 1 en cas de collision
 */
int collision_fantome(world_t *world, fantome_t *fantome);

/**
* \brief Fonction de gestion
 * Gère les collisions avec tout les fantomes du monde
 * En cas de collision, le joueur perd une vie, des points sur son score et les position sont reinitialisees
 * \param world Monde a modifier/regarder
 * \return Renvoie 1 en cas de collision
 */
int collision_fantomes(world_t *world);

/**
* \brief Fonction de gestion
 * Met a jour les donnes du monde
 * \param world Monde a modifier
 */
void update_data(world_t *world);

/**
* \brief Fonction de gestion
 * Gère les deplacements de tout les fantomes du monde
 * \param world Monde a modifier
 */
void move_fantomes(world_t *world);

/**
* \brief Fonction de gestion
 * Gère les deplacements d un fantome
 * \param world Monde a modifier
 * \param fantome Fantome a regarder
 */
void move_fantome1(world_t *world, fantome_t *fantome);

/**
* \brief Fonction de gestion
 * Gère les deplacements d un fantome
 * \param world Monde a modifier
 * \param fantome Fantome a regarder
 */
void move_fantome2(world_t *world, fantome_t *fantome);

/**
* \brief Fonction de gestion
 * Gère les deplacements d un fantome
 * \param world Monde a modifier
 * \param fantome Fantome a regarder
 */
void move_fantome3(world_t *world, fantome_t *fantome);

