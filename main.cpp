#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <fstream>  // ifstream
#include <sstream>  // stringstream
#include <iomanip>  // setw
#include <string>
#include<math.h>
#include <bits/stdc++.h>

using namespace std;

#include <matplot/matplot.h>


template<class T>
void printVetor(std::vector<T> &v);

void printSolution(vector<vector<int>> &Matrix) {
    for (vector<int> linha : Matrix) {
        for (int val : linha)
            cout << setw(4) << val << "  ";
        cout << endl;
    }
}

//Função do Marco
vector<vector<int>> readMatrix(string tsp_file, int nhead, int nnodes) {
    /* Lê arquivo tsp com matriz de distãncia entre cidades
    * ENTRADAS:
    * String com nome do arquivo
    * Inteiro nhead com número de linhas do cabeçalho (serão ignoradas)
    * Inteiro nnodes com tamanho da matriz (número de nós ou cidades)
    * SAÍDA:
    * Matriz nnodes x nnodes
    */

    // Cria matriz nnodes x nnodes preenchida com zeros
    vector<vector<int>> matrix(nnodes, vector<int>(nnodes, 0));

    // Recebe as linhas lidas
    string line;

    // Contador que indica a linha atual do arquivo
    int linecount = 0;

    // Linha da matriz e coluna inicial (ncol = nline + 1)
    int nline, ncol;

    // Valor auxiliar
    int val;

    // Stream do arquivo
    ifstream inputFile(tsp_file);

    while (inputFile) {
        // Pega uma linha
        getline(inputFile, line);

        // Atualiza linha atual
        linecount += 1;

        // Se linha atual for maior que cabeçalho e menor ou igual ao total
        if (linecount > nhead and linecount <= nhead + nnodes) {

            // Linha da matriz: linha atual - tamanho do cabeçalho -1
            nline = linecount - nhead - 1;
            ncol = nline + 1;

            // Itera os valores da linha
            stringstream stream(line);
            while (stream >> val) {
                // Acrescenta cada valor na matriz e incrementa a coluna
                matrix[ncol][nline] = val;
                matrix[nline][ncol] = val;
                ncol++;
            }
        }
    }

    return matrix;
}

// Função para verificar se o vértice v pode ser adicionado no grafo construído
bool zonaSeguraCicloHamiltoniano(int v, std::vector<std::vector<bool>> &grafo, std::vector<int> &caminho, int pos) {
    // Verificando se o vértice é adjacente.
    if (grafo[caminho[pos - 1]][v] == 0) {
        return false;
    }

    // Verificando se o vértice já foi incluído.
    for (int i = 0; i < pos; i++) {
        if (caminho[i] == v) {
            return false;
        }
    }
    return true;
}

// Função auxiliar para ajudar a resolver o problema do ciclo hamiltoniano
bool cicloHamiltonianoAux(std::vector<std::vector<bool>> &grafo, std::vector<int> &caminho, int pos) {
    // caso base: se todos os vértices forem   incluído no ciclo hamiltoniano
    if (pos == grafo.size()) {
        // E se houver uma vantagem do último vértice incluído para o primeiro vértice
        if (grafo[caminho[pos - 1]][caminho[0]] == 1) {
            return true;
        } else {
            return false;
        }
    }

    //  vértices diferentes como um próximo candidato no ciclo hamiltoniano. Não tentamos 0, como incluímos 0 como ponto de partida
    for (int v = 1; v < grafo.size(); v++) {
        // Verificando se este vértice pode ser adicionado no ciclo hamiltoniano
        if (zonaSeguraCicloHamiltoniano(v, grafo, caminho, pos)) {
            caminho[pos] = v;
            // Para construir o resto do caminho
            if (cicloHamiltonianoAux(grafo, caminho, pos + 1) == true)
                return true;
            // Se o vértice adicionado não levar a uma solução,  então será removido
            caminho[pos] = -1;
        }
    }
    return false;
}

