#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct entry {
    char brand[20], productName[50];
    float price;
    int stock;

};

struct nod {
    struct entry data;
    struct nod *urm;
};

int initialized = 0;
struct nod *first = NULL, *last = NULL;
int nrElem = 0;

void menu() {
    if (initialized == 0) {
        struct entry tempEntry;
        printf("Add a first entry:\n");
        printf("Brand:");
        scanf("%s", &tempEntry.brand);
        printf("Product Name:");
        scanf("%s", &tempEntry.productName);
        printf("Price:");
        scanf("%f", &tempEntry.price);
        printf("Products in stock: ");
        scanf("%d", &tempEntry.stock);
        struct nod *p = (struct nod *) malloc(sizeof(struct nod));
        p->data = tempEntry;
        p->urm = NULL;
        first = p;
        last = p;
        last->urm = NULL;
        nrElem++;
        initialized = 1;
    }
    system("CLS");
    printf("1. Add entry\n2. Remove entry\n3. Print current entry list\n4. Exit\nInput a choice : ");
    return;

}

void addFirst() {
    system("CLS");
    struct entry tempEntry;
    printf("Brand:");
    scanf("%s", &tempEntry.brand);
    printf("Product Name:");
    scanf("%s", &tempEntry.productName);
    printf("Price:");
    scanf("%f", &tempEntry.price);
    printf("Products in stock: ");
    scanf("%d", &tempEntry.stock);
    struct nod *p = (struct nod *) malloc(sizeof(struct nod));
    p->data = tempEntry;
    p->urm = first;
    first = p;
}

void addLast() {
    system("CLS");
    struct entry tempEntry;
    printf("Brand:");
    scanf("%s", &tempEntry.brand);
    printf("Product Name:");
    scanf("%s", &tempEntry.productName);
    printf("Price:");
    scanf("%f", &tempEntry.price);
    printf("Products in stock: ");
    scanf("%d", &tempEntry.stock);
    struct nod *p = (struct nod *) malloc(sizeof(struct nod));
    p->data = tempEntry;
    p->urm = NULL;
    last->urm = p;
    last = p;
}

void addPosition() {
    int index, i = 1;
    printf("Which position should the entry be placed after?[0-%d]\n", nrElem);
    scanf("%d", &index);
    if (index < 0 || index > nrElem) {
        printf("Invalid Choice");
        getch();
    } else {
        if (index == 0)
            addFirst();
        else if (index == nrElem)
            addLast();
        else {
            struct nod *p = first;
            while (i < index) {
                p = p->urm;
                i++;
            }
            struct entry tempEntry;
            printf("Brand:");
            scanf("%s", &tempEntry.brand);
            printf("Product Name:");
            scanf("%s", &tempEntry.productName);
            printf("Price:");
            scanf("%f", &tempEntry.price);
            printf("Products in stock: ");
            scanf("%d", &tempEntry.stock);
            struct nod *q = (struct nod *) malloc(sizeof(struct nod));
            q->data = tempEntry;
            q->urm = p->urm;
            p->urm = q;
        }

    }
}

void adaugare() {
    system("CLS");
    int choice;
    printf("Where should the entry be added?\n\n");
    printf("1. As the first entry\n");
    printf("2. As the last entry\n");
    printf("3. After index X\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            addFirst();
            nrElem++;
            break;
        case 2:
            addLast();
            nrElem++;
            break;
        case 3:
            addPosition();
            nrElem++;
            break;

        default:
            printf("Invalid Choice");
            getch();
            getch();
            return;
    }

}

void afisare() {
    int i = 0;
    system("CLS");
    struct nod *p = first;
    printf("Current entry list: \n");
    while (p != NULL) {
        printf("%d. %s, %s, %f, %d\n", ++i, p->data.brand, p->data.productName, p->data.price, p->data.stock);
        p = p->urm;
    }
    getch();
}

void stergPrim() {
    if (nrElem == 0) return;
    if (first != NULL)
        nrElem--;
    struct nod *p = first;
    first = first->urm;
    free(p);
}

void stergUlt() {
    if (nrElem == 0) return;
    if (last != NULL)
        nrElem--;
    struct nod *p = first;
    while (p->urm != last) {
        p = p->urm;
    }
    struct nod *q = last;
    p->urm = NULL;
    last = p;
    free(q);
}

void stergPosi() {
    if (nrElem == 0) return;
    system("CLS");
    int index;
    printf("Insert the index of the entry you wish removed [1-%d]:\n", nrElem);
    scanf("%d", &index);
    if (index < 1 || index > nrElem) {
        printf("Invalid Choice");
        getch();
    } else {
        if (index == 1)
            stergPrim();
        else if (index == nrElem)
            stergUlt();
        else {
            int i = 1;
            struct nod *p = first;
            while (i < index - 1) {
                i++;
                p = p->urm;
            }
            struct nod *q = p->urm;
            p->urm = p->urm->urm;
            free(q);
            nrElem--;
        }

    }
}

void stergX() {
    if (nrElem == 0) return;
    system("CLS");
    printf("Enter the name of the product to be removed (CaSe SeNsItIvE)\n");
    char tempName[50];
    scanf("%s", &tempName);
    struct nod *p = first;
    if (strcmp(p->data.productName, tempName) == 0)
        stergPrim();
    else {
        while (p->urm != NULL && strcmp(p->data.productName, tempName) != 0)
            p = p->urm;
        if (p->urm == NULL) {
            printf("Product not found");
            getch();
            return;
        } else {
            struct nod *q = p->urm->urm;
            free(p->urm);
            p->urm = q;
            nrElem--;
        }

    }
}

void stergere() {
    system("CLS");
    int choice;
    printf("Which entry should be removed?\n\n");
    printf("1. First entry\n");
    printf("2. Last entry\n");
    printf("3. Entry at index X\n");
    printf("4. Product named \"X\"\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            stergPrim();
            break;
        case 2:
            stergUlt();

            break;
        case 3:
            stergPosi();
            break;
        case 4:
            stergX();
            break;
        default:
            scanf("Invalid Choice");
            getch();
            return;
    }

}

int main() {
    int choice;
    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                adaugare();
                break;
            case 2:
                stergere();
                break;
            case 3:
                afisare();
                break;
            case 4:
                return 0;
            default:
                printf("Alegere invalida");
                getch();
        }
    }
}
