#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// --- Début de la 1ère partie importante pour le CTF ---

struct utilisateur
{
	char nom[100];
	char motDePasse[100];
};

#define NOMBRE_UTILISATEURS 6
struct utilisateur utilisateurs[NOMBRE_UTILISATEURS] =
//Noms d'utilisateur et mots de passe des "comptes utilisateurs" du jeu.
//Je les mets en variable globale pour rendre la tâche un peu plus intéressante.
{
	{"Xavier", "Pet1tC4n1cheR05eOO3"},
	{"Laurent", "P01550nR0ugeInten51f835!!"},
	{"Laura", "G4merP0urL4V1e2O25&&"},
	{"Jeanne", "M0t_de_p455e256"},
	{"Vincent", "flag{dess455emb14ge_pr0gr4mme_C}"},
	{"</UCTF>", "UCTF2025"},
};

// --- Fin de la 1ère partie importante pour le CTF ---


//Grille de tic-tac-toe:
char grille[9] =
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
/* Disposition:
	0|1|2
	3|4|5
	6|7|8
	
	Valeurs possibles:
	' ', 'X', 'O'
*/



bool verifierVictoireX (int nombreDeTours)
//Vérifie si le joueur a gagné et affiche un message si oui.
//Les combinaisons de victoire sont hardcodées parce que ce n'est vraiment pas la partie importante du programme.
{
	if ((grille[0] == 'X' && grille[1] == 'X' && grille[2] == 'X') || (grille[3] == 'X' && grille[4] == 'X' && grille[5] == 'X') || (grille[6] == 'X' && grille[7] == 'X' && grille[8] == 'X') \
		|| (grille[0] == 'X' && grille[3] == 'X' && grille[6] == 'X') || (grille[1] == 'X' && grille[4] == 'X' && grille[7] == 'X') || (grille[2] == 'X' && grille[5] == 'X' && grille[8] == 'X') \
		|| (grille[0] == 'X' && grille[5] == 'X' && grille[8] == 'X') || (grille[2] == 'X' && grille[5] == 'X' && grille[6] == 'X'))
	{printf("\nVous avez gagné en %d tours!\n", nombreDeTours); return true;}
	return false;
}


bool verifierVictoireO (int nombreDeTours)
//Vérifie si le joueur a gagné et affiche un message si oui.
//Les combinaisons de victoire sont hardcodées parce que ce n'est vraiment pas la partie importante du programme.
{
	if ((grille[0] == 'O' && grille[1] == 'O' && grille[2] == 'O') || (grille[3] == 'O' && grille[4] == 'O' && grille[5] == 'O') || (grille[6] == 'O' && grille[7] == 'O' && grille[8] == 'O') \
		|| (grille[0] == 'O' && grille[3] == 'O' && grille[6] == 'O') || (grille[1] == 'O' && grille[4] == 'O' && grille[7] == 'O') || (grille[2] == 'O' && grille[5] == 'O' && grille[8] == 'O') \
		|| (grille[0] == 'O' && grille[5] == 'O' && grille[8] == 'O') || (grille[2] == 'O' && grille[5] == 'O' && grille[6] == 'O'))
	{printf("\nVous avez perdu en %d tours.\n", nombreDeTours); return true;}
	return false;
}


void afficherGrille (int tour)
//Affiche la grille de tic-tac-toe dans son état actuel.
//Reçoit le nombre de tours écoulés jusqu'à maintenant en argument.
//Si appelée avec -1 en argument, affiche la grille avec les numéros de case dans chaque case.
{
	if (tour > 0)
	{printf("Tour #%d:\n", tour);}
	
	if (tour == -1)
	{printf(" 1 | 2 | 3\n");}
	else
	{printf(" %c | %c | %c\n", grille[0], grille[1], grille[2]);}
	printf("___|___|___\n");
	printf("   |   |\n");
	if (tour == -1)
	{printf(" 4 | 5 | 6\n");}
	else
	{printf(" %c | %c | %c\n", grille[3], grille[4], grille[5]);}
	printf("___|___|___\n");
	printf("   |   |\n");
	if (tour == -1)
	{printf(" 7 | 8 | 9\n");}
	else
	{printf(" %c | %c | %c\n\n", grille[6], grille[7], grille[8]);}
}