void cicloHamiltoniano(std::vector<std::vector<bool>> &grafo) {
    std::vector<int> caminho;
    for (int i = 0; i < grafo[0].size(); i++)
        caminho.push_back(-1);

    /* vértice 0 como o primeiro vértice do caminho.
     Mesmo havendo um ciclo hamiltoniano, o caminho pode começar a partir de qualquer ponto, pois o grafo não é direcionado */
    caminho[0] = 0;
    if (cicloHamiltonianoAux(grafo, caminho, 1) == true) {
        printVetor(caminho);
    } else {
        cout << " Grafo sem solução :( " << endl;
    }
}

/* Uma função para verificar se a atribuição de cor atual é seguro para o vértice, ou seja, verifica se a aresta existe ou não
(ou seja, gráfico [vertice] [i] == 1). Se existir, então verifica se a cor
ser preenchida no novo vértice (c é enviado no parâmetro) já está usado por seus vértices adjacentes
 (i -> vértices adj) ou não (ou seja, cor [i] == c)*/
bool zonaSeguraColoracaoGrafo(int vertice, std::vector<std::vector<bool>> &grafo, std::vector<int> &vetorCor, int c) {
    for (int i = 0; i < grafo.size(); i++) {
        if (grafo[vertice][i] && c == vetorCor[i]) {
            return false;
        }
    }
    return true;
}

/* Utilizada como auxiliar para resolver o problema de m coloração */
bool coloracaoGrafoAux(std::vector<std::vector<bool>> &grafo, int qtidadeCor, std::vector<int> &vetorCor, int vertice) {
    /* caso base: se todos os vértices tiverem uma cor, então retorna true */
    if (vertice == grafo[0].size())
        return true;

    for (int i = 1; i <= qtidadeCor; i++) {
        /* Verifica se a cor pode ser adicionada, caso contrario, nao será inserida */
        if (zonaSeguraColoracaoGrafo(vertice, grafo, vetorCor, i)) {
            vetorCor[vertice] = i;

            /* atribui cores ao restante do vértice */
            if (coloracaoGrafoAux(grafo, qtidadeCor, vetorCor, vertice + 1) == true)
                return true;

            /*Se uma cor não tiver a uma solução, então é removida */
            vetorCor[vertice] = 0;
        }
    }

    return false;
}


/* Esta função resolve o problema de Colorir grafos usando Backtracking.
        Usa a função auxiliar para resolver o problema.
        Retorna falso se as cores não puderem ser atribuídas, caso contrário, retorne verdadeiro e
        imprime atribuições de cores para todos os vértices.
        Havendo uma solução, esta função imprime  */
void coloracaoGrafo(std::vector<std::vector<bool>> &grafo, int qtidadeCor) {
    // Inicializa todos os valores de cor = 0.
    std::vector<int> cor;
    for (int i = 0; i < grafo.size(); i++)
        cor.push_back(0);

    if (coloracaoGrafoAux(grafo, qtidadeCor, cor, 0) == false) {
        cout << " Grafo sem solução :( " << endl;
    } else {
        cout << "Coloração do grafo: ";
        printVetor(cor);
    }
}


template<class T>
void printVetor(std::vector<T> &v) {
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::cout << *i << " | ";
    }
    std::cout << endl;
}

template<class T>
void printmatriz(std::vector<std::vector<T>> &matriz) {
    for (std::vector<T> p: matriz) {
        for (auto i = p.begin(); i != p.end(); ++i) {
            std::cout << *i << " | ";
        }
        std::cout << endl;
    }
}

// É uma função para verificar se a v[i, j] está sob ataque de alguma rainha.
// Verifica se existe uma outra rainha na posição v[i,j] e nas diagonais.
// Qualquer v[k, l] será diagonal à v[i, j], se k + l for igual a i + j ou k-l for igual a i-j.

int rainhaEstaSofrendoAtaque(std::vector<std::vector<int>> &tabuleiro, int i, int j, int tamanho_quadro) {
    int k, l;
// verifica se há uma rainha na linha ou coluna
    for (k = 0; k < tamanho_quadro; k++) {
        if ((tabuleiro[i][k] == 1) || (tabuleiro[k][j] == 1))
            return 1;
    }
// verificando as diagonais
    for (k = 0; k < tamanho_quadro; k++) {
        for (l = 0; l < tamanho_quadro; l++) {
            if (((k + l) == (i + j)) || ((k - l) == (i - j))) {
                if (tabuleiro[k][l] == 1)
                    return 1;
            }
        }
    }
    return 0;
}

