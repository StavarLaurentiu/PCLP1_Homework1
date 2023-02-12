#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define pret_benzina 8.02
#define pret_motorina 9.29

typedef struct {
    char *brand;
    char *numar;
    char *combustibil;
    double consum;
    int km;
} masina;

void statComb(masina *v, int *cnt_b, int *cnt_m, int *cnt_h, int n) {
    char benzina[] = "benzina", motorina[] = "motorina";
    char hibrid[] = "hibrid";
    for (int i = 0; i < n; i++) {
        if (strcmp(v[i].combustibil, benzina) == 0) {
            (*cnt_b)++;
        } else if (strcmp(v[i].combustibil, motorina) == 0) {
            (*cnt_m)++;
        } else if (strcmp(v[i].combustibil, hibrid) == 0) {
            (*cnt_h)++;
        }
    }

}

int numCorect(masina *v, int i) {
    // fiecare aux(1, 2, 3) retine cate e parte din nr de inmatriculare
    char aux1[21] = {'0'}, aux2[21] = {'0'}, aux3[21] = {'0'};
    char aux[21];
    int cnt = -1;
    strcpy(aux, v[i].numar);

    // formez aux1 (contine litere pana la intalnirea primei cifre)
    int k;
    for (k = 0; k < strlen(aux); k++) {
        if (aux[k] >= 'A' && aux[k] <= 'Z') {
            aux1[++cnt] = aux[k];
        } else {
            break;
        }
    }

    // formez aux2 (contine cifre pana la inalnirea primei litere)
    cnt = -1;
    int j;
    for (j = k; j < strlen(aux); j++) {
        if (aux[j] >= '0' && aux[j] <= '9') {
            aux2[++cnt] = aux[j];
        } else {
            break;
        }
    }

    // formez aux3 (contine doar litere)
    cnt = -1;
    int q;
    for (q = j; q < strlen(aux); q++) {
        if (aux[q] >= 'A' && aux[q] <= 'Z') {
            aux3[++cnt] = aux[q];
        } else {
            break;
        }
    }

    /* Daca au mai ramas caractere in numarul de inmatriculare
    inseamna ca acesta nu este corect(ex : B123ABC12) */
    if (q != strlen(aux)) {
        return 0;
    }

    // verific ca lungimile sa fie corecte
    if (strlen(aux1) < 1 || strlen(aux1) > 2) {
        return 0;
    }
    if (strlen(aux2) < 2 || strlen(aux2) > 3) {
        return 0;
    }
    if (strlen(aux3) != 3) {
        return 0;
    }

    // verific daca continutul auxiliarelor este corect
    int c;
    for (c = 0; c < strlen(aux1); c++) {
        if (aux1[c] < 'A' || aux1[c] > 'Z') {
            return 0;
        }
    }
    for (c = 0; c < strlen(aux2); c++) {
        if (aux2[c] < '0' || aux2[c] > '9') {
            return 0;
        }
    }
    for (c = 0; c < strlen(aux3); c++) {
        if (aux3[c] < 'A' || aux3[c] > 'Z') {
            return 0;
        }
    }

    return 1;

}

