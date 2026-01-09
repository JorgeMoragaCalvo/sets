#include "sets.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

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
	// bug 29-34 - return intersection size - remove unused variables major/minor
	int *arr_three = (int *)malloc(count * sizeof(int));
	for (int i = 0; i < major; i++) {
		for (int j = 0; j < minor; j++) {
			if (arr_one[i] == arr_two[j]) arr_three[count++] = arr_one[i];
		}
	}
	return arr_three;
}

// returns an array with no repeat elements and the size
int *unique(int *arr, const int size, int *unique_count) {
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
	*unique_count = count + 1;
	int *arr_unique = (int *)malloc((count + 1) * sizeof(int));

	if (!arr_unique) {
		*unique_count = 0;
		return NULL;
	}
	for (int i = 0; i < count + 1; i++) arr_unique[i] = arr[i];
	return arr_unique;
}
// crash when n <= 0
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

	if (!array_a || !array_b) {
		free(array_a); // free deals with NULL internally
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