int n_rainhas(std::vector<std::vector<int>> &tabuleiro, int num_rainhas, int tamanho_quadro) {
    int i, j;
    // Caso base: se num_rainhas for 0, solução encontrada.
    //Se não houver mais rainha, isso significa que todas as rainhas foram colocadas e temos uma solução.
    if (num_rainhas == 0)
        return 1;
    for (i = 0; i < tamanho_quadro; i++) {
        for (j = 0; j < tamanho_quadro; j++) {
            // verificando se podemos colocar uma rainha aqui ou não.
            // a rainha não será colocada se o local ja estiver sendo atacado ou já ocupado
            if ((!rainhaEstaSofrendoAtaque(tabuleiro, i, j, tamanho_quadro)) && (tabuleiro[i][j] != 1)) {
                tabuleiro[i][j] = 1;
                // se podemos colocar a próxima rainha no tabuleiro
                if (n_rainhas(tabuleiro, num_rainhas - 1, tamanho_quadro) == 1) {
                    return 1;
                }
                tabuleiro[i][j] = 0;
            }
        }
    }
    return 0;
}


// Aplicar a  programação dinâmica para encontrar o número mínimo de moedas de denominações d1 <d2 <... <dm
// onde d1 = 1 que somam um determinado montante n
// Entrada: Número inteiro positivo e matriz [1..valor_moeda ] de números inteiros positivos crescentes
// indicando as denominações das moedas, onde D [1] = 1
// Saída: O número mínimo de moedas
int change_MakingPD(int qtidade_moeda, std::vector<int> valor_moeda) {
    int tamVetorValorMoeda = valor_moeda.size();
    std::vector<int> temp(qtidade_moeda + 1);
    temp[0] = 0;

    // sub-problemas
    for (int i = 1; i <= qtidade_moeda; i++) {
        temp[i] = INT_MAX;
        for (int j = 0; j < tamVetorValorMoeda; j++) {
            if (i - valor_moeda[j] >= 0) {
                temp[i] = min(temp[i], temp[i - valor_moeda[j]] + 1);
            }
        }
    }
    // solução
    return temp[qtidade_moeda];
}

int change_MakingR(std::vector<int> array_valor_moeda, int tamVetor, int qtidade_moeda) {
    //caso base
    if (qtidade_moeda == 0) {
        return 0;
    }

    if (qtidade_moeda < 0) {
        return INT_MAX;
    }

// inicializa o número mínimo de moedas necessárias ao infinito
    int num_coins = INT_MAX;

    for (int i = 0; i < tamVetor; i++) {
        // volte a verificar se o total pode ser alcançado incluindo
        // moeda atual `array_valor_moeda [i]`
        int result = change_MakingR(array_valor_moeda, tamVetor, qtidade_moeda - array_valor_moeda[i]);

        // atualiza o número mínimo de moedas necessárias se escolher o atual
        // moeda resultou em uma solução
        if (result != INT_MAX) {
            num_coins = min(num_coins, result )+1;
        }
    }
   return num_coins;
}


//exercicios 2-B)
// fibonnaci recursivo, sem o uso de programação dinamica
int fibonacci_recursivo(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
}

int fib_Iterativo(int n) {
    std::vector<int> res;
    res.push_back(0);
    res.push_back(1);
    for (int i = 2; i <= n; i++) {
        res.push_back(res[i - 1] + res[i - 2]);
    }
    return res[n];
}

//exercicios 2-C)
//    //Na abordagem “bottom-up” , a solução ótima começa a ser calculada a partir do subproblema mais trivial.
//    // No caso da série de Fibonacci, basta entender que para se calcular o termo na resolução sempre inicia pelo fib(0), depois fib(1), fib(2)
//    // e assim sucessivamente até chegar em fib(n).

