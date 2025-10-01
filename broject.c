
#include <stdio.h>
#include <string.h>

//  Structures 
typedef struct {
    int idClient;
    char nom[30];
    char prenom[30];
    char email[60];
    float solde;
} Client;

typedef struct {
    int idProduit;
    char nom[30];
    char categorie[30];
    float prix;
    int stock;
    char description[100];
} Produit;

//  Prototypes 
void creerClient(Client *c, int *nextId);
void afficherClient(Client c);
void deposerSolde(Client *c, float montant);
void afficherProduits(Produit produits[], int n);
void acheterProduit(Client *c, Produit produits[], int n);
void rechercherProduit(Produit produits[], int n);
void trierProduits(Produit produits[], int n);
void consultationStatistiques(Produit produits[], int n);


int menuPrincipal();
int menuCatalogue();

//  Fonctions 
void creerClient(Client *c, int *nextId) {
    printf("\n--- Creation Client ---\n");
    printf("Nom: ");
    scanf("%s", c->nom);
    printf("Prenom: ");
    scanf("%s", c->prenom);

    c->idClient = (*nextId)++;
    sprintf(c->email, "%s.%s@client.com", c->prenom, c->nom);
    c->solde = 0.0;

    printf("Client cree avec succes !\n");
}

void afficherClient(Client c) {
    printf("\n--- Profil Client ---\n");
    printf("ID: %d\n", c.idClient);
    printf("Nom: %s %s\n", c.prenom, c.nom);
    printf("Email: %s\n", c.email);
    printf("Solde: %.2f MAD\n", c.solde);
}

void deposerSolde(Client *c, float montant) {
    c->solde += montant;
    printf("Depot effectue. Nouveau solde: %.2f MAD\n", c->solde);
}

void afficherProduits(Produit produits[], int n) {
    printf("\n--- Catalogue Produits ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d | %s | %s | %.2f MAD | Stock: %d\n  -> %s\n",
               produits[i].idProduit, produits[i].nom, produits[i].categorie,
               produits[i].prix, produits[i].stock, produits[i].description);
    }
}

void acheterProduit(Client *c, Produit produits[], int n) {
    int choix;
    afficherProduits(produits, n);
    printf("Entrez ID du produit a acheter: ");
    scanf("%d", &choix);

    int found = -1;
    for (int i = 0; i < n; i++) {
        if (produits[i].idProduit == choix) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Produit introuvable.\n");
        return;
    }

    if (produits[found].stock <= 0) {
        printf("Stock insuffisant.\n");
        return;
    }

    if (c->solde < produits[found].prix) {
        printf("Solde insuffisant.\n");
        return;
    }

    // Mise a jour
    produits[found].stock--;
    c->solde -= produits[found].prix;

    printf("Achat reussi de %s. Nouveau solde: %.2f MAD\n",
           produits[found].nom, c->solde);
}

void rechercherProduit(Produit produits[], int n) {
    int choix;
    char mot[30];
    printf("\nRecherche par:\n1. Nom\n2. Categorie\nVotre choix: ");
    scanf("%d", &choix);

    printf("Entrez le mot: ");
    scanf("%s", mot);

    printf("\n--- Resultat Recherche ---\n");
    for (int i = 0; i < n; i++) {
        if ((choix == 1 && strcasecmp(produits[i].nom, mot) == 0) ||
            (choix == 2 && strcasecmp(produits[i].categorie, mot) == 0)) {
            printf("%d | %s | %s | %.2f MAD | Stock: %d\n",
                   produits[i].idProduit, produits[i].nom, produits[i].categorie,
                   produits[i].prix, produits[i].stock);
        }
    }
}

