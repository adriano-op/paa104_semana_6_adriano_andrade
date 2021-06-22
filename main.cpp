#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <random>
#include<stdio.h>
#include<math.h>
#include <climits>
#include <cstdlib>

#include <locale.h>
#include <cstring>
#include <ctime>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;


//chessboard
int board[100][100];

//std::vector<std::vector<int>> board;
//function to check if the cell is attacked or not
int is_attack(int i, int j, int N) {
    int k, l;
    //checking if there is a queen in row or column
    for (k = 0; k < N; k++) {
        if ((board[i][k] == 1) || (board[k][j] == 1))
            return 1;
    }
    //checking for diagonals
    for (k = 0; k < N; k++) {
        for (l = 0; l < N; l++) {
            if (((k + l) == (i + j)) || ((k - l) == (i - j))) {
                if (board[k][l] == 1)
                    return 1;
            }
        }
    }
    return 0;
}

int N_queen(int n) {
    int i, j;
    //if n is 0, solution found
    if (n == 0)
        return 1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            //checking if we can place a queen here or not
            //queen will not be placed if the place is being attacked
            //or already occupied
            if ((!is_attack(i, j, n)) && (board[i][j] != 1)) {
                board[i][j] = 1;
                //recursion
                //wether we can put the next queen with this arrangment or not
                if (N_queen(n - 1) == 1) {
                    return 1;
                }
                board[i][j] = 0;
            }
        }
    }
    return 0;
}

// Aplica programação dinâmica para encontrar o número mínimo de moedas // de denominações d1 <d2 <... <dm
// onde d1 = 1 que somam // um determinado montanten
// Entrada: Número inteiro positivo e matrizD [1..m ] de números inteiros positivos crescentes
// indicando as denominações das moedas, onde D [1] = 1
// Saída: O número mínimo de moedas que somam toneladas
int change_Making(int N, std::vector<int> m) {
    int M = m.size();
    int dp[N + 1];
    dp[0] = 0;

    // sub-problemas
    for (int i = 1; i <= N; i++) {
        dp[i] = INT_MAX;

        for (int j = 0; j < M; j++) {
            if (i - m[j] >= 0) {
                dp[i] = min(dp[i], dp[i - m[j]] + 1);
            }
        }
    }

    // solução
    return dp[N];
}

//exercicios 2-B)
// fibonnaci recursivo, sem o uso de programação dinamica
int fib(int n) {
    if (n == 0) {
        return 1;
    }

    if (n <= 2) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);

}

//exercicios 2-C)
// fibonnaci recursivo, com o uso de programação dinamica
int fibPD_bottom_up(int n) {
    std::vector<int> res;
    res.push_back(0); //0 -> 1
    res.push_back(1); //1 -> 1
    for (int i = 2; i <= n; i++) {
        res.push_back(fib(i - 1) + fib(i - 2));
    }
    return res[n];
}


int peso[5] = {0, 2, 1, 3, 2};
int valor[5] = {0, 12, 10, 20, 15};
int F[5][6];


//O tempo necessário para encontrar a composição de uma solução ótima é em O (n).
int MFKnapsack(int i, int j) {
    if (F[i][j] < 0) {
        int capacidade = 0;
        if (j < peso[i])
            capacidade = MFKnapsack(i - 1, j);
        else
            capacidade = max(MFKnapsack(i - 1, j), valor[i] + MFKnapsack(i - 1, j - peso[i]));
        F[i][j] = capacidade;
    }
    return F[i][j];
}


int coinCollectionPD(int n, int m, std::vector<std::vector<int>> &C) {
    int F[n][m];
    F[0][0] = C[0][0];
    F[1][1] = C[1][1];
    for (int k = 2; k < m; k++) {
        F[1][k] = F[1][k - 1] + C[1][k];
    }
    for (int i = 2; i < n; i++) {
        F[i][1] = F[i - 1][1] + C[i][0];
        for (int j = 2; j < m; ++j) {
            F[i][j] = std::max(F[i - 1][j], F[i][j - 1]) + C[i][j];
        }
    }

    return F[n][m];
}




