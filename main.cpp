#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

// Algoritmo cuadrático O(n^2)
long long cuadraticAlgorithm(const vector<int>& array) {
    auto start = chrono::steady_clock::now();
    int n = array.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Operación ficticia para ilustrar la complejidad cuadrática
            int result = array[i] * array[j];
        }
    }
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

// Algoritmo lineal logarítmico O(n log n) - Implementación de quicksort
void quicksort(vector<int>& array, int low, int high) {
    if (low < high) {
        int pivot = array[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (array[j] <= pivot) {
                ++i;
                swap(array[i], array[j]);
            }
        }
        swap(array[i + 1], array[high]);
        int partitionIndex = i + 1;
        quicksort(array, low, partitionIndex - 1);
        quicksort(array, partitionIndex + 1, high);
    }
}

long long nLogNAlgorithm(vector<int>& array) {
    auto start = chrono::steady_clock::now();
    int n = array.size();
    quicksort(array, 0, n - 1);
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

// Algoritmo logarítmico O(log n) - Búsqueda binaria
int binarySearch(const vector<int>& array, int target) {
    int low = 0;
    int high = array.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (array[mid] == target) {
            return mid;
        } else if (array[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

long long logAlgorithm(const vector<int>& array, int target) {
    auto start = chrono::steady_clock::now();
    binarySearch(array, target);
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

// Función para encontrar la suma máxima de una subsecuencia
int maxSubsequenceSum(const vector<int>& array) {
    int n = array.size();
    int maxSum = INT_MIN;

    // Iterar sobre todas las posibles subsecuencias
    for (int i = 0; i < (1 << n); ++i) {
        int currentSum = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                currentSum += array[j];
            }
        }
        maxSum = max(maxSum, currentSum);
    }

    return maxSum;
}

// Función para calcular el tiempo de ejecución del algoritmo exponencial
long long exponentialAlgorithm(const vector<int>& array) {
    auto start = chrono::steady_clock::now();
    maxSubsequenceSum(array);
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

int main() {
    vector<int> sizes = {100, 1000, 10000, 100000, 1000000};

//    vector<int> cuadratic = {100, 1000, 10000, 50000, 100000};
//
//    cout << "Complejidad cuadrática (O(n^2)):" << endl;
//    for (int size : cuadratic) {
//        vector<int> array(size, 1); // Crear un vector de tamaño 'size' con todos los elementos inicializados a 1
//        long long duration = cuadraticAlgorithm(array);
//        cout << "Size: " << size << ", Time: " << duration << " ns" << endl;
//    }

    cout << "\nComplejidad lineal logaritmica (O(n log n)):" << endl;
    for (int size : sizes) {
        vector<int> array(size);
        // Llenar el vector con números aleatorios (no es relevante para el análisis de complejidad)
        srand(time(nullptr));
        for (int i = 0; i < size; ++i) {
            array[i] = rand() % size;
        }
        long long duration = nLogNAlgorithm(array);
        cout << "Size: " << size << ", Time: " << duration << " ns" << endl;
    }

    cout << "\nComplejidad logaritmica (O(log n)):" << endl;
    for (int size : sizes) {
        // Crear un vector ordenado del peor caso para la búsqueda binaria
        vector<int> array(size);
        for (int i = 0; i < size; ++i) {
            array[i] = i;
        }
        long long duration = logAlgorithm(array, size - 1); // Buscar el último elemento en el vector
        cout << "Size: " << size << ", Time: " << duration << " ns" << endl;
    }

    cout<<endl;

    vector<int> exponential = {5, 10, 15, 20, 25};
    cout << "Complejidad exponencial (O(2^n)):" << endl;
    for (int size : exponential) {
        // Crear un vector con números crecientes para evaluar peor caso
        vector<int> array(size);
        for (int i = 0; i < size; ++i) {
            array[i] = i + 1;
        }

        long long duration = exponentialAlgorithm(array);
        cout << "Size: " << size << ", Time: " << duration << " ns" << endl;
    }


    return 0;
}
