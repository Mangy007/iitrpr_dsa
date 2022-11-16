// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INFINITY __INT_MAX__
#define NO_EDGE 999999
#define NEGATIVE_WEIGHT_CYCLE 9999999

int dijkstraDataStructure = 4;

vector<vector<int>> getGraphRepresentation(int N);
void applyJohnsonAlgorithm(vector<vector<int>> graph, int N);
void printGraph(vector<vector<int>> graph, int size);

int main(int argc, char *argv[]) {

    if(argc > 1) {
        // cout<<"arg: "<<argv[1]<<endl;
        dijkstraDataStructure = atoi(argv[1]);
    }
    vector<double> time_taken_by_each_testcase;
    int testCases;
    cin >> testCases;
    while (testCases--) {
        clock_t start, end;
		double total_time_consumed;
		start = clock();
        int N, D;
        cin >> N >> D;
        vector<vector<int>> graph = getGraphRepresentation(N);
        applyJohnsonAlgorithm(graph, N);
        end = clock();
		total_time_consumed = ((double)(end-start))/CLOCKS_PER_SEC;
        time_taken_by_each_testcase.push_back(total_time_consumed);
    }
    int size = time_taken_by_each_testcase.size();
    for(int i=0; i<size; i++) {
        cout<<time_taken_by_each_testcase[i]<<" ";
    }
    cout<<endl;

    return 0;
}

vector<vector<int>> getGraphRepresentation(int N) {

    vector<vector<int>> adjMat(N);

    for(int i=0; i<N; i++) {
        vector<int> outEdges(N);
        adjMat[i] = outEdges;
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            int edgeWeight;
            cin >> edgeWeight;

            adjMat[i][j] = edgeWeight;
        }
    }

    return adjMat;
}

vector<vector<int>> getModifiedGraph(vector<vector<int>> graph, int N, int source) {

    vector<vector<int>> newGraph(N+1);

    for(int i=0; i<N+1; i++) {
        vector<int> outEdges(N+1);
        newGraph[i] = outEdges;
    }

    for(int i=0; i<N+1; i++) {
        if(i==source) {
            for(int j=0; j<N+1; j++) {
                newGraph[i][j] = 0;
            }
        }
        else {
            newGraph[i][source] = NO_EDGE;
            for(int j=1; j<N+1; j++) {
                newGraph[i][j] = graph[i-1][j-1];
            }
        }
    }

    return newGraph;
}

vector<int> calculatedDistanceFromSourceUsingBellmanFord(vector<vector<int>> graph, int size, int source) {

    vector<int> distance(size);
    for(int i=0; i<size; i++) {
        distance[i] = INFINITY;
    }
    distance[source] = 0;
    vector<pair<int,int>> edges;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if(i!=j && graph[i][j]!=NO_EDGE)
                edges.push_back(make_pair(i,j));
        }
    }
    int totalEdges = edges.size();
    for(int i=0; i<size-1; i++) {
        for(int j=0; j<totalEdges; j++) {
            int u = edges[j].first;
            int v = edges[j].second;
            int weight = graph[u][v];
            if(distance[u] != INFINITY && distance[u]+weight<distance[v])
                distance[v] = distance[u]+weight;
        }
    }

    for(int j=0; j<totalEdges; j++) {
        int u = edges[j].first;
        int v = edges[j].second;
        int weight = graph[u][v];
        if(distance[u] != INFINITY && distance[u]+weight<distance[v])
            distance[v] = NEGATIVE_WEIGHT_CYCLE;
    }

    return distance;
}

vector<vector<int>> reweightGraph(vector<vector<int>> graph, int size, vector<int> distanceFromNewSource) {

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if(i!=j && graph[i][j]!=NO_EDGE)
                graph[i][j] += distanceFromNewSource[i+1] - distanceFromNewSource[j+1];
        }
    }
    return graph;
}

int getMinDistanceVertexByArray(bool visited[], int distance[], int size) {
    int min = INFINITY;
    int minVertex = INFINITY;
    for(int i=0; i<size; i++) {
        if(visited[i]==false && min>distance[i]) {
            min = distance[i];
            minVertex = i;
        }
    }
    return minVertex;
}

