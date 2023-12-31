#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    long long int first;
    int second;
} pair;

typedef struct
{
    pair *arr;
    int size;
} min_heap;

min_heap *create_min_heap(int capacity);
void swap(pair *a, pair *b);
void min_heapify(min_heap *heap, int index);
void insert(min_heap *heap, pair data);
pair extract_min(min_heap *heap);
void dijikstra(int N, int M, int** weights, int** vis, long long int** dist,min_heap* heap);


#endif