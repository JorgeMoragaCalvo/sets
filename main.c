#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool contains(const int *, int, int);
int * intersection(const int *, int, const int *, int);
int *unique(int *, int, int *);

int main(void) {
	const int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int arr_two[] = {1, 1, 1, 1, 3, 3, 5, 5, 5, 8, 8, 9};
	const int val = 7;
	const int size = sizeof(arr) / sizeof(arr[0]);
	const int size_two = sizeof(arr_two) / sizeof(arr_two[0]);
	int total_unique;

	if (contains(arr, size, val)) printf("%d is in the set\n", val);
	else printf("%d is not in the set\n", val);

	int *result = unique(arr_two, size_two, &total_unique);
	for (int i = 0; i < total_unique; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");

	free(result);

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

int *unique(int *arr, const int size, int *unique) {
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