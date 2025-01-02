#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour un client
typedef struct Client {
    int codecli;
    char prenom[50];
    char nom[50];
    char tel[15];
    char ville[50];
    struct Client *suivant;
} Client;

// Structure pour un compte bancaire
typedef struct Compte {
    int numero;
    char dateOuverture[20];
    char agence[50];
    float solde;
    int codecli;
    struct Compte *suivant;
} Compte;

// Structure pour une opération
typedef struct Operation {
    int code;
    int numeroCompte;
    char type[10];
    float montant;
    char dateOp[20];
    struct Operation *suivant;
} Operation;

// Fonctions pour les listes chaînées
Client *ajouterClient(Client *tete, int codecli, char *prenom, char *nom, char *tel, char *ville) {
    Client *nouveau = (Client *)malloc(sizeof(Client));
    if (!nouveau) {
        printf("Erreur d'allocation mémoire\n");
        return tete;
    }
    nouveau->codecli = codecli;
    strcpy(nouveau->prenom, prenom);
    strcpy(nouveau->nom, nom);
    strcpy(nouveau->tel, tel);
    strcpy(nouveau->ville, ville);
    nouveau->suivant = tete;
    return nouveau;
}

Compte *ajouterCompte(Compte *tete, int numero, char *dateOuverture, char *agence, float solde, int codecli) {
    Compte *nouveau = (Compte *)malloc(sizeof(Compte));
    if (!nouveau) {
        printf("Erreur d'allocation mémoire\n");
        return tete;
    }
    nouveau->numero = numero;
    strcpy(nouveau->dateOuverture, dateOuverture);
    strcpy(nouveau->agence, agence);
    nouveau->solde = solde;
    nouveau->codecli = codecli;
    nouveau->suivant = tete;
    return nouveau;
}

Operation *ajouterOperation(Operation *tete, int code, int numeroCompte, char *type, float montant, char *dateOp) {
    Operation *nouveau = (Operation *)malloc(sizeof(Operation));
    if (!nouveau) {
        printf("Erreur d'allocation mémoire\n");
        return tete;
    }
    nouveau->code = code;
    nouveau->numeroCompte = numeroCompte;
    strcpy(nouveau->type, type);
    nouveau->montant = montant;
    strcpy(nouveau->dateOp, dateOp);
    nouveau->suivant = tete;
    return nouveau;
}

// Fonctions pour enregistrer les données dans des fichiers
void sauvegarderClients(Client *clients) {
    FILE *fichier = fopen("clients.txt", "a");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier clients.txt\n");
        return;
    }
    Client *temp = clients;
    while (temp) {
        fprintf(fichier, "codecli: %d, prenom:\"%s\", nom: \"%s\" ,tel:\"%s\" ,ville: \"%s\"\n", temp->codecli, temp->prenom, temp->nom, temp->tel, temp->ville);
        temp = temp->suivant;
    }
    fclose(fichier);
}

void sauvegarderComptes(Compte *comptes) {
    FILE *fichier = fopen("comptes.txt", "a");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier comptes.txt\n");
        return;
    }
    Compte *temp = comptes;
    while (temp) {
        fprintf(fichier, "numero: %d, dateOuverture: \"%s\" ,agence:\"%s\" ,solde: %.2f, codecli: %d\n", temp->numero, temp->dateOuverture, temp->agence, temp->solde, temp->codecli);
        temp = temp->suivant;
    }
    fclose(fichier);
}

void sauvegarderOperations(Operation *operations) {
    FILE *fichier = fopen("operations.txt", "a");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier operations.txt\n");
        return;
    }
    Operation *temp = operations;
    while (temp) {
        fprintf(fichier, "code: %d ,numero Compte: %d, type: \"%s\", montant: %.2f, date operation: \"%s\"\n", temp->code, temp->numeroCompte, temp->type, temp->montant, temp->dateOp);
        temp = temp->suivant;
    }
    fclose(fichier);
}

// Fonctions pour libérer la mémoire
void libererClients(Client *clients) {
    Client *temp;
    while (clients) {
        temp = clients;
        clients = clients->suivant;
        free(temp);
    }
}

