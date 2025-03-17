/* Tous les includes, pour utiliser les strings notamment */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Variable pour déterminer si le joueur a fini le jeu ou non */
bool finDuJeu = false;

/* Structure joueur */

struct joueur {
    char pseudo[50];
    int score;
    int coeurs;
};

typedef struct
{
    int pos;
} Game;

/* Prototype des fonctions */

void modifStruct(struct joueur *joueur, int score, int coeurs);
void gagne(struct joueur *joueur);
void perdu(struct joueur *joueur);
void afficherStatut(struct joueur *joueur);
int entrerChoix(int min, int max);
void sauverPrincesse(struct joueur *joueur);
void scenarioDonjon(Game *jeu, struct joueur *joueur);
void scenarioVallee(Game *jeu, struct joueur *joueur);
void scenarioMage(Game *jeu, struct joueur *joueur);
void depart(Game *jeu, struct joueur *joueur);


/* Toutes les fonctions qui vont agir sur la structure joueur */

/* Fonction pour ajouter, enlever du score ou des coeurs */

void modifStruct(struct joueur *joueur, int score, int coeurs) {
    joueur->score = joueur->score + score;
    joueur->coeurs = joueur->coeurs + coeurs;
}

/* Fonction si le joueur gagne */

void gagne(struct joueur *joueur) {
    modifStruct(joueur, 10, 0);
    printf("\nVous avez gagne !\n\n");
    finDuJeu = true;
}

/* Fonction si le joueur perd */

void perdu(struct joueur *joueur) {
    modifStruct(joueur, -10, -1);
    printf("\nVous avez perdu ! Il vous reste %d coeurs(s).\n\n", joueur->coeurs);
    finDuJeu = false;
}

/* Fonction si le joueur sauve la princesse */

void sauverPrincesse(struct joueur *joueur) {
    modifStruct(joueur, 20, 0);
    printf("\nVous avez sauve la princesse !\n\n");
    finDuJeu = true;
}

/* Fonction pour afficher les infos du joueur */

void afficherStatut(struct joueur *joueur) {
    printf("\n--- Vos informations ---\n");
    printf("Pseudo : %s\n", joueur->pseudo);
    printf("Score : %d\n", joueur->score);
    printf("Coeurs : %d\n", joueur->coeurs);
    printf("------------------------\n\n");
}

/* PARTIE DONJON */

/* Fonction utilisé pour afficher les choix de cette partie */

void afficherChoixDonjon(char *tableau[3][4], int n) {
    if (n == 1) {
        printf("Vous etes rentre dans le donjon, mais attention, des gardes vous attendent !\n");
        printf("--------------------------------------------------\n");
        printf("1. %s\n", tableau[0][0]); /* Esquiver les gardes*/
        printf("2. %s\n", tableau[0][1]); /* Affronter les gardes */
        printf("3. %s\n", tableau[0][2]); /* Se renoncer */
        printf("--------------------------------------------------\n");
    } else if (n == 2) {
        printf("Vous avez reussi à esquiver les gardes, vous pouvez continuer votre chemin !\n");
        printf("--------------------------------------------------\n");
        printf("4. %s\n", tableau[1][0]); /* 4 : Ouvrir la porte mystérieuse */
        printf("5. %s\n", tableau[1][2]); /* 5 : Fouiller le donjon */
        printf("--------------------------------------------------\n");
    } else if (n == 3) {
        printf("Vous avez decide de fouiller le donjon, vous avez trouve un coffre !\n");
        printf("--------------------------------------------------\n");
        printf("6. %s\n", tableau[2][0]); /* 6 : Coffre avec des motifs de tête de mort */
        printf("7. %s\n", tableau[2][1]); /* 7 : Coffre orné de pierres précieuses */
        printf("--------------------------------------------------\n");
    } else if (n == 4) {
        printf("Vous avez decide d'affronter les gardes, vous etes courageux, mais ils ont appele des renforts !\n");
        printf("--------------------------------------------------\n");
        printf("8. %s\n", tableau[1][1]); /* 8 : Affronter les renforts */
        printf("9. %s\n", tableau[1][3]); /* 9 : Fuir */
        printf("--------------------------------------------------\n");
    }
}


/* Fonction qui execute le scenario */