void statConsum(masina *v, double *consum, double *pret, int n) {
    int cnt = -1;
    char benzina[] = "benzina", motorina[] = "motorina";
    char hibrid[] = "hibrid", electric[] = "electric";
    char aux[] = "-";
    /* Parcurg vectorul de masini iar la intalnirea unui brand pe
    care nu l-am mai intalnit pana acum parcurg restul vectorului
    pentru a cauta celelalte masini cu acel brand, daca exista */
    for (int i = 0; i < n; i++) {
        char nume[21];
        strcpy(nume, v[i].brand);
        if (strcmp(v[i].brand, aux) != 0) {
            /* Pentru fiecare brand nou pun in vectorii de consum si pret
            datele corespunzatoare primei masini gasite de tipul acelui
            brand si repet procedeul pentru toate masinile corespunzatoare,
            punand '-' in locul brandului pentru a imi facilita afisarea din
            main (in vectorul de masini fiecare brand va aparea doar o data);
            Pentru masinile cu combustibil electric nu voi adauga nimic la
            consum si pret */
            cnt++;
            if (strcmp(v[i].combustibil, electric) != 0) {
                consum[cnt] += v[i].consum * v[i].km / 100.0;
            }

            if (strcmp(v[i].combustibil, benzina) == 0 ||
                strcmp(v[i].combustibil, hibrid) == 0) {
                pret[cnt] += (v[i].consum * v[i].km / 100.0) * pret_benzina;
            } else if (strcmp(v[i].combustibil, motorina) == 0) {
                pret[cnt] += (v[i].consum * v[i].km / 100.0) * pret_motorina;
            }

            for (int j = i + 1; j < n; j++) {
                if (strcmp(v[j].brand, nume) == 0) {
                    double consumAux = v[j].consum * v[j].km / 100;
                    if (strcmp(v[i].combustibil, electric) != 0) {
                        consum[cnt] += consumAux;
                    }
                    if (strcmp(v[j].combustibil, benzina) == 0 ||
                        strcmp(v[j].combustibil, hibrid) == 0) {
                        pret[cnt] += consumAux * pret_benzina;
                    } else if (strcmp(v[j].combustibil, motorina) == 0) {
                        pret[cnt] += consumAux * pret_motorina;
                    }
                    strcpy(v[j].brand, aux);
                }
            }
        }
    }

}

int main() {
    int n;
    scanf("%d", &n);
    // aloc dinamic vectorul de masini, respectiv stringurile din structura
    masina *v = (masina *)malloc(n * sizeof(masina));
    for (int i = 0; i < n; i++) {
        char aux[21];
        // am folosit faptul ca sizeof(char) == 1
        scanf("%s ", aux);
        v[i].brand = (char *)malloc(strlen(aux) + 1);
        strcpy(v[i].brand, aux);
        scanf("%s ", aux);
        v[i].numar = (char *)malloc(strlen(aux) + 1);
        strcpy(v[i].numar, aux);
        scanf("%s ", aux);
        v[i].combustibil = (char *)malloc(strlen(aux) + 1);
        strcpy(v[i].combustibil, aux);
        scanf("%lf ", &v[i].consum);
        scanf("%d", &v[i].km);     
    }

    char op;
    // citesc "\n" de la finalul ultimei citiri
    getchar();
    scanf("%c", &op);

    // in functie de operator selectez ce operatie trebuie facuta
    if (op == 'a') {
        /* Parcurg vectorul de masini si cresc contorul corespunztor
        tipului de combustibil al fiecarei masini */
        int cnt_b = 0, cnt_m = 0, cnt_h = 0;
        statComb(v, &cnt_b, &cnt_m, &cnt_h, n);
        printf("benzina - %d\n", cnt_b);
        printf("motorina - %d\n", cnt_m);
        printf("hibrid - %d\n", cnt_h);
        printf("electric - %d\n", n - cnt_b - cnt_m - cnt_h);
    } else if (op == 'b') {
        char aux[] = "-";
        // consumul si pretul fiecarul brand
        double consum[101] = {0}, pret[101] = {0};
        int cnt = -1;
        statConsum(v, consum, pret, n);
        for (int i = 0; i < n; i++) {
            // daca nu a mai fost afisat acest brand
            if (strcmp(v[i].brand, aux) != 0) {
                cnt++;
                printf("%s a consumat %.2lf - %.2lf lei\n", v[i].brand,
                       consum[cnt], pret[cnt]);
            }
        }
    } else if (op == 'c') {
        // flag pentru afisare
        int flag = 1;
        for (int i = 0; i < n; i++) {
            if (!numCorect(v, i)) {
                flag = 0;
                printf("%s cu numarul %s: numar invalid\n", v[i].brand,
                       v[i].numar);
            }
        }
        if (flag) {
            printf("Numere corecte!\n");
        }
    }

    /* Eliberez memoria pentru stringurile din struct si pentru
    vectorul de masini */
    for (int i = 0; i < n; i++) {
        free(v[i].brand);
        free(v[i].numar);
        free(v[i].combustibil);
    }
    free(v);
    return 0;

}