void libererComptes(Compte *comptes) {
    Compte *temp;
    while (comptes) {
        temp = comptes;
        comptes = comptes->suivant;
        free(temp);
    }
}

void libererOperations(Operation *operations) {
    Operation *temp;
    while (operations) {
        temp = operations;
        operations = operations->suivant;
        free(temp);
    }
}

// Fonction principale
int main() {
    Client *clients = NULL;
    Compte *comptes = NULL;
    Operation *operations = NULL;
    int choix;

    do {
        printf("\n=== Gestion des clients d'une banque ===\n");
        printf("1. Ajouter un client\n");
        printf("2. Ajouter un compte\n");
        printf("3. Effectuer une operation\n");
        printf("4. Sauvegarder les donnees\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {
            printf("Entree invalide. Veuillez reessayer.\n");
            while (getchar() != '\n'); // Vider le buffer
            continue;
        }

        while (getchar() != '\n'); // Nettoyer le buffer

        if (choix == 1) {
            int codecli;
            char prenom[50], nom[50], tel[15], ville[50];

            printf("Code client : ");
            scanf("%d", &codecli);
            while (getchar() != '\n');

            printf("Prenom : ");
            fgets(prenom, sizeof(prenom), stdin);
            prenom[strcspn(prenom, "\n")] = '\0';

            printf("Nom : ");
            fgets(nom, sizeof(nom), stdin);
            nom[strcspn(nom, "\n")] = '\0';

            printf("Telephone : ");
            fgets(tel, sizeof(tel), stdin);
            tel[strcspn(tel, "\n")] = '\0';

            printf("Ville : ");
            fgets(ville, sizeof(ville), stdin);
            ville[strcspn(ville, "\n")] = '\0';

            clients = ajouterClient(clients, codecli, prenom, nom, tel, ville);
            printf("Client ajoute avec succes !\n");
        } else if (choix == 2) {
            int numero, codecli;
            char dateOuverture[20], agence[50];
            float solde;

            printf("Numero de compte : ");
            scanf("%d", &numero);
            while (getchar() != '\n');

            printf("Date d'ouverture (jj/mm/aaaa) : ");
            fgets(dateOuverture, sizeof(dateOuverture), stdin);
            dateOuverture[strcspn(dateOuverture, "\n")] = '\0';

            printf("Agence : ");
            fgets(agence, sizeof(agence), stdin);
            agence[strcspn(agence, "\n")] = '\0';

            printf("Solde initial : ");
            scanf("%f", &solde);
            while (getchar() != '\n');

            printf("Code client associe : ");
            scanf("%d", &codecli);
            while (getchar() != '\n');

            comptes = ajouterCompte(comptes, numero, dateOuverture, agence, solde, codecli);
            printf("Compte ajoute avec succes !\n");
        } else if (choix == 3) {
            int code, numeroCompte;
            char type[10], dateOp[20];
            float montant;

            printf("Code operation : ");
            scanf("%d", &code);
            while (getchar() != '\n');

            printf("Numero de compte : ");
            scanf("%d", &numeroCompte);
            while (getchar() != '\n');

            printf("Type d'operation (depôt/retrait) : ");
            fgets(type, sizeof(type), stdin);
            type[strcspn(type, "\n")] = '\0';

            printf("Montant : ");
            scanf("%f", &montant);
            while (getchar() != '\n');

            printf("Date de l'operation (jj/mm/aaaa) : ");
            fgets(dateOp, sizeof(dateOp), stdin);
            dateOp[strcspn(dateOp, "\n")] = '\0';

            operations = ajouterOperation(operations, code, numeroCompte, type, montant, dateOp);
            printf("Operation ajoutee avec succes !\n");
        } else if (choix == 4) {
            sauvegarderClients(clients);
            sauvegarderComptes(comptes);
            sauvegarderOperations(operations);
            printf("Donnees sauvegardees avec succes !\n");
        }
    } while (choix != 5);

    printf("Au revoir !\n");

    // Libération de la mémoire
    libererClients(clients);
    libererComptes(comptes);
    libererOperations(operations);

    return 0;
}