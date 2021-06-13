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
int fibPD(int n) {
    std::vector<int> res;
    res.push_back(1); //0 -> 1
    res.push_back(1); //1 -> 1
    for (int i = 0; i <= n; i++) {
        res.push_back(fib(i - 1) + fib(i - 2));
    }
    return res.back();
}

int main() {
    int n = 3;

    // 1 b)
    // sequencia de fibinacci, sem a utilziação de programação dinamica
    std::cout << "Fibonacci Recursivo de " << n << ": " << fib(n) << std::endl;

    //1 c)
    // sequencia de fibinacci, com a utilziação de programação dinamica
    std::cout << "Fibonacci Programação Dinamica de " << n << ": " << fibPD(n) << std::endl;


    // 1d) Implemente um algoritmo para o problema do troco (Change-making problem(Se ̧c ̃ao 8.1))utilizando programa ̧c ̃ao dinˆamica.
    std::cout << "\n\n" << endl;
    std::cout << "Algoritmo para o problema do troco:" << endl;
    n = 6;
    std::vector<int> v = {1, 3, 4};
    int coin = 6;
    int m = 3;


    std::cout << "Quantidade de coin: " << n << endl;
    std::cout << "Coins Denominations: [ ";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << ' ';
    }
    std::cout << "]"<< endl;
    std::cout << "Num mínimo de moedas esperado: " << change_Making(n, v) << "\n";


//
//        std::cout << "\nAmount of: " << change_amount << "\n";
//        std::cout << "The minimum number of coins required to get desired change:  "
//                  << Change_Making(input, m, change_amount) << "\n";

    return 0;
}
