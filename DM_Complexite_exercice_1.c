#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000 // Taille du tableau

// Prototypes des fonctions
void fillArrayWithRandomNumbers(int arr[], int size);
void copyArray(int src[], int dest[], int size);
void insertionSortIterative(int arr[], int n, int *exchanges);
void tri_insertion_recursif(int arr[], int n, int *exchanges);
void Tri_fusion_rec(int arr[], int l, int r, int *exchanges);
void quickSort(int arr[], int low, int high, int *exchanges);
void quickSortIterative(int arr[], int low, int high, int *exchanges);
void mergesort(int A[], int temp[], int low, int high, int *exchanges);

void fillArraySorted(int arr[], int size);
void fillArrayAlmostSorted(int arr[], int size, int noOfSwaps);

// Fonction principale
int main() {w
    int array[SIZE], copy[SIZE], copy2[SIZE];
    clock_t start, end;
    double cpu_time_used;
    char choice;

    // Demander à l'utilisateur de choisir le mode de remplissage du tableau
    printf("Choisir le mode de remplissage du tableau:\n");
    printf("a) Aleatoire\n");
    printf("b) Trie\n");
    printf("c) Presque trie\n");
    printf("Votre choix: ");
    scanf(" %c", &choice);

    // Remplir le tableau selon le choix de l'utilisateur
    switch(choice) {
        case 'a':
            fillArrayWithRandomNumbers(array, SIZE);
            break;
        case 'b':
            fillArraySorted(array, SIZE);
            break;
        case 'c':
            fillArrayAlmostSorted(array, SIZE, 100); 
            break;
        default:
            printf("Choix invalide.\n");
            return 1;
    }

    int insertionSortExchanges = 0;
    int recursiveInsertionExchanges = 0;
    int recursiveMergeExchanges = 0;
    int iterativeMergeExchanges = 0;
    int iterativeQuickExchanges = 0;
    int recursiveQuickExchanges = 0;

    // Tri par insertion itératif
    copyArray(array, copy, SIZE);
    start = clock();
    insertionSortIterative(copy, SIZE, &insertionSortExchanges);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tri par insertion itératif T= %f , Echanges= %d\n", cpu_time_used, insertionSortExchanges);
   /*
    // Tri par insertion récursif
    copyArray(array, copy, SIZE);
    start = clock();

    tri_insertion_recursif(copy, SIZE, &recursiveInsertionExchanges);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Tri par insertion récursif T= %f , Echanges= %d\n", cpu_time_used, recursiveInsertionExchanges);
*/

    // Tri par fusion récursif
    copyArray(array, copy, SIZE);
    start = clock();
    Tri_fusion_rec(copy, 0, SIZE-1, &recursiveMergeExchanges);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tri par fusion récursif T= %f , Echanges= %d\n", cpu_time_used, recursiveMergeExchanges);


    // Tri par fusion itératif
    copyArray(array, copy, SIZE);
    copyArray(array, copy2, SIZE);
    start = clock();
    mergesort(copy, copy2, 0, SIZE-1, &iterativeMergeExchanges);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tri par fusion itératif T= %f , Echanges= %d\n", cpu_time_used, iterativeMergeExchanges);

    // Tri rapide itératif
    copyArray(array, copy, SIZE);
    start = clock();
    quickSortIterative(copy, 0, SIZE - 1, &iterativeQuickExchanges);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tri rapide itératif T= %f , Echanges= %d\n", cpu_time_used, iterativeQuickExchanges);

    // Tri rapide récursif
    copyArray(array, copy, SIZE);
    start = clock();
    quickSort(copy, 0, SIZE - 1, &recursiveQuickExchanges);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tri rapide récursif T= %f , Echanges= %d\n", cpu_time_used, recursiveQuickExchanges);

    printf("Appuyez sur Entrée pour quitter...");
    getchar(); // Attend une entrée de l'utilisateur avant de se fermer
    return 0;
}

