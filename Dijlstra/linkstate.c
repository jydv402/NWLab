#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_NODES 10

int minDistance(int dist[], bool visited[], int numNodes)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < numNodes; v++)
    {
        if (!visited[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[MAX_NODES][MAX_NODES], int src, int numNodes)
{
    int dist[MAX_NODES];
    bool visited[MAX_NODES];

    for (int i = 0; i < numNodes; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < numNodes - 1; count++)
    {
        int u = minDistance(dist, visited, numNodes);
        visited[u] = true;

        for (int v = 0; v < numNodes; v++)
        {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Node\tDistance from Source Node %d\n", src);
    for (int i = 0; i < numNodes; i++)
    {
        if (dist[i] == INT_MAX)
        {
            printf("%d\tUnreachable\n", i);
        }
        else
        {
            printf("%d\t%d\n", i, dist[i]);
        }
    }
}

int main()
{
    int graph[MAX_NODES][MAX_NODES];
    int numNodes, src;

userIp:
    printf("Enter the number of nodes in the network (Max %d): ", MAX_NODES);
    scanf("%d", &numNodes);

    if (numNodes > MAX_NODES)
    {
        printf("Number of nodes exceeds the maximum allowed.\n");
        goto userIp;
    }

    printf("Enter the adjacency matrix (Use 0 for no link and a positive number for cost):\n");
    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

srcIp:
    printf("Enter the source node (0 to %d): ", numNodes - 1);
    scanf("%d", &src);

    if (src < 0 || src >= numNodes)
    {
        printf("Invalid source node.\n");
        goto srcIp;
    }

    dijkstra(graph, src, numNodes);

    return 0;
}
