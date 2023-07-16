#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void maxHeapify(int arr[], int , int);

void maxHeap(int arr[], int beg, int end){
	for(int i = end / 2 ; i >= 0 ; i--){
		maxHeapify(arr, i, end);
	}
}

void maxHeapify(int arr[], int f, int size){
	int max = f;
	int l = f * 2;
	int r = f * 2 + 1;
	int t;

	if(l <= size && arr[l] > arr[max]){
		max = l;
	}
	if(r <= size && arr[r] > arr[max]){
		max = r;
	}
	if(f != max){
		t = arr[f];
		arr[f] = arr[max];
		arr[max] = t;
		maxHeapify(arr, max, size);
	}
}

void heapSort(int arr[], int size)
{
	int t;
	for(int i = size; i >= 2; i--){
		t = arr[1];
		arr[1] = arr[i];
		arr[i] = t;
		maxHeapify(arr, 1, i-1);
	}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated

void merge(int array[], int low, int mid, int high){
	int i, j, k;
	int n1 = mid - low + 1;
	int n2 = high - mid;

	int * Left = malloc(n1 * sizeof(int));
	int * Right = malloc(n2 * sizeof(int));

	for(i = 0; i < n1; i++){
		Left[i] = array[low + i];
	}
	for(i = 0; i < n2; i++){
		Right[i] = array[mid + i + 1];
	}
	i = 0;
	j = 0;
	k = low;

	while(i < n1 && j < n2){
		if(Left[i] <= Right[j]){
			array[k++] = Left[i++];
		}
		else{
			array[k++] = Right[j++];
		}
	}
	while(i < n1){
		array[k++] = Left[i++];
	}
	while(j < n2){
		array[k++] = Right[j++];
	}
	free(Left);
	free(Right);
}


void mergeSort(int pData[], int low, int high)
{
	if(low < high){
		int mid = (low + high) / 2;

		mergeSort(pData, low, mid);
		mergeSort(pData, mid + 1, high);

		merge(pData, low, mid, high);
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
		
		pDataCopy = (int *) malloc(sizeof(int)*dataSz);
	
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