#include <stdio.h>
#include <string.h>
#include <stdbool.h>


bool finDuJeu = false;


struct joueur {
    char pseudo[50];
    int score;
    int coeurs;
};


void modifStruct(struct joueur *joueur, int score, int coeurs);
void gagne(struct joueur *joueur);
void perdu(struct joueur *joueur);
void afficherStatut(struct joueur *joueur);
int entrerChoixDeux(int premierChoix, int deuxiemeChoix);
int entrerChoixTrois(int premierChoix, int deuxiemeChoix, int troisiemeChoix);
void sauverPrincesse(struct joueur *joueur);
void scenarioDonjon(struct joueur *joueur);
void scenarioVallee(struct joueur *joueur);
void depart(struct joueur *joueur);




void modifStruct(struct joueur *joueur, int score, int coeurs) {
    joueur->score = joueur->score + score;
    joueur->coeurs = joueur->coeurs + coeurs;
}


void gagne(struct joueur *joueur) {
    modifStruct(joueur, 10, 0);
    printf("Vous avez gagne !\n");
    finDuJeu = true;
}


void perdu(struct joueur *joueur) {
    modifStruct(joueur, -10, -1);
    printf("Vous avez perdu ! Il vous reste %d coeur(s) \n", joueur->coeurs);
    finDuJeu = false;
}


void sauverPrincesse(struct joueur *joueur) {
    modifStruct(joueur, 20, 0);
    printf("Vous avez sauve la princesse !\n");
    finDuJeu = true;
}


void afficherStatut(struct joueur *joueur) {
    printf("Pseudo : %s\n" , joueur->pseudo);
    printf("Score : %d \n" , joueur->score);
    printf("Coeurs : %d\n" , joueur->coeurs);
}




void afficherChoixDonjon(char *tableau[3][4], int n) {
    if (n == 1) {
        printf("Vous etes rentre dans le donjon, mais attention, des gardes vous attendent ! \n");
        printf("1. %s\n", tableau[0][0]); /* Esquiver les gardes*/
        printf("2. %s\n", tableau[0][1]); /* Affronter les gardes */
        printf("3. %s\n", tableau[0][2]); /* Se renoncer */
    } if (n == 2) {
        printf("Vous avez reussi à esquiver les gardes, vous pouvez continuer votre chemin !\n");
        printf("4. %s\n", tableau[1][0]); /* 4 : Ouvrir la porte mystérieuse */
        printf("5. %s\n", tableau[1][2]); /* 5 : Fouiller le donjon */
    } else if (n == 3) {
        printf("Vous avez decide de fouiller le donjon, vous avez trouve un coffre !\n");
        printf("6. %s\n", tableau[2][0]); /* 6 : Coffre avec des motifs de tête de mort */
        printf("7. %s\n", tableau[2][1]); /* 7 : Coffre orné de pierres précieuses */
    } else if (n == 4) {
        printf("Vous avez decide d'affronter les gardes, vous etes courageux, mais ils ont appele des renforts !\n");
        printf("8. %s\n", tableau[1][1]); /* 8 : Affronter les renforts */
        printf("9. %s\n", tableau[1][3]); /* 9 : Fuir */
    }
}


void scenarioDonjon(struct joueur *joueur) {
    int choixInitialDonjon;
    int choixActuelDonjon;




    char *choixDonjon[3][4] = {
        {"Esquiver les gardes", "Affronter les gardes", "Se renoncer", ""},
        {"Ouvrir la porte mysterieuse", "Les affronter quand même", "Fouiller le donjon", "Fuir"},
        {"Coffre avec des motifs de tete de mort", "Coffre orne de pierres precieuses", "", ""}
    };

    afficherChoixDonjon(choixDonjon, 1);
    choixInitialDonjon = entrerChoixTrois(1, 2, 3);


    if (choixInitialDonjon == 1) {
        afficherChoixDonjon(choixDonjon, 2);
        choixActuelDonjon = entrerChoixDeux(4, 5);
        modifStruct(joueur, 5, 0);


        if (choixActuelDonjon == 5) {
            afficherChoixDonjon(choixDonjon, 3);
            choixActuelDonjon = entrerChoixDeux(6, 7);
            modifStruct(joueur, 5, 0);

            if (choixActuelDonjon == 6) {
                sauverPrincesse(joueur);
                afficherStatut(joueur);
            } else {
                perdu(joueur);
                afficherStatut(joueur);
        }
        } else if (choixActuelDonjon == 4) {
                perdu(joueur);
                afficherStatut(joueur);


        }
    } else if (choixInitialDonjon == 2) {
        afficherChoixDonjon(choixDonjon, 4);
        choixActuelDonjon = entrerChoixDeux(8, 9);


        if (choixActuelDonjon == 8) {
            perdu(joueur);
            afficherStatut(joueur);
        } else if (choixActuelDonjon == 9) {
            modifStruct(joueur, 5, 0);
            afficherStatut(joueur);
            printf("Vous vous enfuyez vers la vallee !\n");
            scenarioVallee(joueur);
        }
    } else if (choixInitialDonjon == 3) {
        modifStruct(joueur, 2 , 0);
        printf("Vous quittez le donjon et partez vers la vallee.\n");
        scenarioVallee(joueur);
    }
}


