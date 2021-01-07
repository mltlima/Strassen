#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int N = 2000; //Tamanho da matriz


//--------------------------------------------------------------
// Libera memoria dos ponteiros para os calculos
int **liberarMemoria(int **vetor, int tamanho) {

    if (vetor == NULL) {
        return (NULL);
    }

    for (int i = 0; i < tamanho; i++) { 
        if (vetor[i]) { 
            free(vetor[i]); // libera linha da matriz
            vetor[i] = NULL;
        } 
    } 

    free(vetor);         //libera ponteiro
    vetor = NULL;

    return (NULL);   //retorna ponteiro null
}
//--------------------------------------------------------------



// Aloca memoria para matriz com 0s como valores
int **alocarMatrix(int tamanho) {


    int **vetor;
    
    //Alocacao de um vetor
    vetor = (int**) malloc(tamanho * sizeof(int*));

    if (vetor == NULL) {
        printf ("Erro ao alocar memoria");
        return (NULL);
    }

    // aloca memoria para cada vetor da matriz
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = (int*) malloc(tamanho * sizeof(int));

        if (vetor[i] == NULL) {
            printf ("Memoria insuficiente");
            liberarMemoria(vetor, tamanho);
            return (NULL);
        }

        // inicializa matriz com 0s
            for (int j = 0; j < tamanho; j++)
                vetor[i][j] = 0;
        
    }

    return (vetor);     // returns the pointer to the vector. 

}

//--------------------------------------------------------------

//Alocacao na memoria usando malloc
//inicia a matriz com valores aleatorios
//variavel tamanho matriz quadrada NxN
int **alocarMatrixInicial(int tamanho, int potencia) {

    //srand(time(NULL));
    int **vetor;
    
    //Alocacao de um vetor
    vetor = (int**) malloc(potencia * sizeof(int*));

    if (vetor == NULL) {
        printf ("Erro ao alocar memoria");
        return (NULL);
    }

    // aloca memoria para cada vetor da matriz
    for (int i = 0; i < potencia; i++) {
        vetor[i] = (int*) malloc(potencia * sizeof(int));

        if (vetor[i] == NULL) {
            printf ("Memoria insuficiente");
            liberarMemoria(vetor, potencia);
            return (NULL);
        }

        // inicializa matriz com 0s para a matriz tamanho
        // da proxima potencia de 2
            for (int j = 0; j < potencia; j++)
                vetor[i][j] = 0;
        

        // inicializa matriz com numeros entre -1000 e 1000
                for (int j = 0; j < tamanho; j++) {
                    if (i < tamanho)
                        vetor[i][j] = (rand() % (2 * 1001)) - 1001;
                }
        
    }

    return (vetor);     // retorna o ponteiro para o vetor 

}
//--------------------------------------------------------------

//Multiplicacao ingenua de duas matrizes
void multiplica(int **A, int **B, int **C, int tamanho) {
    for (int i = 0; i < tamanho; i++){
        for (int j = 0; j < tamanho; j++){
            C[i][j] = 0;
            for (int k = 0; k < tamanho; k++){
               C[i][j] += A[i][k] * B[k][j]; 
            }  
        } 
    }
}
//--------------------------------------------------------------



// funcao para somar duas matrizes
void soma(int **A, int **B, int **resultado, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            resultado[i][j] = A[i][j] + B[i][j];
        }
    }
}
//--------------------------------------------------------------


// funcao para subtrair duas matrizes
void subtracao(int **A, int **B, int **resultado, int tamanho) {

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            resultado[i][j] = A[i][j] - B[i][j];
        }
    }	
}
//--------------------------------------------------------------