// --- Début de la 2e partie importante pour le CTF ---

int main (int argc, char* argv[])
//Gère la connexion puis le jeu de tic-tac-toe.
//Honnêtement, seule la partie connexion est importante.
//Le programme se termine quand le joueur ou l'ordi gagne la partie ou lorsque l'utilisateur entre Ctrl-C.
{
	struct utilisateur joueur = {"", ""}; //les données entrées par l'utilisateur
	bool connecte = false; //indique si l'utilisateur a entré un nom d'utilisateur et un mot de passe valide
	char input[10]; //input clavier utilisé uniquement dans le jeu de tic-tac-toe
	int caseChoisie; //case choisie par le joueur ou l'ordi dans le jeu de tic-tac-toe
	
	
	srand(time(NULL)); //utilise l'heure acuelle comme seed pour le générateur de nombres aléatoire (pour le jeu de tic-tac-toe)
	printf("Bienvenue dans ce jeu de Tic-Tac-Toe!\nEntrez votre nom d'utilisateur et votre mot de passe pour continuer.\n\n");
	
	//Connexion:
	
	while (!connecte)
	{	
		printf("Nom d'utilisateur: ");
		fgets(joueur.nom, sizeof(joueur.nom), stdin); //fgets prend seulement sizeof(joueur.nom)-1 caractères d'input, ce qui bloque les attaques de type "buffer overflow"
		joueur.nom[strlen(joueur.nom) - 1] = '\0'; //fgets prend l'input en entier, incluant le '\n' final, que je dois donc enlever manuellement
		
		printf("Mot de passe: ");
		fgets(joueur.motDePasse, sizeof(joueur.motDePasse), stdin);
		joueur.motDePasse[strlen(joueur.motDePasse) - 1] = '\0';
		
		for (int i = 0; i < NOMBRE_UTILISATEURS && !connecte; i++)
		{
			if (!strcmp(joueur.nom, utilisateurs[i].nom) && !strcmp(joueur.motDePasse, utilisateurs[i].motDePasse))
			{connecte = true;}
		}
		
		if (!connecte)
		{printf("\nVous avez entré un nom d'utilisateur ou un mot de passe invalide.\nVeuillez réessayer.\n\n");}
	}
	
// --- Fin de la 2e partie importante pour le CTF ---
	
	printf("\nConnexion réussie!\n\n");
	printf("Entrez le numero de la case pour y placer votre pion.\nVous jouez les X et l'ordinateur joue les O.\nVoici à quelles cases correspondent les numéros:\n");
	printf("\n");
	afficherGrille(-1); //affiche les numéros des cases dans la grille
	printf("\n");
	
	
	//Jeu de tic-tac-toe:
	//(Tout le reste du programme est inutile pour le défi et sert seulement à rendre le programme un peu plus gros et réaliste.)
	//(On peut aussi voir ça comme un genre d'Easter Egg?)
	
	for (int i = 1; i < 10 && !verifierVictoireX(i - 1) && !verifierVictoireO(i - 1); i++)
	{
		//Tour du joueur (X):
		do
		{
			printf("\nEntrez le numéro de la case où vous voulez placer votre pion: ");
			fgets(input, sizeof(input), stdin);
			if (input[0] >= '1' && input[0] <= '9' && grille[input[0] - '1'] == ' ') //je me fiche de ce que le joueur entre après son 1er caractère (de toute façon, on se fout pas mal de cette partie du programme)
			{caseChoisie = input[0] - '1';}
			else
			{printf("Numéro de case invalide.\n"); caseChoisie = -1;} //input[0] n'est pas un chiffre de 1 à 9 ou la case est déjà occupée
		} while (caseChoisie == -1);
		
		grille[caseChoisie] = 'X';
		
		//Tour de l'ordi (O):
		do
		{caseChoisie = random() % 9;} while (grille[caseChoisie] != ' '); //génère un nombre de 0 à 8 et n'accepte pas les nombres correspondant à une case non vide
		grille[caseChoisie] = 'O';
		
		//Affichage:
		afficherGrille(i); //i est le numéro du tour
	}
	
	return 0;
}