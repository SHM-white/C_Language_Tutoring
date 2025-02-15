# Sort Functions
## Bubble Sort 冒泡排序
当前阶段掌握这种排序算法即可，如果有时间可以研究一下其他的排序算法。
```c
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
```

## Selection Sort 选择排序

```c
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        // swap arr[i] and arr[min_idx]
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}
```

## Quick Sort 快速排序

```c
void quickSort(int arr[], int l, int r) {
    if (l < r) {
        int pivot = arr[l];
        int i = l+1, j = r;
        while (i <= j) {
            while (i <= r && arr[i] <= pivot)
                i++;
            while (j >= l && arr[j] >= pivot)
                j--;
            if (i < j) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        arr[l] = arr[j];
        arr[j] = pivot;
        quickSort(arr, l, j-1);
        quickSort(arr, j+1, r);
    }
}
```

## Insertion Sort 插入排序

```c
void insertionSort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}
``` 

## Merge Sort 归并排序

```c
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
```

## Heap Sort 堆排序

```c
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest!= i) {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i=n-1; i>=0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}
```
## Counting Sort 计数排序

```c
void countingSort(int arr[], int n) {
    int output[n];
    int max_element = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_element)
            max_element = arr[i];
    }
    int count[max_element+1];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < n; i++)
        count[arr[i]]++;
    for (int i = 1; i <= max_element; i++)
        count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--) {
        output[count[arr[i]]-1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
```

## Radix Sort 基数排序

```c
void radixSort(int arr[], int n) {
    int max_element = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_element)
            max_element = arr[i];
    }
    int exp = 1;
    while (max_element/exp > 0) {
        countingSort(arr, n, exp);
        exp *= 10;
    }
}

void countingSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++) {
        int index = (arr[i]/exp) % 10;
        count[index]++;
    }
    for (int i = 1; i < 10; i++)
        count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--) {
        int index = (arr[i]/exp) % 10;
        output[count[index]-1] = arr[i];
        count[index]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
```
## Bucket Sort 桶排序

```c
void bucketSort(int arr[], int n) {
    int max_element = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_element)
            max_element = arr[i];
    }
    int bucket[max_element+1];
    memset(bucket, 0, sizeof(bucket));
    for (int i = 0; i < n; i++)
        bucket[arr[i]]++;
    int index = 0;
    for (int i = 0; i <= max_element; i++) {
        while (bucket[i] > 0) {
            arr[index++] = i;
            bucket[i]--;
        }
    }
}
```
## Tim Sort 时间排序

```c
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void timSort(int arr[], int n) {
    int minRun = 32;
    for (int i = 0; i < n; i += minRun)
        insertionSort(arr+i, min((n-i), minRun));
    int size = minRun;
    while (size < n) {
        for (int i = 0; i < n; i += size*2) {
            merge(arr, i, i+size-1, min((i+size*2-1), (n-1)));
        }
        size *= 2;
    }
}
```