void scenarioDonjon(Game *jeu, struct joueur *joueur) {
    int choixInitialDonjon;
    int choixActuelDonjon;

    /* Tableau contenant les choix */
    char *choixDonjon[3][4] = {
        {"Esquiver les gardes", "Affronter les gardes", "Se renoncer", ""},
        {"Ouvrir la porte mysterieuse", "Les affronter quand même", "Fouiller le donjon", "Fuir"},
        {"Coffre avec des motifs de tete de mort", "Coffre orne de pierres precieuses", "", ""}
    };

    afficherChoixDonjon(choixDonjon, 1);
    choixInitialDonjon = getChoix(1, 2, 3, 0);

    jeu->pos = 3;

    if (choixInitialDonjon == 1) {
        afficherChoixDonjon(choixDonjon, 2);
        choixActuelDonjon = getChoix(4, 5, 0, 0);
        modifStruct(joueur, 5, 0);
        jeu->pos = 4;

        if (choixActuelDonjon == 5) {
            afficherChoixDonjon(choixDonjon, 3);
            choixActuelDonjon = getChoix(6, 7, 0, 0);
            modifStruct(joueur, 5, 0);
            jeu->pos = 5;

            if (choixActuelDonjon == 6) {
                printf("Vous avez ouvert le coffre et avez trouve a l'interieur un tresor !\n");
                gagne(joueur);
                afficherStatut(joueur);
            } else if (choixActuelDonjon == 7) {
                printf("C'etait un piege..\n");
                perdu(joueur);
                afficherStatut(joueur);
            }
        } else if (choixActuelDonjon == 4) {
            printf("Derriere cette porte se cachait un terrible monstre qui vous a tue...\n");
            perdu(joueur);
            afficherStatut(joueur);
        }
    } else if (choixInitialDonjon == 2) {
        afficherChoixDonjon(choixDonjon, 4);
        choixActuelDonjon = getChoix(8, 9, 0, 0);
        jeu->pos = 6;

        if (choixActuelDonjon == 8) {
            perdu(joueur);
            afficherStatut(joueur);
        } else if (choixActuelDonjon == 9) {
            modifStruct(joueur, 5, 0);
            afficherStatut(joueur);
            printf("Vous vous enfuyez vers la vallee !\n");
            scenarioVallee(jeu, joueur);
        }
    } else if (choixInitialDonjon == 3) {
        modifStruct(joueur, 2 , 0);
        printf("Vous vous etes renonce, vous quittez le donjon et partez vers la vallee.\n");
        scenarioVallee(jeu, joueur);
        jeu->pos = 7;
    }
}

/* PARTIE VALLEE */

void afficherChoixVallee(char *tableau[2][4], int n) {
    printf("--------------------------------------------------\n");
    if (n == 1) {
        printf("Vous vous etes aventure dans la vallee. Trois choix s'offrent a vous !\n");
        printf("1. %s\n", tableau[0][0]);
        printf("2. %s\n", tableau[0][1]);
        printf("3. %s\n", tableau[0][2]);
    } else if (n == 2) {
        printf("Vous avez choisi de vous diriger dans la grotte. Vous tombez nez a nez avec un dragon.\n");
        printf("4. %s\n", tableau[1][0]); // 4 : Sortir de la grotte
        printf("5. %s\n", tableau[1][1]); // 5 : Affronter le dragon
    } else if (n == 3) {
        printf("Vous avez choisi de vous diriger vers la riviere enchantee. Deux choix s'offrent a vous :\n");
        printf("6. %s\n", tableau[1][2]); // 6 : Boire l'eau
        printf("7. %s\n", tableau[1][3]); // 7 : Se baigner
    }
    printf("--------------------------------------------------\n");
}



void scenarioVallee(Game *jeu, struct joueur *joueur) {
    int choixInitialVallee;
    int choixActuelVallee;

    char *choixVallee[2][4] = {
        {"Se diriger vers la grotte", "Se diriger vers la riviere enchantee", "Parler au mage", ""},
        {"Sortir de la grotte", "Affronter le dragon", "Boire l'eau de la riviere", "Se baigner dans la riviere"}
    };

    afficherChoixVallee(choixVallee, 1);
    choixInitialVallee = getChoix(1, 2, 3, 0);
    jeu->pos = 8;

    if (choixInitialVallee == 1) {
        afficherChoixVallee(choixVallee, 2);
        choixActuelVallee = getChoix(4, 5, 0, 0);
        modifStruct(joueur, 5, 0);
        jeu->pos = 9;

        if (choixActuelVallee == 4) {
            printf("Vous avez decide de sortir de la grotte , vous etes donc retourner au choix de depart \n");
            depart(jeu, joueur);
        } else if (choixActuelVallee == 5) {
            printf("Vous avez affronte le dragon qui emprisonnait la princesse, vous l'avez vaincu !\n");
            sauverPrincesse(joueur);
            afficherStatut(joueur);
        }
    } else if (choixInitialVallee == 2) {
        afficherChoixVallee(choixVallee, 3);
        choixActuelVallee = getChoix(6, 7, 0, 0);
        jeu->pos = 10;

        if (choixActuelVallee == 6) {
            printf("Vous avez bu l'eau mais elle est empoisonne..\n");
            perdu(joueur);
            afficherStatut(joueur);
        }
        if (choixActuelVallee == 7) {
            scenarioMage(jeu, joueur);
        }
    } else if (choixInitialVallee == 3) {
        modifStruct(joueur, 2, 0);
        printf("Vous quittez la vallee et vous vous dirigez vers le mage.\n");
        scenarioMage(jeu, joueur);
        jeu->pos = 11;
    }
}

