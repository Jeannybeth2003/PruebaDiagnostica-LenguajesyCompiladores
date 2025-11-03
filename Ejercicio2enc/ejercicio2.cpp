#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

// Función para generar el triángulo de Pascal
void generarTrianguloPascal(int n, std::vector<int>& coeficientes) {
    coeficientes.resize(n + 1);
    coeficientes[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        coeficientes[i] = 1;
        for (int j = i - 1; j > 0; j--) {
            coeficientes[j] = coeficientes[j] + coeficientes[j - 1];
        }
    }
}

// Función para mostrar el polinomio
void mostrarPolinomio(int n, const std::vector<int>& coeficientes) {
    std::cout << "(x+1)^" << n << " = ";
    for (int i = n; i >= 0; i--) {
        if (coeficientes[i] != 0) {
            if (i != n) std::cout << " + ";
            if (coeficientes[i] != 1 || i == 0) {
                std::cout << coeficientes[i];
            }
            if (i > 0) {
                std::cout << "x";
                if (i > 1) {
                    std::cout << "^" << i;
                }
            }
        }
    }
    std::cout << std::endl;
}

// Función para calcular el valor del polinomio para un x dado
long long calcularPolinomio(int n, int x, const std::vector<int>& coeficientes) {
    long long resultado = 0;
    std::cout << "Cálculo para x = " << x << ":" << std::endl;
    
    for (int i = n; i >= 0; i--) {
        if (coeficientes[i] != 0) {
            long long termino = coeficientes[i];
            for (int j = 0; j < i; j++) {
                termino *= x;
            }
            resultado += termino;
            
            if (i < n) {
                std::cout << " + ";
            }
            if (coeficientes[i] != 1 || i == 0) {
                std::cout << coeficientes[i];
            }
            if (i > 0) {
                std::cout << "x";
                if (i > 1) {
                    std::cout << "^" << i;
                }
            }
        }
    }
    std::cout << " = " << resultado << std::endl;
    return resultado;
}

int main() {
    int n = 100;
    std::vector<int> coeficientes;
    clock_t inicio, fin;
    
    // Medir tiempo de generación del triángulo de Pascal
    inicio = clock();
    generarTrianguloPascal(n, coeficientes);
    fin = clock();
    
    // Mostrar el polinomio
    mostrarPolinomio(n, coeficientes);
    
    // Calcular y mostrar el resultado para x = 2
    calcularPolinomio(n, 2, coeficientes);
    
    // Mostrar tiempo de ejecución
    std::cout << "\nTiempo de ejecución: " << (fin - inicio) / (double)CLOCKS_PER_SEC << " segundos" << std::endl;
    
    // Guardar resultados en archivo
    std::ofstream archivo("resultado.txt");
    if (archivo.is_open()) {
        archivo << "Tiempo de ejecución: " << (fin - inicio) / (double)CLOCKS_PER_SEC << " segundos\n\n";
        archivo << "Polinomio (x+1)^" << n << ":\n";
        mostrarPolinomio(n, coeficientes);
        archivo << "\nResultado para x = 2:\n";
        calcularPolinomio(n, 2, coeficientes);
        archivo.close();
        std::cout << "\nResultados guardados en 'resultado.txt'" << std::endl;
    } else {
        std::cout << "No se pudo abrir el archivo para escritura" << std::endl;
    }
    
    return 0;
}
