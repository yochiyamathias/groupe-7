#include <stdio.h>
#include <string.h>

// structure pour un client
typedef struct {
    int codecli;
    char prenom[40];
    char nom[40];
    char tel[15];
    char ville[40];
} Client;

// structure pour un compte
typedef struct {
    int numero;
    char dateOuverture[15];
    char agence[40];
    float solde;
    int codecli; // Lien avec un client
} Compte;

// structure pour une operatiuon
typedef struct {
    int code;
    int numeroCompte;
    char type[10]; // "depot" ou "retrait"
    float montant;
    char dateOp[15];
} Operation;

	