/* Fonction qui affiche les choix auxquels est confronté le joueur (Spécial Donjon) */
void afficherChoixVallee(char *tableau[2][4], int n) {
    if (n == 1) {
        printf("Vous vous etes aventure dans la vallee. Trois choix s'offrent à vous !\n");
        printf("1. %s\n", tableau[0][0]);
        printf("2. %s\n", tableau[0][1]);
        printf("3. %s\n", tableau[0][2]);
    }
    if (n == 2) {
        printf("Vous avez choisi de vous diriger dans la grotte. Vous tombez nez a nez avec un dragon.\n");
        printf("4. %s\n", tableau[1][0]); // 4 : Affronter le dragon
        printf("5. %s\n", tableau[1][1]); // 5 : Sortir de la grotte (retour au choix de départ)
    } else if (n == 3) {
        printf("Vous avez choisi de vous diriger vers la riviere enchantee. Deux choix s'offrent a vous :\n");
        printf("6. %s\n", tableau[1][2]); // 6 : Boire l'eau
        printf("7. %s\n", tableau[1][3]); // 7 : Se baigner
    }
}


void scenarioVallee(struct joueur *joueur) {
    int choixInitialVallee;
    int choixActuelVallee;


    char *choixVallee[2][4] = {
        {"Se diriger vers la grotte", "Se diriger vers la riviere enchantee", "Parler au mage", ""},
        {"Sortir de la grotte", "Affronter le dragon", "Boire l'eau de la riviere", "Se baigner dans la riviere"}
    };

    afficherChoixVallee(choixVallee, 1);
    choixInitialVallee = entrerChoixTrois(1, 2, 3);
    if (choixInitialVallee == 1) {
        afficherChoixVallee(choixVallee, 2);
        choixActuelVallee = entrerChoixDeux(4, 5);
        modifStruct(joueur, 5, 0);


        if (choixActuelVallee == 4) {
            depart(joueur);
        } else if (choixActuelVallee == 5) {
            sauverPrincesse(joueur);
            afficherStatut(joueur);
        }
    } else if (choixInitialVallee == 2) {
        afficherChoixVallee(choixVallee, 3);
        choixActuelVallee = entrerChoixDeux(6, 7);


        if (choixActuelVallee == 6) {
            perdu(joueur);
            afficherStatut(joueur);
        }
        if (choixActuelVallee == 7) {
            // Téléportation au mage (à définir)
        }
    } else if (choixInitialVallee == 3) {
        modifStruct(joueur, 2, 0);
        printf("Vous quittez la vallee et vous vous dirigez vers le mage.\n");
    }
}


int entrerChoixDeux(int premierChoix, int deuxiemeChoix) {
    int choix;
    printf("Entrez votre choix: ");
    scanf("%d", &choix);

    if (choix == premierChoix || choix == deuxiemeChoix) {
        return choix;


    } else {
        while (choix != premierChoix && choix != deuxiemeChoix) {
            printf("Choix invalide, veuillez entrer un choix valide: ");
            scanf("%d", &choix);
        }
    }
    return choix;
}


int entrerChoixTrois(int premierChoix, int deuxiemeChoix, int troisiemeChoix) {
    int choix;
    printf("Entrez votre choix: ");
    scanf("%d", &choix);

    if (choix == premierChoix || choix == deuxiemeChoix) {
        return choix;


    } else {
        while (choix != premierChoix && choix != deuxiemeChoix && choix != troisiemeChoix) {
            printf("Choix invalide, veuillez entrer un choix valide: ");
            scanf("%d", &choix);
        }
    }
    return choix;
}




void depart(struct joueur *joueur) {
    int choixInitial;


    printf("Vous etes au choix de depart\n");
    printf("1. Entrer dans le donjon\n");
    printf("2. S'aventurer dans la vallee\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choixInitial);


    if (choixInitial == 1) {
        scenarioDonjon(joueur);
    } else if (choixInitial == 2)
    {
    scenarioVallee(joueur);
        } else {
            printf("Choix invalide, veuillez reessayer\n");
            depart(joueur);
        }
    }


int main() {
    struct joueur joueur;
    joueur.score = 20;
    joueur.coeurs = 3;


    printf("Entrez votre pseudo: ");
    scanf("%s", joueur.pseudo);


    afficherStatut(&joueur);


    while (joueur.coeurs > 0 && finDuJeu == false) {
        depart(&joueur);
    }

    if (joueur.coeurs == 0 ) {
        printf("Vous avez perdu, le jeu est termine !\n");
    } else if (finDuJeu == true) {
        printf("Le jeu est termine!\n");
    }
    return 0;
}



