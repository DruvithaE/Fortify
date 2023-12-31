#include "functions.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int N,M;
        scanf("%d %d", &N, &M);
        int** weights;
        weights = (int**)malloc(N*sizeof(int*));
        for(int i=0;i<N;i++)
        {
            weights[i] = (int*)malloc(M*sizeof(int));
        }

        for(int i=0;i<N;i++)
        {
            for(int j=0;j<M;j++)
            {
                scanf("%d", &weights[i][j]);
            }
        }
        int source_x[N+M-1], source_y[N+M-1], dest_x[N+M-1], dest_y[N+M-1];
        for(int i=0;i<N;i++)
        {
            source_x[i] = i;
            source_y[i] = 0;
        }
        for(int i=0;i<M;i++)
        {
            source_x[i+N-1] = N-1;
            source_y[i+N-1] = i;
        }
        for(int i=0;i<M;i++)
        {
            dest_x[i] = 0;
            dest_y[i] = i;
        }
        for(int i=0;i<N;i++)
        {
            dest_x[i+M-1] = i;
            dest_y[i+M-1] = M-1;
        }
        long long int** dist = (long long int**)malloc(N*sizeof(long long int*));
        for(int i=0;i<N;i++)
        {
            dist[i] = (long long int*)malloc(M*sizeof(long long int));
        }
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<M;j++)
            {
                dist[i][j] = __LONG_LONG_MAX__;
            }
        }
        //int visited[N][M];
        int** visited;
        visited = (int**)malloc(N*sizeof(int*));
        for(int i=0;i<N;i++)
        {
            visited[i] = (int*)malloc(M*sizeof(int));
        }
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<M;j++)
            {
                visited[i][j] = 0;
            }
        }
        min_heap* heap = create_min_heap(N*M);
        for(int i=0;i<N+M-1;i++)
        {
            dist[source_x[i]][source_y[i]] = weights[source_x[i]][source_y[i]];
            insert(heap, (pair){dist[source_x[i]][source_y[i]], source_x[i]*M+source_y[i]});
        } 
        dijikstra(N, M, weights, visited, dist, heap);
        long long int min_dist = __LONG_LONG_MAX__;
        for(int i=0;i<N+M-1;i++)
        {
            if(min_dist>dist[dest_x[i]][dest_y[i]])
                min_dist = dist[dest_x[i]][dest_y[i]];
        }
        
        printf("%lld\n", min_dist);
        free(heap->arr);
        free(heap);
        for(int i=0;i<N;i++)
        {
            free(weights[i]);
            free(dist[i]);
            free(visited[i]);
        }
        free(weights);
        free(dist);
        free(visited);

    }
    
    return 0;
}
