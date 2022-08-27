#include<stdio.h>
#include<stdlib.h>  // used by rand() function to generate random integers
#include<stdbool.h> // used by boolean variables
#include<time.h>

void bubbleSort(unsigned int A[], int n);
void selectionSort(unsigned int A[], int n);
void insertionSort(unsigned int A[], int n);
void merge(unsigned int A[], int left, int mid, int right);
void mergeSort(unsigned int A[], int left, int right);
int partition(unsigned int A[], int start, int end);
void quickSort(unsigned int A[], int start, int end);
void inverseArray(unsigned int A[], int size);
void getInputArray(unsigned int A[], int size, int order);
void printArray(unsigned int A[], int size, char *printType);

int main() {

	int testCases;
	scanf("%d", &testCases);
 
	while(testCases--) {
		// N = Size of Input array, S = Sorting algorithms to be used, k = Input order, p = Output format
		int N, S, k, p;

		scanf("%d%d%d%d", &N, &S, &k, &p);
		unsigned int A[N];

		getInputArray(A, N, k);
		if(p==2) printArray(A,N, "Input");
		
		clock_t start, end;
		double total_time_consumed;
		start = clock();
		switch(S) {
			case 0: bubbleSort(A,N); break;
			case 1: selectionSort(A,N); break;
			case 2: insertionSort(A,N);break;
			case 3: mergeSort(A,0, N-1); break;
			case 4: quickSort(A,0, N-1); break;
			default:  continue;
		}
		end = clock();
		total_time_consumed = ((double)(end-start))/CLOCKS_PER_SEC;
		
		if(p==1 || p==2) printArray(A,N, "Output");
		printf("\nsorting took %f seconds\n", total_time_consumed);
	}

	return 0;
}

void inverseArray(unsigned int A[], int size) {
	
	for(int i=0; i<size/2; i++) {
		unsigned int temp = A[i];
		A[i] = A[size-i-1];
		A[size-i-1] = temp;
	}
}

void getInputArray(unsigned int A[], int size, int order) {

	srand(time(0));
	for(int i=0; i<size;i++) A[i] = rand()%10000000;

	switch(order) {
		case 0: break;
		case 1: quickSort(A, 0, size-1); break;
		case 2: quickSort(A, 0, size-1); inverseArray(A, size); break;
		default: break;
	}
}

void bubbleSort(unsigned int A[], int n) {

	for(int i=0;i<n-1;i++) {
		bool flag = false;
		for(int j=i+1;j<n;j++) {
			if(A[i]>A[j]) {
				unsigned int temp = A[i];
				A[i] = A[j];
				A[j] = temp;
				flag = true;
			}
		}
	if(!flag) break;
	}
}

void selectionSort(unsigned int A[], int n) {
	
	for(int i=0;i<n-1;i++) {
		unsigned int min = A[i];
		int index = i;
		for(int j=i+1;j<n;j++) {
			if(A[j]<min) {
				min = A[j];
				index = j;
			}
		}
		unsigned int temp = A[i];
		A[i] = min;
		A[index] = temp;
	}
}

void insertionSort(unsigned int A[], int n) {

	for(int i=1; i<n; i++) {
		unsigned int currentValue = A[i];
		int j=i-1;
		for(; j>=0; j--) {
			if(A[j]>currentValue) A[j+1] = A[j];
			else break;
		}
		A[j+1] = currentValue;
	}
}

void merge(unsigned int A[], int left, int mid, int right) {

	int size1 = mid-left+1, size2 = right-mid;
	unsigned int B[size1], C[size2];
	for(int i=0; i<size1; i++) B[i] = A[left+i];
	for(int i=0; i<size2; i++) C[i] = A[mid+1+i];
	int i=0, j=0, k=left;
	while(k<=right) {
		if(i<size1 && j<size2) {
			if(B[i]<=C[j]) { A[k] = B[i]; i++; }
			else { A[k] = C[j]; j++; }
		}
		else if(i<size1) { A[k] = B[i]; i++; }
		else { A[k] = C[j]; j++; }
		k++;
	}
}

void mergeSort(unsigned int A[], int left, int right) {

	if(left<right) {
		int mid = (left+right)/2;
		mergeSort(A, left, mid);
		mergeSort(A, mid+1, right);
		merge(A, left, mid, right);
	}
	else return;
}

int partition(unsigned int A[], int start, int end) {

	unsigned int pivot = A[start];
	int i=start, j=end;
	while(i<=j) {
		if(A[i] <= pivot) i++;
		else if(pivot < A[j]) j--;
		else {
			unsigned int temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}

	unsigned int temp = A[j];
	A[j] = A[start];
	A[start] = temp;

	return j;
}

//  
void quickSort(unsigned int A[], int start, int end) {

	if(start<end) {
		int index = partition(A, start, end);
		quickSort(A, start, index-1);
		quickSort(A, index+1, end);
	}
	else return;
}

// prints the array which takes array, array size 
// and a string asking for the type of array you are printing i.e input/output array
void printArray(unsigned int A[], int size, char *printType) {
	
	printf("\n %s array: ", printType);
	for(int i=0; i<size && i<50; i++) printf("%d ",A[i]);
}