int fib_ProgDinam_bottom_up(int n) {
    std::vector<int> res;
    res.push_back(0); //0 -> 0
    res.push_back(1); //1 -> 1
    for (int i = 2; i <= n; i++) {
        res.push_back(fib_ProgDinam_bottom_up(i - 1) + fib_ProgDinam_bottom_up(i - 2));
    }
    return res[n];
}

//   // Na abordagem “top-down” (ou memoization), partimos da solução geral ótima que se deseja encontrar e, então,
//   // analisa-se quais subproblemas são necessários resolver até que se chegue em um subproblema com resolução trivial.
//   // Ao longo dos cálculos os resultados são armazenados para que sejam reutilizados.
//   // Dessa forma, o algoritmo observa primeiramente na tabela se a solução ótima do subproblema já foi computado.
//   // Caso positivo, simplesmente extrai o valor. Caso negativo, resolve e salva o resultado na tabela.
//   //Entrada: Número do qual se deseja saber o seu Fibonacci.
//   //Saída: Número na sequencia de Fibonacci correspondente.
int fib_ProgDinam_top_down(int n, std::vector<int> &aux) {
    if (aux[n] != -1) {
        return aux[n];
    } else {
        if (n <= 1) {
            aux[n] = n;
        } else {
            aux[n] = fib_ProgDinam_top_down(n - 1, aux) + fib_ProgDinam_top_down(n - 2, aux);
        }
    }

    return aux[n];
}


std::vector<int> peso = {0, 2, 1, 3, 2};
std::vector<int> valor = {0, 12, 10, 20, 15};
std::vector<std::vector<int>> F(5, std::vector<int>(6));


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

int coinCollectingRecursivo(int i, int j, std::vector<std::vector<int>> &C) {
    if (i == 0 && j == 0) {
        return C[i][j];
    } else if (i == 0) {
        return coinCollectingRecursivo(i, j - 1, C) + C[i][j];
    } else if (j == 0) {
        return coinCollectingRecursivo(i - 1, j, C) + C[i][j];
    } else {
        return std::max(coinCollectingRecursivo(i, j - 1, C), coinCollectingRecursivo(i - 1, j, C)) + C[i][j];
    }
}

int coinCollectingITERATIVO(int m, int n, std::vector<std::vector<int>> &a) {
    int c[m][n];
    if (m == 0 && n == 0) {
        return a[m][n];
    }
    c[0][0] = a[0][0];

    for (int i = 1; i < m; i++) {
        c[i][0] = c[i - 1][0] + a[i][0];
    }
    for (int j = 1; j < n; j++) {
        c[0][j] = c[0][j - 1] + a[0][j];
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            c[i][j] = max(c[i - 1][j], c[i][j - 1]) + a[i][j];
        }
    }

    std::cout << "Tabuleiro CoinCollecting Iterativo: " << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            std::cout << c[i][j] << " ";
        std::cout << endl;
    }
    std::cout << "Num coins: ";

    return c[m - 1][n - 1];
}

std::vector<int> inicializaVectorRandom(int t) {
    unsigned seed = time(0);
    srand(seed);
    vector<int> nums;

    for (int i = 0; i < t; i++) {
        nums.push_back(1 + rand() % 1000);
    }
    return nums;
}

