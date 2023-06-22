#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void Insertion(int *A, int num) {
    for (int i = 1; i < num; i++) {
        int key = A[i];
        int j = i-1;
        while (j >= 0 && A[j] > key) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
    }
}

void Merge(int *A, int p, int q, int r) {
    int nl = q - p + 1;
    int nr = r - q;
    int al[nl];
    int ar[nr];
    for (int i = p; i < q+1; i++) {
        al[i - p] = A[i];
    }
    for (int j = q+1; j < r+1; j++) {
        ar[j - q - 1] = A[j];
    }

    int i = 0, j = 0, k = p;
    while (i < nl && j < nr) {
        if (al[i] <= ar[j]) {
            A[k] = al[i];
            i++;
        }
        else{
            A[k] = ar[j];
            j++;
        }
        k++;
    }
    while (i < nl) {
        A[k] = al[i];
        i++;
        k++;
    }
    while (j < nr) {
        A[k] = ar[j];
        j++;
        k++;
    }
}

void MergeSort(int *A, int p, int r) {
    if (p >= r)
        return;
    int q = (p+r)/2;
    MergeSort(A, p, q);
    MergeSort(A, q+1, r);
    Merge(A, p, q, r);
}

int Partition(int *A, int p, int r) {
    int i = p;
    for (int j = p; j < r; j++) {
        if (A[j] < A[r]) {
            int tmp = A[j];
            A[j]  = A[i];
            A[i] = tmp;
            i++;
        }
    }
    int tmp = A[r];
    A[r] = A[i];
    A[i] = tmp;

    return i;
}

void QuickSort(int *A, int p, int r) {
    if (p < r) {
        int q = Partition(A, p, r);
        QuickSort(A, p, q-1);
        QuickSort(A, q+1, r);
    }
}

void QuickSort_intro(int *A, int p, int r, int depth) {

    if (depth == 0 ) {
        if (r - p + 1 > 16) {
            MergeSort(A, p, r);
        }
        return;
    }

    if (p < r) {
        
        int tmp;
        if (A[p] > A[(p+r)/2]) {
            tmp = A[(p+r)/2];
            A[(p+r)/2] = A[p];
            A[p] = tmp;
        }
        if (A[(p+r)/2] > A[r]) {
            tmp = A[r];
            A[r] = A[(p+r)/2];
            A[(p+r)/2] = tmp;
        }
        if (A[p] > A[(p+r)/2]) {
            tmp = A[(p+r)/2];
            A[(p+r)/2] = A[p];
            A[p] = tmp;
        }
        

        int q = Partition(A, p, (p+r)/2);
        QuickSort_intro(A, p, q-1, depth-1);
        QuickSort_intro(A, q+1, r, depth-1);
    }
}

void IntroSort(int *A, int num) {
    double a = (double)num;
    double b = log2(a);
    double c = 2 * ceil(c);

    if (num <= 16) {
        Insertion(A, num);
        return;
    }
    QuickSort_intro(A, 0, num-1, c);
}

int main(int argc, char **argv) {

    // error for argc
    if (argc != 3) {
        printf("Wrong input sentence\n");
        return 0;
    }

    // file open for reading
    FILE *fp = fopen(argv[1], "r");
    if (fp==NULL) {
        printf("File open error\n");
        return 0;
    }

    // read unsorted list in file
    int num;
    fscanf(fp, "%d", &num);
    int arr[num];
    for (int i = 0; i < num; i++) {
        fscanf(fp, "%d", &arr[i]);
    }

    // file close
    fclose(fp);


    // Before sorting, time check
    clock_t start = clock();

    // Algorithm 1. Insertion sort
    if (atoi(argv[2]) == 1) {
        Insertion(arr, num);
    }

    // Algorithm 2. quick sort
    else if (atoi(argv[2]) == 2) {
        QuickSort(arr, 0, num-1);
    }


    // Algorithm 3. merge sort
    else if (atoi(argv[2]) == 3) {
        MergeSort(arr, 0, num-1);
    }

    // Algorithm 4. my sort
    else if (atoi(argv[2]) == 4) {
        IntroSort(arr, num);
    }

    // After sorting, time check
    clock_t end = clock();
    double duration = (double)(end - start)/CLOCKS_PER_SEC;

    // file open for writing
    char str[100];
    sprintf(str, "result_%s_%s", argv[2], argv[1]);
    FILE *fp_w = fopen(str, "w");
    if (fp_w == NULL) {
        printf("File open error\n");
        return 0;
    }

    // write the result in file
    fprintf(fp_w, "%s\n", argv[1]);
    fprintf(fp_w, "%s\n", argv[2]);
    fprintf(fp_w, "%d\n", num);
    fprintf(fp_w, "%lf\n", duration);
    for (int j = 0; j < num; j++) {
        fprintf(fp_w, "%d ", arr[j]);
    }

    // file close
    fclose(fp_w);


}