#include <stdio.h>

#define MAX 10

double somatorioU(int i, int j, double M[][MAX], double L[][MAX], double U[][MAX]) {
    double cont = 0.0;
    int k;
    for (k = 0; k < i; k++) {
        cont += L[i][k] * U[k][j];
    }
    return cont;
}

void MU(int i, int j, int n, double M[][MAX], double L[][MAX], double U[][MAX]) {
    for (j = 0; j < n; j++) {
        if (i == 0) {
            U[i][j] = M[i][j];
			printf("\nMatriz U[%d][%d] = %.2lf\n", i, j, U[i][j]);
        } else {
            U[i][j] = M[i][j] - somatorioU(i, j, M, L, U);
			printf("\nMatriz U[%d][%d] = %.2lf\n", i, j, U[i][j]);
        }
    }
}

double somatorioL(int i, int j, double M[][MAX], double L[][MAX], double U[][MAX]) {
    double cont = 0.0;
    int k;
    for (k = 0; k < j; k++) {
        cont += L[i][k] * U[k][j];
    }
    return cont;
}

void ML(int i, int j, int n, double M[][MAX], double L[][MAX], double U[][MAX]) {
    for (i = 0; i < n; i++) {
        if (j == 0) {
            L[i][j] = M[i][j] / U[j][j];
			printf("\nMatriz L[%d][%d] = %.2lf\n", i, j, L[i][j]);
        } else {
            L[i][j] = (M[i][j] - somatorioL(i, j, M, L, U)) / U[j][j];
			printf("\nMatriz L[%d][%d] = %.2lf\n", i, j, L[i][j]);
        }
    }
}

void BU(int i, int j, int n, double B[], double L[][MAX], double BU[]) {
    BU[i] = B[i];
    for (j = 0; j < i; j++) {
        BU[i] -= L[i][j] * BU[j];
    }
}

void MGC(int t, double M[][MAX], double X[], double B[]) {
    int i, j;
    double U[MAX][MAX], L[MAX][MAX], Bu[MAX];

    for (i = 0, j = 0; i < t; i++) {
        MU(i, j, t, M, L, U);
        j++;
        ML(i, j, t, M, L, U);
        BU(i, j, t, B, L, Bu);
    }

    // Resolver o sistema linear
    for (i = t - 1; i >= 0; i--) {
        X[i] = Bu[i];
        for (j = i + 1; j < t; j++) {
            X[i] -= U[i][j] * X[j];
        }
        X[i] /= U[i][i];
    }
}

int main() {
    double A[MAX][MAX], X[MAX], B[MAX];
    int i, n, j;

    printf("Digite a ordem da matriz: ");
    scanf("%d", &n);

    printf("\nDigite a matriz\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("\nDigite o vetor B:\n");
    for (i = 0; i < n; i++) {
        scanf("%lf", &B[i]);
    }

    MGC(n, A, X, B);

    printf("\nO vetor X eh:\n(");
    for (i = 0; i < n; i++) {
        printf(" %lf ", X[i]);
    }
	printf(")");
    return 0;
}