//Multiplicacao de matrizes algoritmo de strassen
void strassen(int **A, int **B, int **C, int tamanho) {

    // tamanho < valor muda do algoritimo de strassen
    // para multiplicacao ingenua
    if (tamanho < 256) {
        //C[0][0] = A[0][0] * B[0][0]; // Multiplicacao ate matriz 1 x 1
        multiplica(A,B,C,tamanho);
        return;
    } else {
        
        int novoTamanho = tamanho/2; //metade do tamanho a cada chamada recursiva da funcao
        int **a11, **a12, **a21, **a22;
        int **b11, **b12, **b21, **b22;
        int **c11, **c12, **c21, **c22;
        int **m1, **m2, **m3, **m4, **m5, **m6, **m7;

        // alocacao memoria:
        a11 = alocarMatrix(novoTamanho);
        a12 = alocarMatrix(novoTamanho);
        a21 = alocarMatrix(novoTamanho);
        a22 = alocarMatrix(novoTamanho);

        b11 = alocarMatrix(novoTamanho);
        b12 = alocarMatrix(novoTamanho);
        b21 = alocarMatrix(novoTamanho);
        b22 = alocarMatrix(novoTamanho);

        c11 = alocarMatrix(novoTamanho);
        c12 = alocarMatrix(novoTamanho);
        c21 = alocarMatrix(novoTamanho);
        c22 = alocarMatrix(novoTamanho);

        m1 = alocarMatrix(novoTamanho);
        m2 = alocarMatrix(novoTamanho);
        m3 = alocarMatrix(novoTamanho);
        m4 = alocarMatrix(novoTamanho);
        m5 = alocarMatrix(novoTamanho);
        m6 = alocarMatrix(novoTamanho);
        m7 = alocarMatrix(novoTamanho);

        int **resultadoA = alocarMatrix(novoTamanho);
        int **resultadoB = alocarMatrix(novoTamanho);

        //Dividir a matriz em 4
        for (int i = 0; i < novoTamanho; i++) { 
            for (int j = 0; j < novoTamanho; j++) {
                a11[i][j] = A[i][j];
                a12[i][j] = A[i][j + novoTamanho];
                a21[i][j] = A[i + novoTamanho][j];
                a22[i][j] = A[i + novoTamanho][j + novoTamanho];

                b11[i][j] = B[i][j];
                b12[i][j] = B[i][j + novoTamanho];
                b21[i][j] = B[i + novoTamanho][j];
                b22[i][j] = B[i + novoTamanho][j + novoTamanho];
            }
        }

        //Calculo m1 a m7

            soma(a11, a22, resultadoA, novoTamanho); // a11 + a22
            soma(b11, b22, resultadoB, novoTamanho); // b11 + b22
            strassen(resultadoA, resultadoB, m1, novoTamanho); // m1 = (a11+a22) * (b11+b22)
            
            soma(a21, a22, resultadoA, novoTamanho); // a21 + a22
            strassen(resultadoA, b11, m2, novoTamanho); // m2 = (a21+a22) * (b11)

            subtracao(b12, b22, resultadoB, novoTamanho); // b12 - b22
            strassen(a11, resultadoB, m3, novoTamanho); // m3 = (a11) * (b12 - b22)

            subtracao(b21, b11, resultadoB, novoTamanho); // b21 - b11
            strassen(a22, resultadoB, m4, novoTamanho); // m4 = (a22) * (b21 - b11)

            soma(a11, a12, resultadoA, novoTamanho); // a11 + a12
            strassen(resultadoA, b22, m5, novoTamanho); // m5 = (a11+a12) * (b22)	

            subtracao(a21, a11, resultadoA, novoTamanho); // a21 - a11
            soma(b11, b12, resultadoB, novoTamanho); // b11 + b12
            strassen(resultadoA, resultadoB, m6, novoTamanho); // m6 = (a21-a11) * (b11+b12)

            subtracao(a12, a22, resultadoA, novoTamanho); // a12 - a22
            soma(b21, b22, resultadoB, novoTamanho); // b21 + b22
            strassen(resultadoA, resultadoB, m7, novoTamanho); // m7 = (a12-a22) * (b21+b22)

        //Calculando c21, c21, c11 e c22:

            soma(m3, m5, c12, novoTamanho); // c12 = m3 + m5
            soma(m2, m4, c21, novoTamanho); // c21 = m2 + m4
            
            soma(m1, m4, resultadoA, novoTamanho); // m1 + m4
            subtracao(resultadoA, m5, resultadoB, novoTamanho); // m1 + m4 - m5
            soma(resultadoB, m7, c11, novoTamanho); // c11 = m1 + m4 - m5 + m7

            subtracao(m1, m2, resultadoA, novoTamanho); // m1 - m2
            soma(resultadoA, m3, resultadoB, novoTamanho); // m1 - m2 + m3
            soma(resultadoB, m6, c22, novoTamanho); // c22 = m1 + m3 - m2 + m6

        //Passar resultados para a matriz c
            for (int i = 0; i < novoTamanho ; i++) {
                for (int j = 0 ; j < novoTamanho ; j++) {
                    C[i][j] = c11[i][j];
                    C[i][j + novoTamanho] = c12[i][j];
                    C[i + novoTamanho][j] = c21[i][j];
                    C[i + novoTamanho][j + novoTamanho] = c22[i][j];
                }
            }


            // liberar memoria
        a11 = liberarMemoria(a11, novoTamanho);
        a12 = liberarMemoria(a12, novoTamanho);
        a21 = liberarMemoria(a21, novoTamanho);
        a22 = liberarMemoria(a22, novoTamanho);

        b11 = liberarMemoria(b11, novoTamanho);
        b12 = liberarMemoria(b12, novoTamanho);
        b21 = liberarMemoria(b21, novoTamanho);
        b22 = liberarMemoria(b22, novoTamanho);

        c11 = liberarMemoria(c11, novoTamanho);
        c12 = liberarMemoria(c12, novoTamanho);
        c21 = liberarMemoria(c21, novoTamanho);
        c22 = liberarMemoria(c22, novoTamanho);

        m1 = liberarMemoria(m1, novoTamanho);
        m2 = liberarMemoria(m2, novoTamanho);
        m3 = liberarMemoria(m3, novoTamanho);
        m4 = liberarMemoria(m4, novoTamanho);
        m5 = liberarMemoria(m5, novoTamanho);
        m6 = liberarMemoria(m6, novoTamanho);
        m7 = liberarMemoria(m7, novoTamanho);
        resultadoA = liberarMemoria(resultadoA, novoTamanho);
        resultadoB = liberarMemoria(resultadoB, novoTamanho);
    }
}
//--------------------------------------------------------------