int CoinCollecting_recursivo(int m, int n, std::vector<std::vector<int>> a) {
    int c[m][n];
    c[0][0] = a[0][0];

    for( int i = 1; i<m; i++){
        c[i][0] = c[i - 1][0] + a[i][0];
    }
    for( int j = 1; j < n; j++){
        c[0][j] = c[0][j - 1] + a[0][j];
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
                c[i][j] = max(c[i - 1][j], c[i][j - 1]) + a[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            std::cout <<  c[i][j] << " ";
        std::cout << endl;
    }
    return c[m - 1][n - 1];
}


int main() {

    // // 1 b)  Implemente  um  algoritmo  para  o  cálculo  do n-éesimo  número  de  Fibonacci  sem  utilizar programação dinâmica.
//    int n = 3;
//    std::cout << "Fibonacci Recursivo de " << n << ": " << fib(n) << std::endl;


//---------------------------------------------------------------------------------------------------------------------

//    //1 c)  Implemente  um  algoritmo  para  o  cálculo  do n-éesimo  número  de  Fibonacci  com  utilizar programação dinâmica.
//    // sequencia de fibinacci, com a utilziação de programação dinamica
//    std::cout << "Fibonacci Programação Dinamica de " << n << ": " << fibPD_bottom_up(n) << std::endl;

//-----------------------------------------------------------------------------------------------------------------
//    // 1d) Implemente um algoritmo para o problema do troco (Change-making problem(Seção 8.1)
//    // utilizando programação dinâmica.

//    std::cout << "\n\n" << endl;
//    std::cout << "Algoritmo para o problema do troco:" << endl;
//    int n = 6;
//    std::vector<int> v = {1, 3, 4};
//    int coin = 6;
//    int m = 3;

//    std::cout << "Quantidade de coin: " << n << endl;
//    std::cout << "Coins Denominations: [ ";
//    for (size_t i = 0; i < v.size(); i++) {
//        std::cout << v[i] << ' ';
//    }
//    std::cout << "]" << endl;
//    std::cout << "Num mínimo de moedas esperado: " << change_Making(n, v) << "\n";

//-----------------------------------------------------------------------------------------------------------------

//    //1 e)  Implemente um algoritmo para o problema de coleta de moedas (Coin-collecting problem(Seção 8.1)
//    // utilizando programação dinâmica.
//
//    std::vector<std::vector<int>> b =
//            {{0, 1, 0, 1, 0, 0},
//             {1, 0, 0, 1, 1, 0},
//             {0, 1, 0, 1, 1, 0},
//             {0, 0, 0, 1, 0, 1},
//             {1, 1, 1, 0, 1, 0}};
//    std::cout << "coinCollectionPD: " << coinCollectionPD(5, 6, b) << endl;
//    std::cout << endl;

//----------------------------------------------------------------------------------------------------------------------

// 1 f)  Implemente um algoritmo para o problema de coleta de moedas (Coin-collecting problem(Se ̧c ̃ao 8.1))
    // sem utilizar programação dinãmica.

//    std::vector<std::vector<int>> a =
//            {{0, 1, 0, 1, 0, 0},
//             {1, 0, 0, 1, 1, 0},
//             {0, 1, 0, 1, 1, 0},
//             {0, 0, 0, 1, 0, 1},
//             {1, 1, 1, 0, 1, 0}};
//
//    std::cout << "CoinCollecting: "<<endl ;
//    std::cout <<"Num coins: " << CoinCollecting_recursivo(5, 6, a);
//    std::cout << endl;

    //-----------------------------------------------------------------------------------------------------------------
    // 1 g) Implemente o algoritmo baseado em função de memória (memory function) para solução do problema da mochila (knapsack problem).
    // F -> armazena os valores
    // Variáveis globais peso[1..n], Value[1..n],

//    for (int i = 1; i < 5; i++)
//        for (int j = 1; j < 6; j++)
//            F[i][j] = -1;
//    std::cout <<"MFKnapsack: "<< MFKnapsack(4, 5);

//--------------------------------------------------------------------

//taking the value of N
//    int N;
//    std::cout << "Enter the value of N for NxN chessboard: ";
//    std::cin >> N;
//
//    //inicializa o vetor com 0
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            board[i][j] = 0;
//        }
//    }
//
//
//
//    //  N_queen(N);
//
//    //imprimir a  matix
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++)
//            std::cout << board[i][j] << " ";
//        std::cout << endl;
//    }


    return 0;
}
