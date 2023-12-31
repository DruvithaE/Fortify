#include "functions.h"


min_heap *create_min_heap(int capacity)
{
    min_heap *heap = (min_heap *)malloc(sizeof(min_heap));
    heap->arr = (pair *)malloc(sizeof(pair) * 1e6);
    heap->size = 0;
    return heap;
}

void swap(pair *a, pair *b)
{
    pair temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(min_heap *heap, int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;
    if (left < heap->size && heap->arr[left].first < heap->arr[smallest].first)
        smallest = left;
    if (right < heap->size && heap->arr[right].first < heap->arr[smallest].first)
        smallest = right;
    if (smallest != index)
    {
        swap(&heap->arr[smallest], &heap->arr[index]);
        min_heapify(heap, smallest);
    }
}

void insert(min_heap *heap, pair data)
{
    heap->arr[heap->size] = data;
    heap->size++;
    int i = heap->size - 1;
    while (i != 0 && heap->arr[(i - 1) / 2].first > heap->arr[i].first)
    {
        swap(&heap->arr[(i - 1) / 2], &heap->arr[i]);
        i = (i - 1) / 2;
    }
}

pair extract_min(min_heap *heap)
{
    if (heap->size == 0)
        return (pair){-1, -1};
    if (heap->size == 1)
    {
        heap->size--;
        return heap->arr[0];
    }
    pair root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    min_heapify(heap, 0);
    return root;
}

void dijikstra(int N, int M, int** weights, int** vis, long long int** dist,min_heap* heap)
{
    //Print Initial Heap
    //printf("Initial Heap:\n");
    //for(int i=0;i<heap->size;i++)
//        printf("%d %d - %lld\n", heap->arr[i].second/M, heap->arr[i].second%M, heap->arr[i].first);
    while(heap->size!=0)
    {
        pair curr_node = extract_min(heap);
        int weight = curr_node.first;
        int curr_node_x = curr_node.second/M;
        int curr_node_y = curr_node.second%M;
  //      printf("Extracted node: %d %d - %d\n", curr_node_x, curr_node_y, weight);
        if(vis[curr_node_x][curr_node_y]==1)
            continue;
        vis[curr_node_x][curr_node_y] = 1;
        if(curr_node_x+1<N && vis[curr_node_x+1][curr_node_y]==0)
        {
            if(dist[curr_node_x+1][curr_node_y]>weight+weights[curr_node_x+1][curr_node_y])
            {
                dist[curr_node_x+1][curr_node_y] = weight+weights[curr_node_x+1][curr_node_y];
    //            printf("Inserting node: %d %d - %lld\n", curr_node_x+1, curr_node_y, dist[curr_node_x+1][curr_node_y]);
                insert(heap, (pair){dist[curr_node_x+1][curr_node_y], (curr_node_x+1)*M+curr_node_y});
            }
        }
        if(curr_node_x-1>=0 && vis[curr_node_x-1][curr_node_y]==0)
        {
            if(dist[curr_node_x-1][curr_node_y]>weight+weights[curr_node_x-1][curr_node_y])
            {
                dist[curr_node_x-1][curr_node_y] = weight+weights[curr_node_x-1][curr_node_y];
                //printf("Inserting node: %d %d - %lld\n", curr_node_x-1, curr_node_y, dist[curr_node_x-1][curr_node_y]);
                insert(heap, (pair){dist[curr_node_x-1][curr_node_y], (curr_node_x-1)*M+curr_node_y});
            }
        }
        if(curr_node_y+1<M && vis[curr_node_x][curr_node_y+1]==0)
        {
            if(dist[curr_node_x][curr_node_y+1]>weight+weights[curr_node_x][curr_node_y+1])
            {
                dist[curr_node_x][curr_node_y+1] = weight+weights[curr_node_x][curr_node_y+1];
                //printf("Inserting node: %d %d - %lld\n", curr_node_x, curr_node_y+1, dist[curr_node_x][curr_node_y+1]);
                insert(heap, (pair){dist[curr_node_x][curr_node_y+1], curr_node_x*M+curr_node_y+1});
            }
        }
        if(curr_node_y-1>=0 && vis[curr_node_x][curr_node_y-1]==0)
        {
            if(dist[curr_node_x][curr_node_y-1]>weight+weights[curr_node_x][curr_node_y-1])
            {
                dist[curr_node_x][curr_node_y-1] = weight+weights[curr_node_x][curr_node_y-1];
                //printf("Inserting node: %d %d - %lld\n", curr_node_x, curr_node_y-1, dist[curr_node_x][curr_node_y-1]);
                insert(heap, (pair){dist[curr_node_x][curr_node_y-1], curr_node_x*M+curr_node_y-1});
            }
        }
        if(curr_node_x+1<N && curr_node_y+1<M && vis[curr_node_x+1][curr_node_y+1]==0)
        {
            if(dist[curr_node_x+1][curr_node_y+1]>weight+weights[curr_node_x+1][curr_node_y+1])
            {
                dist[curr_node_x+1][curr_node_y+1] = weight+weights[curr_node_x+1][curr_node_y+1];
                //printf("Inserting node: %d %d - %lld\n", curr_node_x+1, curr_node_y+1, dist[curr_node_x+1][curr_node_y+1]);
                insert(heap, (pair){dist[curr_node_x+1][curr_node_y+1], (curr_node_x+1)*M+curr_node_y+1});
            }
        }
        if(curr_node_x+1<N && curr_node_y-1>=0 && vis[curr_node_x+1][curr_node_y-1]==0)
        {
            if(dist[curr_node_x+1][curr_node_y-1]>weight+weights[curr_node_x+1][curr_node_y-1])
            {
                dist[curr_node_x+1][curr_node_y-1] = weight+weights[curr_node_x+1][curr_node_y-1];
                //printf("Inserting node: %d %d - %lld\n", curr_node_x+1, curr_node_y-1, dist[curr_node_x+1][curr_node_y-1]);
                insert(heap, (pair){dist[curr_node_x+1][curr_node_y-1], (curr_node_x+1)*M+curr_node_y-1});
            }
        }
        if(curr_node_x-1>=0 && curr_node_y+1<M && vis[curr_node_x-1][curr_node_y+1]==0)
        {
            if(dist[curr_node_x-1][curr_node_y+1]>weight+weights[curr_node_x-1][curr_node_y+1])
            {
                dist[curr_node_x-1][curr_node_y+1] = weight+weights[curr_node_x-1][curr_node_y+1];
                //printf("Inserting node: %d %d - %lld\n", curr_node_x-1, curr_node_y+1, dist[curr_node_x-1][curr_node_y+1]);
                insert(heap, (pair){dist[curr_node_x-1][curr_node_y+1], (curr_node_x-1)*M+curr_node_y+1});
            }
        }
        if(curr_node_x-1>=0 && curr_node_y-1>=0 && vis[curr_node_x-1][curr_node_y-1]==0)
        {
            if(dist[curr_node_x-1][curr_node_y-1]>weight+weights[curr_node_x-1][curr_node_y-1])
            {
                dist[curr_node_x-1][curr_node_y-1] = weight+weights[curr_node_x-1][curr_node_y-1];
                //printf("Inserting node: %d %d - %lld\n", curr_node_x-1, curr_node_y-1, dist[curr_node_x-1][curr_node_y-1]);
                insert(heap, (pair){dist[curr_node_x-1][curr_node_y-1], (curr_node_x-1)*M+curr_node_y-1});
            }
        }

    }
}