void trierProduits(Produit produits[], int n) {
    int choix;
    printf("\nTrier par:\n1. Prix (croissant)\n2. Prix (decroissant)\n3. Nom (A-Z)\nVotre choix: ");
    scanf("%d", &choix);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int condition = 0;
            if (choix == 1 && produits[i].prix > produits[j].prix) condition = 1;
            else if (choix == 2 && produits[i].prix < produits[j].prix) condition = 1;
            else if (choix == 3 && strcmp(produits[i].nom, produits[j].nom) > 0) condition = 1;

            if (condition) {
                Produit tmp = produits[i];
                produits[i] = produits[j];
                produits[j] = tmp;
            }
        }
    }
    printf("Produits tries avec succes.\n");
    printf("\nProduits tries avec succes. Voici le nouveau catalogue:\n");
    afficherProduits(produits, n);
}
// ================= statistique =================
void consultationStatistiques(Produit produits[], int n) {
    int trouve = 0;
    printf("\n=== Consultation statistiques personnelles ===\n");
    printf("Produits encore disponibles (stock > 0):\n\n");

    for (int i = 0; i < n; i++) {
        if (produits[i].stock > 0) {
            printf("%d | %s | %s | %.2f MAD | Stock: %d\n  -> %s\n",
                   produits[i].idProduit, produits[i].nom, produits[i].categorie,
                   produits[i].prix, produits[i].stock, produits[i].description);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun produit disponible, tout est en rupture de stock.\n");
    }
}



int menuPrincipal() {
    int choix;
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Creer/Modifier Client\n");
    printf("2. Afficher Client\n");
    printf("3. Deposer Solde\n");
    printf("4. Catalogue Produits\n");
    printf("5. Acheter Produit\n");
    printf("6. Quitter\n");
    printf("Votre choix: ");
    scanf("%d", &choix);
    return choix;
}

int menuCatalogue() {
    int choix;
    printf("\n=== MENU CATALOGUE ===\n");
    printf("1. Afficher Produits\n");
    printf("2. Rechercher Produit\n");
    printf("3. Trier Produits\n");
    printf("4. Consultation statistiques personnelles\n"); 
    printf("5. Retour\n");
    printf("Votre choix: ");
    scanf("%d", &choix);
    return choix;
}

//  Main 
int main() {
    Client client;
    int clientCree = 0;
    int nextIdClient = 1;

    Produit produits[5] = {
        {1, "Laptop", "Informatique", 7000, 5, "Ordinateur Portable i5"},
        {2, "Smartphone", "Electronique", 3000, 10, "Telephone Android"},
        {3, "Casque", "Accessoires", 500, 20, "Casque Bluetooth"},
        {4, "Imprimante", "Bureau", 1500, 3, "Imprimante Couleur"},
        {5, "Clavier", "Accessoires", 250, 15, "Clavier AZERTY"}
    };

    int nbProduits = 5;
    int choix;

    while (1) {
        choix = menuPrincipal();
        if (choix == 1) {
            creerClient(&client, &nextIdClient);
            clientCree = 1;
        } else if (choix == 2) {
            if (clientCree) afficherClient(client);
            else printf("Aucun client cree.\n");
        } else if (choix == 3) {
            if (clientCree) {
                float montant;
                printf("Montant a deposer: ");
                scanf("%f", &montant);
                deposerSolde(&client, montant);
            } else printf("Creez un client d'abord.\n");

            } else if (choix == 4) {
    int choixC;
    do {
        choixC = menuCatalogue();
        if (choixC == 1) afficherProduits(produits, nbProduits);
        else if (choixC == 2) rechercherProduit(produits, nbProduits);
        else if (choixC == 3) trierProduits(produits, nbProduits);
        else if (choixC == 4) consultationStatistiques(produits, nbProduits); 
    } while (choixC != 5);
}
 
         else if (choix == 5) {
            if (clientCree) acheterProduit(&client, produits, nbProduits);
            else printf("Creez un client d'abord.\n");
        } else if (choix == 6) {
            printf("Merci d'avoir utilise notre systeme !\n");
            break;
        } else {
            printf("Choix invalide.\n");
        }
    }

    return 0;
}