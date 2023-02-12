#include <stdio.h>
#include <string.h>

// interschimba doua stringuri
void mySwap(char *a, char *b, int n) {
    char aux[1002];
    strncpy(aux, a, n);
    strncpy(a, b, n);
    strncpy(b, aux, n);
    
}

void adunare(char *a, char *b, int n) {
    // cazul in care se aduna un nr negativ cu unul pozitiv
    if ((*a == '1' && *b == '0') || (*a == '0' && *b == '1')) {
        /* Voi avea grija ca primul numar sa fie intotdeauna mai mare (a)
        daca voi recurge la o interschimbare semnul rezultatului va fi
        negativ, altfel pozitiv */
        char semn = '0';
        if (*a == '1') {
            mySwap(a, b, n);
        }
        if (strncmp(a + 1, b + 1, n - 1) < 0) {
            semn = '1';
            mySwap(a, b, n);
        }
        // fac ambele numere pozitive
        *a = 0;
        *b = 0;
        // scad numerele
        for (int i = n - 1; i >= 1; i--) {
            // nr = rezultatul scaderii brute (ex 5 - 8 = -3, nr = -3)
            int nr = ((int)*(a + i) - 48) - ((int)*(b + i) - 48);
            // daca nr < 0 inseamna ca trebuie sa ma "imprumut"
            if (nr < 0) {
                /* Acum in nr ramane rezultatul de pe acel bit
                (ex nr = -3 -> nr = 10 - 3 -> nr = 7) */
                nr = 10 + nr;
                /* Merg spre stanga pana gasesc o cifra de unde
                sa imprumut, daca gasesc cifra 0 o transform
                in 9 si imi continui cautarea */
                for (int j = i - 1; j >= 1; j--) {
                    if (*(a + j) != '0') {
                        (*(a + j))--;
                        break;
                    } else {
                        (*(a + j)) = '9';
                    }
                }
            }
            // pun rezultatul scaderii de pe acel bit in a
            *(a + i) = (char)(nr + 48);
        }
        *a = semn;
    }
    // cazul in care se aduna fie doua numere pozitive fie doua negative
    else {
        // ce ramane "in minte"
        int rest = 0;
        for (int i = n - 1; i >= 1; i--) {
            /* In nr retin rezultatul adunarii bit cu bit
            Voi face cast de la char la int iar din rezultat scad
            48 (codul ASCII a lui 0) pentru a obtine chiar numarul in
            format int, ulterior inversez procesul */
            int nr = ((int)*(a + i) - 48) + ((int)*(b + i) - 48) + rest;
            rest = nr / 10;
            *(a + i) = (char)(nr % 10 + 48);
        }
    }

}

// transform scaderile in adunari prin reguli de forma a - b == a + (-b)
void scadere(char *a, char *b, int n) {
    if (*a == '1' && *b == '0') {
        *b = '1';
        adunare(a, b, n);
    } else if (*a == '0' && *b == '1') {
        *b = '0';
        adunare(a, b, n);
    } else if (*a == '1' && *b == '1') {
        *b = '0';
        adunare(a, b, n);
    } else {
        *b = '1';
        adunare(a, b, n);
    }

}

int main() {
    int n;
    char a[1002], b[1002], op[10];  // op = operator

    // citire date
    scanf("%d", &n);
    scanf("%s", a);
    scanf("%s", op);

    while (*op != '0' && scanf("%s", b)) {
        if (*op == '+') {
            // adunare parte reala
            adunare(a, b, n / 2);
            // adunare parte imaginara
            adunare(a + n / 2, b + n / 2, n / 2);
        } else if (*op == '-') {
            // scadere parte reala
            scadere(a, b, n / 2);
            // scadere parte imaginara
            scadere(a + n / 2, b + n / 2, n / 2);
        }

        printf("%s\n", a);
        scanf("%s", op);
    }
    return 0;

}