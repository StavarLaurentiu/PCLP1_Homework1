#include <stdio.h>
#include <string.h>

void codificareA(char *text, char *key) {
    // m = nr de linii, n = nr de coloane = lungimea cheii
    int m, n = strlen(key);
    /* Decid cate linii are matricea de codificare in functie de
    rezultatul operatiei strlen(text) % strlen(key) */
    if (strlen(text) % strlen(key) != 0) {
        m = strlen(text) / strlen(key) + 1;
    } else {
        m = strlen(text) / strlen(key);
    }

    // construiesc matricea de codificare
    char cod[101][101];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cod[i][j] = ' ';
        }
    }
    int cnt = -1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cod[i][j] = text[++cnt];
            // daca am pus toate caracterele din text in matrice
            if (cnt == strlen(text) - 1) {
                break;
            }
        }
    }

    // fac un vector ce retine ordinea de afisare a coloanelor
    int ord[101];
    for (int i = 0; i < n; i++) {
        ord[i] = i;
    }
    // sortez cheia si vectorul de ordine dupa aceasta
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (key[i] > key[j]) {
                char aux = key[i];
                key[i] = key[j];
                key[j] = aux;
                int auxx = ord[i];
                ord[i] = ord[j];
                ord[j] = auxx;
            }
        }
    }

    /* Pun in "text" matricea "cod"(pe coloane) tinand cont
    de vectorul de ordine */
    cnt = -1;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            text[++cnt] = cod[i][ord[j]];
        }
    }
    text[++cnt] = '\0';
    
}

void codificareB(char *text, int nr) {
    char alf[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int q = 0; q < nr; q++) {
        // fac o permutare la dreapta
        char aux = text[strlen(text) - 1];
        for (int i = strlen(text) - 1; i > 0; i--) {
            text[i] = text[i - 1];
        }

        // construiesc noul caracter daca nu este spatiu
        if (aux != ' ') {
            // caut pozitia literei in alfabet
            int poz = 0;
            for (int i = 0; i < strlen(alf); i++) {
                if (aux == alf[i]) {
                    poz = i;
                    break;
                }
            }
            /* Daca noua pozitie nu depaseste lungimea alfabetului
            pun litera de la acea pozitie in string, in caz contrar
            scad lungimea alfabetului din pozitie pana cand aceasta
            se afla in alfabet si pun litera de la acea pozitie in
            string */
            poz += nr;
            if (poz >= strlen(alf)) {
                while (poz >= strlen(alf)) {
                    poz -= strlen(alf);
                }
            }
            text[0] = alf[poz];
        } else {
            text[0] = aux;
        }
    }

}

void decodificareA(char *text, char *key) {
    // m = nr de linii, n = nr de coloane = lungimea cheii
    int m, n = strlen(key);
    /* Decid cate linii are matricea de codificare in functie de
    rezultatul operatiei strlen(text) % strlen(key) */
    if (strlen(text) % strlen(key) != 0) {
        m = strlen(text) / strlen(key) + 1;
    } else {
        m = strlen(text) / strlen(key);
    }

    // construiesc matricea de codificare
    char cod[101][101];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cod[i][j] = ' ';
        }
    }
    // pun caracterele din text in matricea de codificare, pe coloana
    int cnt = -1;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            cod[i][j] = text[++cnt];
            // daca am pus toate caracterele din text in matrice
            if (cnt == strlen(text) - 1) {
                j = n;
                break;
            }
        }
    }

    // fac un vector ce retine ordinea de afisare a coloanelor
    int ord[101];
    for (int i = 0; i < n; i++) {
        ord[i] = i;
    }
    // sortez cheia si vectorul de ordine dupa aceasta
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (key[i] > key[j]) {
                char aux = key[i];
                key[i] = key[j];
                key[j] = aux;
                int auxx = ord[i];
                ord[i] = ord[j];
                ord[j] = auxx;
            }
        }
    }

    // inversez procesul de codificare in "matAux"
    char matAux[101][101];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matAux[i][j] = ' ';
        }
    }
    for (int j = 0; j < n; j++) {
        // in "col" retin nr coloanei ce trebuie pusa in matricea aux
        int col;
        for (int c = 0; c < n; c++) {
            if (ord[c] == j) {
                col = c;
                break;
            }
        }
        // pun coloana "col" in matAux
        for (int i = 0; i < m; i++) {
            matAux[i][j] = cod[i][col];
        }
    }

    // pun in "text" decodificarea obtinuta in matAux
    cnt = -1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            text[++cnt] = matAux[i][j];
        }
    }
    text[++cnt] = '\0';

}

void decodificareB(char *text, int nr) {
    char alf[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int q = 0; q < nr; q++) {
        // fac o permutare la stanga
        char aux = text[0];
        for (int i = 0; i < strlen(text) - 1; i++) {
            text[i] = text[i + 1];
        }

        // construiesc noul caracter daca nu este spatiu
        if (aux != ' ') {
            // caut pozitia literei in alfabet
            int poz = 0;
            for (int i = 0; i < strlen(alf); i++) {
                if (aux == alf[i]) {
                    poz = i;
                    break;
                }
            }

            /* Daca noua pozitie nu este mai mica ca 0 pun litera de
            la acea pozitie din alfabet in string, in caz contrar
            adun lungimea alfabetului la pozitie pana cand aceasta
            este mai mare ca 0 si pun litera de la acea pozitie din
            alfabet in string */
            poz -= nr;
            if (poz >= strlen(alf)) {
                while (poz < 0) {
                    poz += strlen(alf);
                }
            }
            text[strlen(text) - 1] = alf[poz];
        } else {
            text[strlen(text) - 1] = aux;
        }
    }

}

int main() {
    char text[101], tipCodificare[14], mySTOP[] = "STOP";
    char CodA[] = "CodificareA", CodB[] = "CodificareB";
    char DeCodA[] = "DecodificareA", DeCodB[] = "DecodificareB";
    char key[30];
    fgets(text, 101, stdin);
    // elimin "\n" de la final
    *(text + strlen(text) - 1) = '\0';
    scanf("%s", tipCodificare);

    while (strcmp(tipCodificare, mySTOP) != 0) {
        // citesc spatiul dintre tipul codificarii si cheie
        getchar();
        if (strncmp(tipCodificare, CodA, 12) == 0) {
            fgets(key, 29, stdin);
            *(key + strlen(key) - 1) = '\0';
            codificareA(text, key);
        } else if (strncmp(tipCodificare, CodB, 12) == 0) {
            int nr;
            scanf("%d", &nr);
            codificareB(text, nr);
        } else if (strcmp(tipCodificare, DeCodA) == 0) {
            fgets(key, 29, stdin);
            *(key + strlen(key) - 1) = '\0';
            decodificareA(text, key);
        } else if (strcmp(tipCodificare, DeCodB) == 0) {
            int nr;
            scanf("%d", &nr);
            decodificareB(text, nr);
        }

        puts(text);
        scanf("%s", tipCodificare);
    }
    return 0;

}