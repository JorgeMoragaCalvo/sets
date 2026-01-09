#pragma once
#ifndef SETS_H
#define SETS_H

#include <stdbool.h>

int * union_set(int *arr_a, int size_a, int *arr_b, int size_b, int *size_c);
int maximum(const int *arr, int n);
int minimum(const int *arr, int n);
int *unique(int *arr, int size, int *unique_count);
int * intersection(const int *arr_one, int size_one, const int *arr_two, int size_two);
bool contains(const int *arr, int n, int element);

#endif