int main(void) {

    int **A;
    int **B;
    int **C; 

    // Procura pela proxima potencia de dois maior que o tamanho da matriz
    int potencia = 1;
    while(potencia < N)
        potencia *= 2;

    srand(time(NULL));
    A = alocarMatrixInicial(N,potencia);
    B = alocarMatrixInicial(N,potencia);
    C = alocarMatrix(potencia);

    //-------------------------------------------------------
    //Imprime matrizes geradas aleatoriamente
    //Comentar para matrizes grandes
/*
    printf("\nMatrix A \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", A[i][j]);
            printf("\n");
    }

    printf("\nMatrix B \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", B[i][j]);
            printf("\n");
    }
*/
    //--------------------------------------------------------

    //Multiplicacao normal
    clock_t tempo = clock();
    multiplica(A,B,C,N);
    tempo = clock() - tempo;
    double tempoExecucao = (double)(tempo) / CLOCKS_PER_SEC;
    printf("\nTempo gasto multiplicacao normal %f\n", tempoExecucao);
    /*
    printf("Matrix resultante \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", C[i][j]);
            printf("\n");
    }
*/
    //---------------------------------------------------------------------------


    //Multiplicacao Strassen
    clock_t tempo2 = clock();
    strassen(A,B,C,potencia);
    tempo2 = clock() - tempo2;
    double tempoExecucao2 = (double)(tempo2) / CLOCKS_PER_SEC;
    printf("\nTempo gasto multiplicacao strassen %f\n", tempoExecucao2);
   /* 
    printf("Matrix resultante \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", C[i][j]);
            printf("\n");
    }
*/
    //--------------------------------------------------------------------------
}



