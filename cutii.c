#include <stdio.h>

// parcurgere vectorul box si pune toate ciclurile in matricea "a"
void cautareCicluri(int box[], int p, int a[][501], int *m) {
    for (int i = 1; i <= p; i++) {
        if (box[i] != 0) {
            (*m)++;
            // contor pentru coloana
            int n = -1;
            int ci = i;
            // pun punctul de plecare al ciclului in matrice
            a[*m][++n] = ci;
            int cnt = 0;
            while (cnt < p) {
                int c = box[ci];
                box[ci] = 0;
                if (c == i) {
                    break;
                }
                ci = c;
                a[*m][++n] = c;
                cnt++;
            }
            // marchez sfarsitul ciclului
            a[*m][++n] = -1;
        }
    }

}

void jocBox(int box[], int i, int p, int *castig) {
    int ci = i;
    *castig = 0;
    int cnt = 0;
    while (cnt < p / 2) {
        int c = box[i];
        // daca jocul a fost castigat
        if (c == ci) {
            *castig = 1;
            break;
        } else
            i = c;
        cnt++;
    }
    
}

int main() {
    // box = vectorul pentru cutii, p = prizonieri
    int box[512], p;
    scanf("%d", &p);
    for (int i = 1; i <= p; i++) {
        scanf("%d", &box[i]);
    }

    // flag pentru afisare (0 == nu s-a afisat nimic)
    int afisare = 0;
    for (int i = 1; i <= p; i++) {
        // flag pentru fiecare prizonier (0 == a pierdut jocul)
        int castig = 0;
        jocBox(box, i, p, &castig);
        /* Testez daca prizonierul nu a trecut testul si inca nu s-a facut
        vreo afisare */
        if (!castig && !afisare) {
            printf("Nu\n");
            afisare = 1;
        }
    }

    // testez daca nu s-a facut afisarea deja
    if (!afisare) {
        printf("Da\n");
    }

    // matrice ce retine ciclurile
    int a[501][501];
    // linia si coloana matricei de cicluri
    int m = -1, n = 0;
    cautareCicluri(box, p, a, &m);

    /* Parcurg matricea de cicluri ce are m + 1 linii in urma apelarii
    functiei cautareCicluri() */
    for (int i = 0; i <= m; i++) {
        n = 0;
        while (a[i][n] != -1) {
            // daca este ultimul element din ciclu schimb afisarea
            if (a[i][n + 1] == -1) {
                printf("%d", a[i][n]);
            } else {
                printf("%d ", a[i][n]);
            }
            n++;
        }
        printf("\n");
    }
    return 0;
    
}