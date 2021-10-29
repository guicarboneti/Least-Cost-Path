#include <stdio.h>
#include <stdint.h>

typedef struct conexao {
    int a, b;   // sedes a e b;
    int c;      // custo de transmissão na conexão
} conexao;  // conexao entre a e b

// int checa_viabilidade(   cons,   a,    b) {
//     if (cons[i].a == b)
//         return 0;   // é viável
//     else
//         return checa_viabilidade(cons, a, b, );
// }

int main() {
    int n;  // numero de sedes
    int c;  // numero de conexoes possiveis
    int o;  // sede de origem
    int d;  // sede de destino
    int dt; // demanda de transmissão de o para d

    scanf("%d %d", &n, &c);
    scanf("%d %d %d", &o, &d, &dt);
    conexao cons[c];
    for (int i=0; i<c; i++) {
        scanf("%d %d %d", &cons[i].a, &cons[i].b, &cons[i].c);
    }

    // if (!checa_viabilidade(cons, a, b)) {     // retorna se o problema não é viável
    //     fprintf(stderr, "O problema e inviavel");
    //     return 1;
    // }

    printf("min: ");
    for (int i=0; i<c; i++) {   // função objetivo
        printf("%dx%d0 + %dx%d1", cons[i].c, i+1, cons[i].c, i+1);
        if (i+1<c) printf(" + ");
    }
    printf(";\n");

    int p=1;    // flag que indica primeira variável da desigualdade
    for (int i=0; i<c; i++) {   // deigualdade dos caminhos que saem da origem
        if (cons[i].a == o) {
            if (p==1) {
                printf("x%d0 ", i+1);
                p=0;
            } else {
                printf("+ x%d0 ", i+1);
            }
        }
        if (cons[i].b == o) {
            if (p==1) {
                printf("x%d1 ", i+1);
                p=0;
            } else {
                printf("+ x%d1 ", i+1);
            }
        }
    }
    printf(">= %d;\n", dt);

    p=1;
    for (int i=0; i<c; i++) {   // deigualdade dos caminhos que chegam ao destino
        if (cons[i].b == d) {
            if (p==1) {
                printf("x%d0 ", i+1);
                p=0;
            } else {
                printf("+ x%d0 ", i+1);
            }
        }
        if (cons[i].a == d) {
            if (p==1) {
                printf("x%d1 ", i+1);
                p=0;
            } else {
                printf("+ x%d1 ", i+1);
            }
        }
    }
    printf(">= %d;\n", dt);

    for (int i=0; i<c; i++) {   // desigualdades intermediárias
        // desigualdades em relação às conexões que chegam à sede
        if (cons[i].a != o) {   // desigualdade da direção convencional
            p=1;
            for (int j=0; j<c; j++) {
                if (cons[j].b == cons[i].a && i!=j) {
                    if (p==1) {
                        printf("x%d0 <= x%d0", i+1, j+1);
                        p=0;
                    } else {
                        printf(" + x%d0", j+1);
                    }
                }
                if (cons[j].a == cons[i].a && i!=j) {
                    if (p==1) {
                        printf("x%d0 <= x%d1", i+1, j+1);
                        p=0;
                    } else {
                        printf(" + x%d1", j+1);
                    }
                }
            }
            if (p==0) printf(";\n");
        }
        if (cons[i].b != d) {   // desigualdade da direção contrária
            p=1;
            for (int j=0; j<c; j++) {
                if (cons[j].b == cons[i].b && i!=j) {
                    if (p==1) {
                        printf("x%d1 <= x%d0", i+1, j+1);
                        p=0;
                    } else {
                        printf(" + x%d0", j+1);
                    }
                }
                if (cons[j].a == cons[i].b && i!=j) {
                    if (p==1) {
                        printf("x%d1 <= x%d1", i+1, j+1);
                        p=0;
                    } else {
                        printf(" + x%d1", j+1);
                    }
                }
            }
            if (p==0) printf(";\n");
        }

        // desigualdades em relação às conexões que saem da sede
        if (cons[i].b != d) {   // desigualdade da direção convencional
            p=1;
            for (int j=0; j<c; j++) {
                if (cons[j].a == cons[i].b && i!=j) {
                    if (p==1) {
                        printf("x%d0 >= x%d0 - x%d1", i+1, j+1, j+1);
                        p=0;
                    } else {
                        printf(" + x%d0 - x%d1", j+1, j+1);
                    }
                }
                if (cons[j].b == cons[i].b && i!=j) {
                    if (p==1) {
                        printf("x%d0 >= x%d1 - x%d0", i+1, j+1, j+1);
                        p=0;
                    } else {
                        printf(" + x%d1 - x%d0", j+1, j+1);
                    }
                }
            }
            if (p==0) printf(";\n");
        }
        if (cons[i].a != o) {   // desigualdade da direção contrária
            p=1;
            for (int j=0; j<c; j++) {
                if (cons[j].a == cons[i].a && i!=j) {
                    if (p==1) {
                        printf("x%d1 >= x%d0 - x%d1", i+1, j+1, j+1);
                        p=0;
                    } else {
                        printf(" + x%d0 - x%d1", j+1, j+1);
                    }
                }
                if (cons[j].b == cons[i].a && i!=j) {
                    if (p==1) {
                        printf("x%d1 >= x%d1 - x%d0", i+1, j+1, j+1);
                        p=0;
                    } else {
                        printf(" + x%d1 - x%d0", j+1, j+1);
                    }
                }
            }
            if (p==0) printf(";\n");
        }
    }

    for (int i=0; i<c; i++) {   // desigualdades que evitam fazer caminho inverso na origem ou no destino
        if (cons[i].a == o) {
            printf("x%d1 = 0;\n", i+1);
        }
        if (cons[i].b == d) {
            printf("x%d1 = 0;\n", i+1);
        }
    }

    printf("int ");
    for (int i=0; i<c; i++) {   // declara as variáveis como inteiros
        printf("x%d0, x%d1", i+1, i+1);
        if (i+1<c) printf(", ");
    }
    printf(";\n");

    return 0;
}