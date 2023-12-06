// CMakeProject1.cpp : Defines the entry point for the application.
//

#include "CMakeProject1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X 88
#define O 79
#define SPACE 32

void printBoard(char* p, int s) {
    // Input ukazovatelov na velkost hracehj plochy
    // funkcia printne aktualnu board
    int i, j;
    for (i = 0; i < s; i++) {
        printf("\n");
        if (i > 0) {
            // Print horizontalne ciary
            for (j = 0; j < s; j++) {
                if (j > 0) {
                    printf("----");
                }
                else {
                    printf("\t---");
                }
            }
        }
        else {
            // Print hlavičky
            printf("\t");
            for (j = 0; j < s; j++) {
                if (j > 0) {
                    printf("  %c ", j + 65);
                }
                else {
                    printf(" %c ", j + 65);
                }
            }
            printf("\n");
        }
        printf("\n %i", i + 1);
        // Print hodnoty riadkov
        for (j = 0; j < s; j++) {
            if (j > 0) {
                printf("|");
            }
            else {
                printf("\t");
            }
            printf(" %c ", *(p + i * s + j));
        }
    }
    printf("\n\n");
}

int turn(char* p, char player, int size) {

    char action[3];
    int x, y;

    while (1) {
        printf("Hrac za %c, umiestnite znacku :", player);
        scanf("%s", action);
        x = action[0];
        y = action[1];

        // Prerusi hru po stlaceni q
        if (action[0] == 113 || action[0] == 81) {
            printf("Ukoncenie hry...");
            exit(0);
        }
        // Kontrola platnosti hodnoty umiestnenia znacky
        if (x >= 97) {
            x -= 32;
        }
        if (x > (64 + size) || x < 65) {
            printf("%c je neplatna hodnota pre x.\n", x);
            continue;
        }
        else if (y > 48 + size || y < 48) {
            printf("%c je neplatna hodnota pre y.\n", y);
            continue;
        }
        else {
            // nastav index
            x -= 65;
            y -= 49;
            // printf("x:%d, y:%d\n",x, y);
        }
        // Skontroluje ci je uz policko obsadene


        if (*(p + y * size + x) == SPACE) { //*(p + y * size + x) ukazatel na aktualne zadane policko
            *(p + y * size + x) = player;                           // p - ukazatel na hraciu plochu
            break;
        }
        else {
            printf("Zvolene policko je uz obsadene.\n");
        }
    }

    //*(p + y * velkost + x) = hrac;

    return 0;
}


int checkWin(char* p, int size) {
    int i, j;        // premenne pre for cykly
    int hx, ho;      // Počítadlá horizontalne
    int vx, vo;      // Počítadlá vertikalne
    int hval, vval;  // Docasne ulozisko pre hodnoty
    int dx1, dx2, do1, do2;
    int total = 0;
    dx1 = dx2 = do1 = do2 = 0;

    // Loop cez riadky a stplce
    for (i = 0; i < size; i++) {
        // Reset
        hx = ho = vx = vo = 0;
        // Loop cez bunky
        for (j = 0; j < size; j++) {
            // Dostaneme hodnoty pre riadky a stplce
            hval = *(p + i * size + j); //bude obsahovat aktualnu hodnotu v riakdu (hval = X alebo O alebo medzera)
            vval = *(p + j * size + i); //bude obsahovat aktualnu hodnotu v stplci (vval = X alebo O alebo medzera)
            // Skontroluje zhody
            if (hval == X) {
                hx++;
            }
            if (hval == O) {
                ho++;
            }
            if (vval == X) {
                vx++;
            }
            if (vval == O) {
                vo++;
            }
            // Skontroluje diagonaly
            // dole
            if (i == j) {
                if (hval == X) {
                    dx1++;
                }
                if (hval == O) {
                    do1++;
                }
            }
            // hore
            if (size - 1 - i == j) {
                if (hval == X) {// je to X
                    dx2++;
                }
                if (hval == O) {// je to O
                    do2++;
                }
            }
        }
        // printf("Straights; Row: %i, hx: %i, ho: %i, vx: %i, vo: %i.\n", i, hx, ho, vx, vo);
        // printf("Diagonals; Row: %i, dx1: %i, do1: %i, dx2: %i, do2: %i.\n", i, dx1, do1, dx2, do2);
        if (hx == size || vx == size || dx1 == size || dx2 == size) {
            return X;
        }
        else if (ho == size || vo == size || do1 == size || do2 == size) {
            return O;
        }
        total += hx + ho;
    }
    // Skontroluje ci je hracia plocha plna
    // printf("Total: %i",total);
    if (total == size * size) {
        return 1;
    }
    return 0;
}



int main() {
    // Deklaracia premennych
    int players;
    int i, j;
    char* pboard;  // Zmena typu pboard na char*
    int size;
    int winner = 0;
    char playerArray[] = { X, O };  // zmena typu playerArray na char
    int p;


    char player1[10];
    char player2[10];


    printf("Vitajte v piskvorkach!\n");


    // Hraci
    printf("Zadajte meno prveho hraca, ktory bude hrat za X: ");
    scanf("%10s", player1);
    printf("Zadajte meno druheho hraca, ktory bude hrat za O: ");
    scanf("%10s", player2);

    printf("hrac 1: %s \nhrac 2: %s \n", player1, player2);



    // Velkost hracej plochy
    printf("Zvolte velkost hracej plochy (1-9): ");
    scanf("%ls", &size);

    // Kontrola ci je zadan hodnota medzi 1 a 9
    while (size - 48 < 1 || size - 48 > 9) {
        printf("Zadane cislo je prilis velke, prosim zvolte velkost medzi 1 a 9: ", size);
        scanf("%ls", &size);
    }
    size -= 48;
  


    // Vygenerovanie hracej plochy
    pboard = (char*)malloc(size * size * sizeof(char));  // Zmena typu pboard na char*

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            *(pboard + i * size + j) = SPACE;
        }
    }


    printBoard(pboard, size);

    char xo;
    int u = 0;

    while (1) {

        int result = checkWin(pboard, size);
        
        if (checkWin(pboard, size) != 0) {
            winner = result;
            break;
        }

        if (u % 2 == 0) {
            xo = X;
        }
        else {
            xo = O;
        }

        turn(pboard, xo, size);
        printBoard(pboard, size);
        checkWin(pboard, size);



        u++;

    }


    printBoard(pboard, size);
    free(pboard);  // uvolnenie pamäte kvoli malloc

    // Deklarácia výhercu!
    if (winner == 0) {
        printf("Remiza!");
    }
    else {
        printf("%c vyhral hru!", winner);
    }
    printf(" Po stlaceni hocijakeho tlacitka dokoncite.");
    getchar();
    getchar();
    return 0;
}
