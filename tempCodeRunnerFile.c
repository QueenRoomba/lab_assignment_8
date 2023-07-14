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