// Fonction pour remplir le tableau avec des nombres aléatoires
void fillArrayWithRandomNumbers(int arr[], int size) {
    srand(time(NULL)); 
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % SIZE;
    }
}

void copyArray(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

// Fonction de tri par insertion itératif
void insertionSortIterative(int arr[], int n, int *exchanges){
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        (*exchanges)++;
    }
}

// Fonction auxiliaire pour le tri par insertion récursif
void tri_insertion_recursif(int arr[], int n, int *exchanges) {
    if (n <= 1)
        return;

    tri_insertion_recursif(arr, n - 1, exchanges);

    int dernier = arr[n - 1];
    int j = n - 2;

    while (j >= 0 && arr[j] > dernier) {
        arr[j + 1] = arr[j];
        j--;
        (*exchanges)++;
    }
    arr[j + 1] = dernier;
}

// Fonction principale qui implémente le tri par fusion
void Tri_fusion_rec(int arr[], int l, int r, int *exchanges) {
    if (l < r) {
        int m = l + (r - l) / 2;

        Tri_fusion_rec(arr, l, m, exchanges);
        Tri_fusion_rec(arr, m + 1, r, exchanges);
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;
        int L[n1], R[n2];

        for (i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[m + 1+ j];

        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
            (*exchanges)++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
            (*exchanges)++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
            (*exchanges)++;
        }
    }
}

void quickSort(int arr[], int low, int high, int *exchanges) {
    if (low < high) {
        int pivot = arr[low]; // Choisir le pivot comme premier élément du tableau
        int i = low, j = high;

        while (i <= j) {
            while (arr[i] < pivot) {
                i++;
            }
            while (arr[j] > pivot) {
                j--;
            }
            if (i <= j) {
                // Échanger les éléments arr[i] et arr[j]
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
                (*exchanges)++;
            }
        }

        // Appels récursifs pour les sous-tableaux gauche et droit
        quickSort(arr, low, j, exchanges);
        quickSort(arr, i, high, exchanges);
    }
}

void quickSortIterative(int arr[], int low, int high, int *exchanges) {
    // Créer une pile pour stocker les indices bas et haut
    int stack[high - low + 1];
    int top = -1;

    // Pousser l'indice bas et haut sur la pile
    stack[++top] = low;
    stack[++top] = high;

    // Parcourir la pile
    while (top >= 0) {
        // Dépiler les indices bas et haut
        high = stack[top--];
        low = stack[top--];

        // Partition
        int pivot = arr[low];
        int i = low - 1;
        int j = high + 1;

        while (1) {
            do {
                i++;
            } while (arr[i] < pivot);

            do {
                j--;
            } while (arr[j] > pivot);

            if (i >= j)
                break;

            // Échanger arr[i] et arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            (*exchanges)++;
        }

        int pi = j; // Point d'intersection

        // Si des éléments restent à gauche de la partition, les pousser sur la pile
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        // Si des éléments restent à droite de la partition, les pousser sur la pile
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

int min(int x, int y) {
    return (x < y) ? x : y;
}

void mergesort(int A[], int temp[], int low, int high, int *exchanges)
{
    for (int m = 1; m <= high - low; m = 2*m)
    {
        for (int i = low; i < high; i += 2*m)
        {
            int from = i;
            int mid = i + m - 1;
            int to = min(i + 2*m - 1, high);

            int k = from, i = from, j = mid + 1;

            while (i <= mid && j <= to)
            {
                if (A[i] < A[j]) {
                    temp[k++] = A[i++];
                }
                else {
                    temp[k++] = A[j++];
                }
                (*exchanges)++;
            }

            while (i < SIZE && i <= mid) {
                temp[k++] = A[i++];
                (*exchanges)++;
            }

            for (int i = from; i <= to; i++) {
                A[i] = temp[i];
            }
        }
    }
}

void fillArraySorted(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}

void fillArrayAlmostSorted(int arr[], int size, int noOfSwaps) {
    fillArraySorted(arr, size);
    while (noOfSwaps--) {
        int idx1 = rand() % size;
        int idx2 = rand() % size;
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}