void affichageMage(char *txt) {
    printf("%s\n", txt);
}

void scenarioMage(Game *jeu, struct joueur *joueur) {
    affichageMage("* Vous allez parler au mage *");
    affichageMage("'Bonjour jeune aventurier !\n''Je suis le mage Ozar et j'ai une proposition a te faire. Je peux : \n");
    affichageMage("'1. Te teleporter au donjon'\n'2. Te teleporter aleatoirement sur la carte'\n* 3. Continuer votre route *\n * 4. Essayer de lui voler sa baguette *");
    int choixMage = getChoix(1, 2, 3, 4);
    switch (choixMage)
    {
        case 1:
        jeu->pos = 1;
        affichageMage("* Vous avez ete teleporte au donjon *");
        scenarioDonjon(jeu, joueur);
        break;
        case 2:
        srand(time(NULL));
        int rng = rand() % 28;
        jeu->pos = rng;
        affichageMage("* Vous avez ete teleporte à un endroit aléatoire *");
        break;
        case 3:
        jeu->pos = 2;
        affichageMage("* Vous continuez votre route dans la vallee *");
        scenarioVallee(jeu, joueur);
        break;
        case 4:
        jeu->pos = 0;
        affichageMage("* Vous essayez de lui voler sa baguette *\n* Vous ratez... *\n'Tu ne merite pas mon aide !!'\n* Le mage vous as teleporte au depart *");
        depart(jeu, joueur);
    }
}
/* Gestion des entrées utilisateurs */

int getChoix(int premierChoix, int deuxiemeChoix, int troisiemeChoix, int quatriemeChoix) {
    int choix;
    printf("Entrez votre choix: ");
    scanf("%d", &choix);

    if (choix == premierChoix || choix == deuxiemeChoix || choix == troisiemeChoix || choix == quatriemeChoix) {
        return choix;

    /* Gestion des erreurs, si le joueur écrit un choix invalide ou autre chose qu'un nombre */

    } else {
        while (choix != premierChoix && choix != deuxiemeChoix && choix!= troisiemeChoix && choix != quatriemeChoix) {
            printf("Choix invalide, veuillez entrer un choix valide: ");
            scanf("%d", &choix);
        }
    }
    return choix;
}
/* Fonction qui correspond au choix de départ */

void depart(Game *jeu, struct joueur *joueur) {
    int choixInitial;


    printf("\nVous etes au choix de depart\n\n");
    printf("1. Entrer dans le donjon\n");
    printf("2. S'aventurer dans la vallee\n");
    printf("\nEntrez votre choix: ");
    scanf("%d", &choixInitial);
    jeu->pos = 12;

    if (choixInitial == 1) {
        scenarioDonjon(jeu, joueur);
    } else if (choixInitial == 2)
    {
    scenarioVallee(jeu, joueur);
        } else {
            printf("\nChoix invalide, veuillez reessayer\n\n");
            depart(jeu, joueur);
        }
    }

/* Fonction main qui execute le programme */

int main() {
    struct joueur joueur;
    joueur.score = 20;
    joueur.coeurs = 3;
    Game jeu = {0};


    printf("\nEntrez votre pseudo: ");
    scanf("%s", joueur.pseudo);


    afficherStatut(&joueur);


    while (joueur.coeurs > 0 && finDuJeu == false) {
        depart(&jeu, &joueur);
    }

    if (joueur.coeurs == 0 ) {
        printf("\nVous avez perdu, le jeu est termine !\n\n");
    } else if (finDuJeu == true) {
        printf("\nLe jeu est termine !\n\n");
    }
    return 0;
}



