#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void swapify(int *num1, int *num2) {
	int tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}

//n is size of heap, node is index in arr[]
void heapify (int arr[], int node, int n) {	
	//First, create biggest index and root
	int biggestIndex = node;

	//intilize for left and for right
	int left = 2 * node + 1;
	int right = 2 * node + 2;

	//Checks if left is bigger than root
	if (left < n && arr[left] > arr[biggestIndex]) {
		biggestIndex = left;
	}

	//Checks if right is bigger than root
	if (right < n && arr[right] > arr[biggestIndex]) {
		biggestIndex = right;
	}
	
	//Terminating condition
	if (biggestIndex != node) {
		
		//Swaps to make larger node the root
		swapify(&arr[node], &arr[biggestIndex]);

		//recursion
		heapify(arr, biggestIndex, n);
	} 
}

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(arr, i, n);
	}

	for (int i = n - 1; i >= 0; i--) {
		swapify(&arr[0], &arr[i]);

		heapify(arr, 0, i);
	}
}

void mergeify(int arr[], int left, int mid, int right) {
	
	int a, b, c;
    int n1 = mid - left + 1;
    int n2 = right - mid;
 
    //Create two temp arrays
    int L[n1], R[n2];

	for (a = 0; a < n1; a++) {
        L[a] = arr[left + a];
	}
    for (b = 0; b < n2; b++) {
        R[b] = arr[mid + 1 + b];
	}

    //Merges the two arrays back into the original array
    a = 0;
    b = 0;
    c = left;
    while (a < n1 && b < n2) {
        if (L[a] <= R[b]) {
            arr[c] = L[a];
            a++;
        }
        else {
            arr[c] = R[b];
            b++;
        }
        c++;
    }
 
    // Copies leftover elments for L
    while (a < n1) {
        arr[c] = L[a];
        a++;
        c++;
    }
 
    // Copies leftover elemnets for R
    while (b < n2) {
        arr[c] = R[b];
        b++;
        c++;
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int left, int right) {
	if (left < right) {
        int mid = left + (right - left) / 2;
 
        // Sorts the two halves
        mergeSort(pData, left, mid);
        mergeSort(pData, mid + 1, right);
 
        mergeify(pData, left, mid, right);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}