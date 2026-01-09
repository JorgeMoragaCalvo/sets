#include "sort.h"

void mergeSort(int *arr, const int p, const int r){
	if(p >= r) return;

	const int q = (p + r) / 2;
	mergeSort(arr, p, q);
	mergeSort(arr, q + 1, r);
	merge(arr, p, q, r);
}

void merge(int *arr, const int p, const int q, const int r){
	const int leftSize = q - p + 1;
	const int rightSize = r - q;
	int leftArray[leftSize];
	int rightArray[rightSize];
	//the left and right half of the original array is copied to leftArray and rightArray respectively
	for(int i = 0; i < leftSize; i++) leftArray[i] = arr[p + i];
	for(int j = 0; j < rightSize; j++) rightArray[j] = arr[q + j + 1];

	int i = 0, j = 0, k = p;
	while(i < leftSize && j < rightSize){
		if(leftArray[i] <= rightArray[j]){
			arr[k] = leftArray[i];
			i++;
		}
		else{
			arr[k] = rightArray[j];
			j++;
		}
		k++;
	}

	while(i < leftSize){
		arr[k] = leftArray[i];
		i++;
		k++;
	}

	while(j < rightSize){
		arr[k] = rightArray[j];
		j++;
		k++;
	}
}