int main() {
    // 1 a)   Para que tipo de problema serve a t ́ecnica de programação dinâmica.?
    //PDF

//    ---------------------------------------------------------------------------------------------------------------------
////     // 1 b)  Implemente  um  algoritmo  para  o  cálculo  do n-ésimo  número  de  Fibonacci  sem  utilizar programação dinâmica.
////     //Entrada: Número do qual se deseja saber o seu Fibonacci.
////     //Saída: Número na sequencia de Fibonacci correspondente.
////            std::cout << "Análise de Recorrencia:  " << std::endl;
////            std::cout << "T(n) = T(n – 1) + T(n – 2) + c " << std::endl;
////            std::cout << "T(0) = T(1) = 1 " << std::endl;
////            std::cout << "T(n) ≈ 2^n " << std::endl;



//            int num_Fibonacci = 6;
//            std::cout << "  ------------------- Algoritmo de Fibonacci Recursivo Bottom UP ------------------- " << std::endl;
//            std::cout << "Número : " << num_Fibonacci << endl;
//            std::cout << "Sequecia de Fibonacci: " << fibonacci_recursivo(num_Fibonacci) << std::endl;

//    std::cout << "Iniciando Teste de Desempenho " << std::endl;

//    std::vector<int> ns({ 5,10,15,20});
//    std::vector<double> time({});
//
//
//    for (int n : ns) {
//        auto start = std::chrono::system_clock::now();
//
//        fibonacci_recursivo(n);
//
//        auto finish= std::chrono::system_clock::now();
//        std::chrono::duration<double> elapsed = finish - start;
//        std::cout << "N = " << n << " : " << elapsed.count() << std::endl;
//
//        time.push_back(elapsed.count());
//    }
//
//    matplot::plot(ns,time, "-s")
//            ->line_width(5)
//            .marker_size(10)
//            .marker_color("g")
//            .marker_face_color({.5,.5,.5});
//
//    matplot::show();




//---------------------------------------------------------------------------------------------------------------------

//    //1 c)  Implemente  um  algoritmo  para  o  cálculo  do qtidade_moeda-éesimo  número  de  Fibonacci  com  utilizar programação dinâmica.

//    std::cout << "  ------------------- Algoritmo de Fibonacci Bottom Up ------------------- " << std::endl;
//    int num_Fibonacci = 6;
//    std::cout << "Número : " << num_Fibonacci << endl;
//    std::cout << "Fibonacci Programação Dinamica Bottom up : " << fib_ProgDinam_bottom_up(num_Fibonacci) << std::endl;
//    std::cout << "Complexidade : O(n)" << endl;


//    std::cout << "  ------------------- Algoritmo de Fibonacci Top Down ------------------- " << std::endl;
// //   int num_Fibonacci = 6;
//    std::vector<int> vetorAux(num_Fibonacci +1, -1);
//    std::cout << "Número : " << num_Fibonacci << endl;
//    std::cout << "Sequecia de Fibonacci: " << fib_ProgDinam_top_down(num_Fibonacci, vetorAux) << std::endl;
//    std::cout << "Complexidade fib_ProgDinam_top_down: O(n)" << endl;
//


//    std::cout << "  ------------------- Algoritmo de Fibonacci Iterativo ------------------- " << std::endl;
//    std::cout << "Complexidade Iterativo: O(n)" << endl;
//    std::cout << "Sequecia de Fibonacci Iterativo: " << fib_Iterativo(num_Fibonacci);




//-----------------------------------------------------------------------------------------------------------------
    // 1d) Implemente um algoritmo para o problema do troco (Change-making problem(Seção 8.1)


    std::vector<int> array_valor_moeda = {1, 2, 4};
    int qtidade_moeda = 6;

    std::cout << "Algoritmo para o problema do troco, com programação dinamica" << endl;
    std::cout << endl;
    std::cout << "Numero mim de moedas PD: " << change_MakingPD(qtidade_moeda, array_valor_moeda) << "\n";


    std::cout << "Numero mim de moedas Recursivo: "
              << change_MakingR(array_valor_moeda, array_valor_moeda.size(), qtidade_moeda) << "\n";




////-----------------------------------------------------------------------------------------------------------------

    //    //1 e)  Implemente um algoritmo para o problema de coleta de moedas (Coin-collecting problem(Seção 8.1)
    //    // utilizando programação dinâmica.

//    std::cout << "Matriz " <<  endl;
//    std::vector<std::vector<int>> b =
//            {{0, 1, 0, 1, 0, 0},
//             {1, 0, 0, 1, 1, 0},
//             {0, 1, 0, 1, 1, 0},
//             {0, 0, 0, 1, 0, 1},
//             {1, 1, 1, 0, 1, 0}};
//    printmatriz(b);
//
//    std::cout << "coinCollection utilizando Programação Dinamica: " << coinCollectionPD(b.size(), b[0].size(), b)
//              << endl;
//
//
//     std::cout << endl;

//----------------------------------------------------------------------------------------------------------------------

    // 1 f)  Implemente um algoritmo para o problema de coleta de moedas (Coin-collecting problem(Seção 8.1)) sem utilizar programação dinãmica

    // resultutado =6
    //        std::vector<std::vector<int>> a =
    //                {{0, 1, 0, 1, 0, 0},
    //                 {1, 0, 0, 1, 1, 0},
    //                 {0, 1, 0, 1, 1, 0},
    //                 {0, 0, 0, 1, 0, 1},
    //                 {1, 1, 1, 0, 1, 0}};


    //resultado =5
//    std::vector<std::vector<int>> a = {{0, 0, 0, 0, 1, 0},
//                                       {0, 1, 0, 1, 0, 0},
//                                       {0, 0, 0, 1, 0, 1},
//                                       {0, 0, 1, 0, 0, 1},
//                                       {1, 0, 0, 0, 1, 0}};
//
//
//    std::cout << "Matriz: " << endl;
//    for (int i = 0; i < a.size() - 1; i++) {
//        for (int j = 0; j < a[0].size() - 1; j++)
//            std::cout << a[i][j] << " ";
//        std::cout << endl;
//    }
//
//    std::cout << "CoinCollecting  Recursivo: " << coinCollectingRecursivo(a.size() - 1, a[0].size() - 1, a);
//
//    std::cout << endl;
//    std::cout << endl;
//   // std::cout << "Tabuleiro CoinCollecting Iterativo: " << endl;
//    std::cout << coinCollectingITERATIVO(a.size(), a[0].size(), a);
//    std::cout << endl;


//-----------------------------------------------------------------------------------------------------------------
////     1 g) Implemente o algoritmo baseado em função de memória (memory function) para solução do problema da mochila (knapsack problem).
////     F -> armazena os valores
////     Variáveis globais peso[1..qtidade_moeda], Value[1..qtidade_moeda],

    //inicializa a matriz com -1.
    //    for (int i = 1; i < F.size(); i++)
    //        for (int j = 1; j < F[0].size(); j++)
    //            F[i][j] = -1;
    //    std::cout << "MFKnapsack: " << MFKnapsack( F.size()-1,F[0].size()-1);

//----------------------------------------------------------------------------------------------------------------------
    // 2 (a)  Descreva a técnica de backtracking
    // PDF

// ----------------------------------------------------------------------------------------------------------------------
    ////2 (b)  Implemente um algoritmo baseado em backtracking para a a resolução do problema das qtidade_moeda-rainhas.
//
//        int tamanho_quadro=8;  //   tamanho do tabuleiro (NxN) ";
//        std::vector<std::vector<int>> quadro(tamanho_quadro, std::vector<int>(tamanho_quadro));
//
//        int qtidade_rainha = tamanho_quadro;
//        n_rainhas(quadro, qtidade_rainha, tamanho_quadro);
//        std::cout << "Algoritmo das N Rainhas " << endl;
//        std::cout << "Número de rainhas:" << qtidade_rainha << endl;
//        std::cout << "Tamanho quadro:" << tamanho_quadro << endl;
//        std::cout << "Disposição: " << endl;
//
//        //imprimir a  matrix
//        for (int i = 0; i < tamanho_quadro; i++) {
//            for (int j = 0; j < tamanho_quadro; j++)
//                std::cout << quadro[i][j] << " ";
//            std::cout << endl;
//        }
// ---------------------------------------------------------------------------------------------------------------------
    //// 2 c)  Implemente  um  algoritmo  baseado  em  backtracking  para  a  a  resolucão  do  problema  decoloração de grafos com m cores.

    ////        O que é algoritmo de m colocaração de grafos Backtracking?
    ////        Neste problema, um gráfico não direcionado é fornecido. Também são fornecidas cores m.
    ////        O problema é descobrir se é possível atribuir nós com m cores diferentes, de forma que dois vértices adjacentes do gráfico não tenham as mesmas cores.
    ////        Se houver uma solução, exiba qual cor é atribuída a qual vértice.
    ////        A partir do vértice 0, tentaremos atribuir cores uma a uma a todos os diferentes nós. Mas antes de atribuir,
    ////        temos que verificar se a cor é segura ou não. Uma cor não é segura se os vértices adjacentes contiverem a mesma cor.

    //    std::vector<std::vector<bool>> grafo = {{0, 1, 1, 1},
    //                                            {1, 0, 1, 0},
    //                                            {1, 1, 0, 1},
    //                                            {1, 0, 1, 0},
    //    };
    //    cout <<"Algoritimo M Coloração Grafo com Backtracking" << endl;
    //    int numeroCorGrafo = 3;
    //    cout << "Número de cores:  " << numeroCorGrafo << endl;
    //    cout << "Tamanho do grafo: " << grafo.size() << endl;
    //    coloracaoGrafo(grafo, numeroCorGrafo);

//----------------------------------------------------------------------------
    //    //(d) Implemente um algoritmo baseado em backtracking que encontre um ciclo hamiltoniano  num grafo
    //
    //    // Um caminho hamiltoniano é um caminho que permite passar por todos os vértices de um grafo G, não repetindo nenhum,
    //    // ou seja, passar por todos uma e uma só vez por cada. Caso esse caminho seja possível descrever um ciclo, este é
    //    // denominado ciclo hamiltoniano (ou circuito hamiltoniano) em G. E, um grafo que possua tal circuito é chamado de
    //    // grafo hamiltoniano.
    //
    //    //Entrada:
    //    //Um grafo [V][V] é a representação de uma matriz de adjacência do grafo.
    //    // Um grafo de valor [i][j] é 1 se houver uma borda direta de i para j, caso contrário, grafo [i][j] é 0.
    //
    //    //Saída:
    //    //um caminho de array [V] que deve conter o Caminho Hamiltoniano. o caminho [i] deve representar o iº vértice no
    //    // caminho hamiltoniano. O código também deve retornar falso se não houver um ciclo hamiltoniano no grafo.



/*
        (0)--(1)--(2)
        | / \ |
        | / \ |
        | / \ |
        (3)-------(4) */
//    std::vector<std::vector<bool>> grafo = {{0, 1, 0, 1, 0},
//                                            {1, 0, 1, 1, 1},
//                                            {0, 1, 0, 0, 1},
//                                            {1, 1, 0, 0, 1},
//                                            {0, 1, 1, 1, 0}};
//
//    std::cout << "Ciclo Hamiltoniano com Backtracking " << endl;
//    std::cout << "Grafo com Ciclo: " << endl;
//    printmatriz(grafo);
//    std::cout << "Ciclo: ";
//
//    cicloHamiltoniano(grafo);
//
//    /*
//    (0)--(1)--(2)
//    | / \ |
//    | / \ |
//    | / \ |
//    (3) (4) */
//    std::vector<std::vector<bool>> grafo2 = {{0, 1, 0, 1, 0},
//                                             {1, 0, 1, 1, 1},
//                                             {0, 1, 0, 0, 1},
//                                             {1, 1, 0, 0, 0},
//                                             {0, 1, 1, 0, 0}};
//
//    std::cout <<  endl;
//    std::cout << "Grafo sem Ciclo: " << endl;
//    printmatriz(grafo);
//    std::cout << "Ciclo: ";
//    cicloHamiltoniano(grafo2);

//----------------------------------------------------------------------------------------------------------------------

// Nome do arquivo
//    string tsp_file = "brazil58.tsp"; // alternativa: gr17
//
//    // Cabeçalho tem 7 linhas, matriz tem 58 cidades (nós)
//    int nhead = 7;
//    int nnodes = 58; // para gr17: 17
//
//    // Lê o arquivo, guarda distâncias em matrix e imprime
//    vector<vector<int>> matrix = readMatrix(tsp_file, nhead, nnodes);
//    printSolution(matrix);
//



    return 0;


}
