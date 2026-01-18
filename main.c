#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Marfa {
    char denumire[50];
    char tara[30];
    char producator[50];
    int articol;
    float pret;
};

struct Marfa *tablou = NULL;
int n = 0;

void alocare() {
    printf("Introdu numarul de elemente: ");
    scanf("%d", &n);
    tablou = (struct Marfa*)malloc(n * sizeof(struct Marfa));
}

void introducere() {
    for (int i = 0; i < n; i++) {
        printf("\nMarfa %d\n", i + 1);
        printf("Denumire: ");
        scanf("%s", tablou[i].denumire);
        printf("Tara: ");
        scanf("%s", tablou[i].tara);
        printf("Producator: ");
        scanf("%s", tablou[i].producator);
        printf("Articol: ");
        scanf("%d", &tablou[i].articol);
        printf("Pret: ");
        scanf("%f", &tablou[i].pret);
    }
}

void cautare() {
    int art;
    printf("Introdu articolul cautat: ");
    scanf("%d", &art);

    int gasit = 0;
    for (int i = 0; i < n; i++) {
        if (tablou[i].articol == art) {
            printf("\nElement gasit:\n");
            printf("Denumire: %s\n", tablou[i].denumire);
            printf("Tara: %s\n", tablou[i].tara);
            printf("Producator: %s\n", tablou[i].producator);
            printf("Articol: %d\n", tablou[i].articol);
            printf("Pret: %.2f\n", tablou[i].pret);
            gasit = 1;
        }
    }

    if (!gasit) {
        printf("Elementul nu a fost gasit.\n");
    }
}


void sortare() {
    struct Marfa aux;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (tablou[i].pret > tablou[j].pret) {
                aux = tablou[i];
                tablou[i] = tablou[j];
                tablou[j] = aux;
            }
}

void redactare() {
    int poz;
    printf("Introdu pozitia (1-%d): ", n);
    scanf("%d", &poz);
    poz--;

    printf("Denumire noua: ");
    scanf("%s", tablou[poz].denumire);
    printf("Pret nou: ");
    scanf("%f", &tablou[poz].pret);
}

void adaugare() {
    n++;
    tablou = (struct Marfa*)realloc(tablou, n * sizeof(struct Marfa));

    printf("Denumire: ");
    scanf("%s", tablou[n - 1].denumire);
    printf("Tara: ");
    scanf("%s", tablou[n - 1].tara);
    printf("Producator: ");
    scanf("%s", tablou[n - 1].producator);
    printf("Articol: ");
    scanf("%d", &tablou[n - 1].articol);
    printf("Pret: ");
    scanf("%f", &tablou[n - 1].pret);
}

void eliminare() {
    int poz;
    printf("Introdu pozitia de sters: ");
    scanf("%d", &poz);
    poz--;

    for (int i = poz; i < n - 1; i++)
        tablou[i] = tablou[i + 1];

    n--;
    tablou = (struct Marfa*)realloc(tablou, n * sizeof(struct Marfa));
}

void inserare() {
    int poz;
    printf("Introdu pozitia de inserare: ");
    scanf("%d", &poz);
    poz--;

    n++;
    tablou = (struct Marfa*)realloc(tablou, n * sizeof(struct Marfa));

    for (int i = n - 1; i > poz; i--)
        tablou[i] = tablou[i - 1];

    printf("Denumire: ");
    scanf("%s", tablou[poz].denumire);
    printf("Tara: ");
    scanf("%s", tablou[poz].tara);
    printf("Producator: ");
    scanf("%s", tablou[poz].producator);
    printf("Articol: ");
    scanf("%d", &tablou[poz].articol);
    printf("Pret: ");
    scanf("%f", &tablou[poz].pret);
}

void salvare() {
    FILE *f = fopen("marfa.txt", "w");
    for (int i = 0; i < n; i++)
        fprintf(f, "%s %s %s %d %.2f\n",
                tablou[i].denumire,
                tablou[i].tara,
                tablou[i].producator,
                tablou[i].articol,
                tablou[i].pret);
    fclose(f);
}

void citire() {
    FILE *f = fopen("marfa.txt", "r");
    if (!f) {
        printf("Fisierul nu a putut fi deschis!\n");
        return;
    }

    n = 0;
    free(tablou); // Eliberăm memoria anterioară
    tablou = NULL;

    struct Marfa temp;
    while (fscanf(f, "%s %s %s %d %f",
                  temp.denumire,
                  temp.tara,
                  temp.producator,
                  &temp.articol,
                  &temp.pret) == 5) {
        n++;
        tablou = (struct Marfa*)realloc(tablou, n * sizeof(struct Marfa));
        tablou[n - 1] = temp;
                  }

    fclose(f);
    printf("%d elemente au fost citite din fisier.\n", n);
}


void afisare() {
    for (int i = 0; i < n; i++) {
        printf("\nDenumire:%d \nTara:%s \nProducator:%s \nArticol:%s \nPret:%d\n",
               i + 1,
               tablou[i].denumire,
               tablou[i].tara,
               tablou[i].producator,
               tablou[i].articol,
               tablou[i].pret);
    }
}

void eliberare() {
    free(tablou);
    tablou = NULL;
    n = 0;
}

int main() {
    int opt;
    do {
        printf("\n--- MENIU ---\n");
        printf("1. Alocare memorie\n");
        printf("2. Introducere elemente\n");
        printf("3. Cautare element\n");
        printf("4. Sortare\n");
        printf("5. Redactare\n");
        printf("6. Adaugare la sfarsit\n");
        printf("7. Eliminare element\n");
        printf("8. Inserare element\n");
        printf("9. Salvare in fisier\n");
        printf("10. Citire din fisier\n");
        printf("11. Afisare\n");
        printf("12. Eliberare memorie\n");
        printf("0. Iesire\n");
        printf("Optiunea: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1: alocare(); break;
            case 2: introducere(); break;
            case 3: cautare(); break;
            case 4: sortare(); break;
            case 5: redactare(); break;
            case 6: adaugare(); break;
            case 7: eliminare(); break;
            case 8: inserare(); break;
            case 9: salvare(); break;
            case 10: citire(); break;
            case 11: afisare(); break;
            case 12: eliberare(); break;
        }
    } while (opt != 0);

    return 0;
}
