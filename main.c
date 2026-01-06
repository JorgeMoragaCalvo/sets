#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool contains(const int *, int, int);
int * intersection(const int *, int, const int *, int);
int *unique(int *, int, int *);
int minimum(const int *, int);
int maximum(const int *, int);
int * union_set(int *, int, int *, int, int *);
void mergeSort(int *, int, int);
void merge(int *, int, int, int);

int main(void) {
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int arr_two[] = {1, 1, 1, 1, 3, 3, 5, 5, 5, 8, 8, 9};
	const int val = 7;
	const int size = sizeof(arr) / sizeof(arr[0]);
	const int size_two = sizeof(arr_two) / sizeof(arr_two[0]);

	if (contains(arr, size, val)) printf("%d is in the set\n", val);
	else printf("%d is not in the set\n", val);

	// int *result = unique(arr_two, size_two, &total_unique);
	// printf("Unique elements in main:\n");
	// for (int i = 0; i < total_unique; i++) {
	// 	printf("%d ", result[i]);
	// }
	printf("\n");
	int union_size;
	int *arr_union = union_set(arr, size, arr_two, size_two, &union_size);
	printf("Result of union:\n");
	for (int i = 0; i < union_size; i++) printf("%d ", arr_union[i]);

	//free(result);
	free(arr_union);

	return 0;
}

bool contains(const int *arr, const int n, const int element) {
	for (int i = 0; i < n; i++) {
		if (arr[i] == element) return true;
	}
	return false;
}

int * intersection(const int *arr_one, const int size_one, const int *arr_two, const int size_two) {
	int major = 0, minor = 0, count = 0;
	if (size_one > size_two) {
		major = size_one;
		minor = size_two;
	} else {
		major = size_two;
		minor = size_one;
	}

	for (int i = 0; i < major; i++) {
		for (int j = 0; j < minor; j++) {
			if (arr_one[i] == arr_two[j]) count++;
		}
	}

	int *arr_three = (int *)malloc(count * sizeof(int));
	for (int i = 0; i < major; i++) {
		for (int j = 0; j < minor; j++) {
			if (arr_one[i] == arr_two[j]) arr_three[count++] = arr_one[i];
		}
	}
	return arr_three;
}

// returns an array with no repeat elements and the size
int *unique(int *arr, const int size, int *unique) {
	// missing sorting function
	mergeSort(arr, 0, size - 1);
	int j = 0, k = 0, count = 0;
	arr[k++] = arr[0];
	for (int i = 1; i < size; i++) {
		if (arr[j] != arr[i]) {
			arr[k++] = arr[i];
			j = i;
			count++;
		}
	}
	*unique = count + 1;
	int *arr_unique = (int *)malloc((count) * sizeof(int));
	if (!arr_unique) {
		*unique = 0;
		return NULL;
	}
	for (int i = 0; i < count + 1; i++) arr_unique[i] = arr[i];
	return arr_unique;
}

int minimum(const int *arr, const int n) {
	int minimum = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] < minimum) minimum = arr[i];
	}
	return minimum;
}

int maximum(const int *arr, const int n) {
	int maximum = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > maximum) maximum = arr[i];
	}
	return maximum;
}

int * union_set(int *arr_a, const int size_a, int *arr_b, const int size_b, int *size_c) {
	int length_a, length_b, total_unique;
	int *array_a = unique(arr_a, size_a, &length_a);
	int *array_b = unique(arr_b, size_b, &length_b);
	// printf("Array A in function:\n");
	// for (int i = 0; i < length_a; i++) printf("%d ", array_a[i]);
	// printf("\n");
	// printf("Array B in function:\n");
	// for (int i = 0; i < length_b; i++) printf("%d ", array_b[i]);
	// printf("\n");

	if (!array_a || !array_b) {
		free(array_a); // free deals with NULL internally, but safe to call
		free(array_b);
		*size_c = 0;
		return NULL;
	}

	int *array_c = (int *)malloc((length_a + length_b) * sizeof(int));
	if (!array_c) {
		free(array_a);
		free(array_b);
		*size_c = 0;
		return NULL;
	}

	for (int i = 0; i < length_a; i++) array_c[i] = array_a[i];
	for (int i = 0; i < length_b; i++) array_c[length_a + i] = array_b[i];
	int *union_result = unique(array_c, length_a + length_b, &total_unique);

	*size_c = total_unique;
	free(array_a);
	free(array_b);
	free(array_c);
	return union_result;
}

void mergeSort(int *arr, const int p, const int r){
	if(p >= r) return;

	int q = (p + r) / 2;
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