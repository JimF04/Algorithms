#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

// Algoritmo lineal O(n) - suma máxima de una subsecuencia contigua en un arreglo
int maxSubarraySum(const vector<int>& array) {
    int n = array.size();
    int maxEndingHere = 0;
    int maxSoFar = INT_MIN;

    for (int i = 0; i < n; ++i) {
        maxEndingHere = max(array[i], maxEndingHere + array[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }

    return maxSoFar;
}

// Algoritmo cuadrático O(n^2)
long cuadraticAlgorithm(const vector<int>& array) {
    int n = array.size();
    int result;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result = array[i] * array[j];
        }
    }
    return result;
}

// Algoritmo lineal logarítmico O(n log n) - Quicksort
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

// Algoritmo exponencial O(2^n) - suma máxima de una subsecuencia
int maxSubsequenceSum(const vector<int>& array) {
    int n = array.size();
    int maxSum = INT_MIN;

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

int main() {
    vector<int> sizes = {100, 1000, 10000, 100000, 1000000};

    cout << "Complejidad lineal (O(n)):" << endl;
    for (int size : sizes) {
        // Crear un vector con números negativos para evaluar el peor caso
        vector<int> array(size, -1000); // Todos los elementos son -1000

        auto start = chrono::steady_clock::now();
        maxSubarraySum(array);
        auto end = chrono::steady_clock::now();
        long duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        cout << "Size: " << size << ", Time: " << duration << " ns" << endl;
    }

    cout<<endl;

    vector<int> cuadratic = {100, 1000, 10000, 50000, 100000};

    cout << "Complejidad cuadratica (O(n^2)):" << endl;
    for (int size : cuadratic) {
        vector<int> array(size, 1);

        auto start = chrono::steady_clock::now();
        cuadraticAlgorithm(array);
        auto end = chrono::steady_clock::now();
        long duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        cout << "Size: " << size << ", Time: " << duration << " ns" << endl;
    }

    cout << "\nComplejidad lineal logaritmica (O(n log n)):" << endl;
    for (int size : sizes) {
        vector<int> array(size);
        srand(time(nullptr));
        for (int i = 0; i < size; ++i) {
            array[i] = rand() % size;
        }

        auto start = chrono::steady_clock::now();
        int n = array.size();
        quicksort(array, 0, n - 1);
        auto end = chrono::steady_clock::now();
        long duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        cout << "Size: " << size << ", Time: " << duration << " ns" << endl;
    }

    cout << "\nComplejidad logaritmica (O(log n)):" << endl;
    for (int size : sizes) {
        vector<int> array(size);
        for (int i = 0; i < size; ++i) {
            array[i] = i;
        }

        auto start = chrono::steady_clock::now();
        binarySearch(array, size - 1); // Buscar el último elemento
        auto end = chrono::steady_clock::now();
        long duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

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

        auto start = chrono::steady_clock::now();
        maxSubsequenceSum(array);
        auto end = chrono::steady_clock::now();
        long duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        cout << "Size: " << size << ", Time: " << duration << " ns" << endl;
    }


    return 0;
}
