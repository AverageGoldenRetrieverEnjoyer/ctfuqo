#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


struct utilisateur
{
	char nom[100];
	char motDePasse[100];
};

#define NOMBRE_UTILISATEURS 6
struct utilisateur utilisateurs[NOMBRE_UTILISATEURS] =
{
	{"Xavier", "Pet1tC4n1cheR05eOO3"},
	{"Laurent", "P01550nR0ugeInten51f835!!"},
	{"Laura", "G4merP0urL4V1e2O25&&"},
	{"Jeanne", "M0t_de_p455e256"},
	{"Vincent", "flag{dess455emb14ge_pr0gr4mme_C}"},
	{"Marie-Laurence", "JaimeTicTacToe28"}	
};


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
{
	if ((grille[0] == 'X' && grille[1] == 'X' && grille[2] == 'X') || (grille[3] == 'X' && grille[4] == 'X' && grille[5] == 'X') || (grille[6] == 'X' && grille[7] == 'X' && grille[8] == 'X') \
		|| (grille[0] == 'X' && grille[3] == 'X' && grille[6] == 'X') || (grille[1] == 'X' && grille[4] == 'X' && grille[7] == 'X') || (grille[2] == 'X' && grille[5] == 'X' && grille[8] == 'X') \
		|| (grille[0] == 'X' && grille[5] == 'X' && grille[8] == 'X') || (grille[2] == 'X' && grille[5] == 'X' && grille[6] == 'X'))
	{printf("\nVous avez gagné en %d tours!\n", nombreDeTours); return true;}
	return false;
}


bool verifierVictoireO (int nombreDeTours)
{
	if ((grille[0] == 'O' && grille[1] == 'O' && grille[2] == 'O') || (grille[3] == 'O' && grille[4] == 'O' && grille[5] == 'O') || (grille[6] == 'O' && grille[7] == 'O' && grille[8] == 'O') \
		|| (grille[0] == 'O' && grille[3] == 'O' && grille[6] == 'O') || (grille[1] == 'O' && grille[4] == 'O' && grille[7] == 'O') || (grille[2] == 'O' && grille[5] == 'O' && grille[8] == 'O') \
		|| (grille[0] == 'O' && grille[5] == 'O' && grille[8] == 'O') || (grille[2] == 'O' && grille[5] == 'O' && grille[6] == 'O'))
	{printf("\nVous avez perdu en %d tours.\n", nombreDeTours); return true;}
	return false;
}


void afficherGrille (int tour)
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


int main (int argc, char* argv[])
{
	struct utilisateur joueur = {"", ""};
	bool connecte = false;
	char input[10];
	int caseChoisie;
	
	
	srand(time(NULL));
	printf("Bienvenue dans ce jeu de Tic-Tac-Toe!\nEntrez votre nom d'utilisateur et votre mot de passe pour continuer.\n\n");
	
	while (!connecte)
	{	
		printf("Nom d'utilisateur: ");
		fgets(joueur.nom, sizeof(joueur.nom), stdin);
		joueur.nom[strlen(joueur.nom) - 1] = '\0';
		
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
	
	printf("\nConnexion réussie!\n\n");
	printf("Entrez le numero de la case pour y placer votre pion.\nVous jouez les X et l'ordinateur joue les O.\nVoici à quelles cases correspondent les numéros:\n");
	printf("\n");
	afficherGrille(-1);
	printf("\n");
	
	for (int i = 1; i < 10 && !verifierVictoireX(i - 1) && !verifierVictoireO(i - 1); i++)
	{
		//Tour du joueur:
		do
		{
			printf("\nEntrez le numéro de la case où vous voulez placer votre pion: ");
			fgets(input, sizeof(input), stdin);
			if (input[0] >= '1' && input[0] <= '9' && grille[input[0] - '1'] == ' ')
			{caseChoisie = input[0] - '1';}
			else
			{printf("Numéro de case invalide.\n"); caseChoisie = -1;}
		} while (caseChoisie == -1);
		
		grille[caseChoisie] = 'X';
		
		//Tour de l'ordi:
		do
		{caseChoisie = random() % 10;} while (grille[caseChoisie] != ' ');
		grille[caseChoisie] = 'O';
		
		afficherGrille(i);
	}
	
	return 0;
}