void findPathByDijkstraByArray(vector<vector<int>> graph, vector<int> reweightedDistance, int source, int size) {

    bool visited[size];
    int distance[size];
    for(int i=0; i<size; i++) {
        distance[i] = INFINITY;
        visited[i] = false;
    }
    distance[source] = 0;
    
    for(int i=0; i<size; i++) {
        int currMinVertex = getMinDistanceVertexByArray(visited, distance, size);
        if(currMinVertex==INFINITY) {
            currMinVertex=i;
        }
        visited[currMinVertex] = true;
        
        for(int j=0; j<size; j++) {
            if(visited[j]==false && graph[currMinVertex][j]!=NO_EDGE && distance[currMinVertex]!=INFINITY && (distance[currMinVertex]+graph[currMinVertex][j])<distance[j])
                distance[j] = distance[currMinVertex]+graph[currMinVertex][j] + reweightedDistance[j+1] - reweightedDistance[currMinVertex+1];
        }
    }
    for(int i=0; i<size; i++) {
        if(distance[i]>NO_EDGE) distance[i] = NO_EDGE;
        cout<<distance[i]<<" ";
    }
}

void findPathByDijkstraByBinaryHeap(vector<vector<int>> graph, vector<int> reweightedDistance, int source, int size) {
    
    priority_queue<pair<int, int>> binaryHeap;
    vector<int> distance;
    for(int i=0; i<size; i++) {
        distance.push_back(INFINITY);
    }
    distance[source] = 0;
    binaryHeap.push(make_pair(0, source));

    while(!binaryHeap.empty()) {

        int minVertex = binaryHeap.top().second;
        binaryHeap.pop();

        for(int j=0; j<size; j++) {
            if(j!=minVertex && graph[minVertex][j]!=NO_EDGE && (distance[minVertex]+graph[minVertex][j])<distance[j]) {
                distance[j] = distance[minVertex]+graph[minVertex][j] + reweightedDistance[j+1] - reweightedDistance[minVertex+1];
                binaryHeap.push(make_pair(distance[j], j));
            }
        }
    }
    for(int i=0; i<size; i++) {
        if(distance[i]>NO_EDGE) distance[i] = NO_EDGE ;
        cout<<distance[i]<<" ";
    }
}


void applyJohnsonAlgorithm(vector<vector<int>> graph, int N) {

    int source = 0;
    vector<vector<int>> modifiedGraph = getModifiedGraph(graph, N, source);
    vector<int> distanceFromNewSource = calculatedDistanceFromSourceUsingBellmanFord(modifiedGraph, N+1, source);
    graph = reweightGraph(graph, N, distanceFromNewSource);
    // cout<<endl;
    // printGraph(graph, N);
    for(int i=0; i<N; i++) {
        bool isNegativeWeightCyclePresent = false;
        for(int j = 0; j < N; j++) {
            if(graph[i][j]>NO_EDGE || graph[i][j]<0)
                isNegativeWeightCyclePresent = true;
        }
        if(!isNegativeWeightCyclePresent) {
            if(dijkstraDataStructure==2) {
                //binary heap
                findPathByDijkstraByBinaryHeap(graph, distanceFromNewSource, i, N);
            }
            else {
                findPathByDijkstraByArray(graph, distanceFromNewSource, i, N);
            }
        }
        else {
            cout<<"-1";
        }
        cout<<endl;
    }
    

}

void printGraph(vector<vector<int>> graph, int size) {

     for (int i = 0; i < size; i++) {
        bool isNegativeWeightCyclePresent = false;
        for(int j = 0; j < size; j++) {
            if(graph[i][j]>NO_EDGE)
                isNegativeWeightCyclePresent = true;
        }
        if(!isNegativeWeightCyclePresent) {
            for(int j = 0; j < size; j++) {
                cout<<graph[i][j]<<" ";
            }
        }
        else {
            cout<<"-1";
        }
        cout<<endl;
    }
}
