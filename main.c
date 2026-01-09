#include <stdio.h>
#include <stdlib.h>
#include "sets.h"

int main(void) {
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int arr_two[] = {1, 1, 1, 1, 3, 3, 5, 5, 5, 8, 8, 9};
	const int val = 7;
	const int size = sizeof(arr) / sizeof(arr[0]);
	const int size_two = sizeof(arr_two) / sizeof(arr_two[0]);

	if (contains(arr, size, val)) printf("%d is in the set\n", val);
	else printf("%d is not in the set\n", val);

	printf("\n");
	int union_size;
	int *arr_union = union_set(arr, size, arr_two, size_two, &union_size);
	printf("Result of union:\n");
	for (int i = 0; i < union_size; i++) printf("%d ", arr_union[i]);

	int inter_size;
	int *arr_intersection = intersection(arr, size, arr_two, size_two, &inter_size);
	printf("\nResult of intersection:\n");
	for (int i = 0; i < inter_size; i++) printf("%d ", arr_intersection[i]);

	free(arr_union);
	free(arr_intersection);

	return 0;
}
