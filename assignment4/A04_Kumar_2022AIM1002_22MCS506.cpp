// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

typedef struct Node {
    int key;
    int height;
    double distance;
    // Node * next;
} Node;

#define INFINITY __INT_MAX__

void performOperationBasedOnQueryType(int query);
void findQuickestPathBasedOnM(vector<vector<int>> adjMat, int M, int sx, int sy, int vx, int vy);


int main() {

    int testCases;
    cin >> testCases;
    while (testCases--) {
        int query;
        cin >> query;
        performOperationBasedOnQueryType(query);
    }

    return 0;
}

vector<vector<Node *>> getGraphRepresentation(int N, int M, int d) {
    vector<vector<Node *>> adjList;
    Node * heights[N][N];
    int buildingNumber = 1;
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            int heightOfBuilding;
            cin >> heightOfBuilding;
            Node * temp = (Node *) malloc(sizeof(Node));
            temp->key = buildingNumber++;
            temp->height = heightOfBuilding;
            heights[i][j] = temp;
        }
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            vector<Node *> nodes;
            nodes.push_back(heights[i][j]);
            if(M==2) {
                if(j+1<N) nodes.push_back(heights[i][j+1]);
                if(i+1<N) nodes.push_back(heights[i+1][j]);
            }
            else if(M==4) {
                if(d<0) {
                    if(i-1>=0) nodes.push_back(heights[i-1][j]);
                    if(j-1>=0) nodes.push_back(heights[i][j-1]);
                    if(j+1<N) nodes.push_back(heights[i][j+1]);
                    if(i+1<N) nodes.push_back(heights[i+1][j]);
                }
                else {
                    if(i-1>=0 && (abs(heights[i][j]->height-heights[i-1][j]->height)<=d)) nodes.push_back(heights[i-1][j]);
                    if(j-1>=0 && (abs(heights[i][j]->height-heights[i][j-1]->height)<=d)) nodes.push_back(heights[i][j-1]);
                    if(j+1<N && (abs(heights[i][j]->height-heights[i][j+1]->height)<=d)) nodes.push_back(heights[i][j+1]);
                    if(i+1<N && (abs(heights[i][j]->height-heights[i+1][j]->height)<=d)) nodes.push_back(heights[i+1][j]);
                }
            }
            else if(M==6) {
                if(i-1>=0) nodes.push_back(heights[i-1][j]);
                if(j-1>=0) nodes.push_back(heights[i][j-1]);
                if(j+1<N) nodes.push_back(heights[i][j+1]);
                if(i+1<N) nodes.push_back(heights[i+1][j]);
                if(i-1>=0 && j+1<N) nodes.push_back(heights[i-1][j+1]);
                if(i+1<N && j+1<N) nodes.push_back(heights[i+1][j+1]);
            }
            else if(M==8) {
                if(j-1>=0) nodes.push_back(heights[i][j-1]);
                if(i-1>=0) nodes.push_back(heights[i-1][j]);
                if(j+1<N) nodes.push_back(heights[i][j+1]);
                if(i+1<N) nodes.push_back(heights[i+1][j]);
                if(i-1>=0 && j+1<N) nodes.push_back(heights[i-1][j+1]);
                if(i+1<N && j+1<N) nodes.push_back(heights[i+1][j+1]);
                if(i-1>=0 && j-1>0) nodes.push_back(heights[i-1][j-1]);
                if(i+1<N && j-1>=0) nodes.push_back(heights[i+1][j-1]);
            }
            else return adjList;
            adjList.push_back(nodes);
        }
    }
    return adjList;
}

//test function: might delete later
void printGraph(vector<vector<Node *>> adjList) {

    for(vector<Node *> node : adjList) {
        for(Node * elem : node) {
            cout << elem->key << "(" << elem->height << ") ->";
        }
        cout << endl;
    }
}

Node * getMinDistanceNode(bool visit[], set<Node *> sortestPath) {
    double min = INFINITY;
    Node * minNode = NULL;
    for(Node * node : sortestPath) {
        if(!visit[node->key-1] && min>=node->distance) {
            if(min==node->distance && minNode!=NULL && minNode->key<node->key) continue;
            min = node->distance;
            minNode = node;
        }
    }
    return minNode;
}

void findQuickestPathByDijkstra(vector<vector<Node *>> graph, int source, int dest, int N) {

    Node * sourceNode = graph[source-1][0];
    Node * destNode = graph[dest-1][0];
    bool visited[graph.size()];
    set<Node *> sortestPath;
    int totalNodes = graph.size();
    
    for(vector<Node *> node : graph) {
        if(node[0]==sourceNode) node[0]->distance = 0;
        else node[0]->distance = INFINITY;

        visited[node[0]->key-1] = false;
        sortestPath.insert(node[0]);
    }
    
    for(int i=0; i<totalNodes; i++) {
        Node * currMinNode = getMinDistanceNode(visited, sortestPath);
        Node * startNode = graph[currMinNode->key-1][0];
        visited[currMinNode->key-1] = true;

        for(Node * node : graph[currMinNode->key-1]) {
            if(!visited[node->key-1]) {
                double currDiff;
                // nodePosition variable gives the node position from the current node from the base node
                int nodePosition = abs(node->key-startNode->key);
                if(nodePosition==0 || nodePosition==1 || nodePosition==N)
                    currDiff = (double)abs(node->height-currMinNode->height);
                else
                    currDiff = 1.5*(double)abs(node->height-currMinNode->height);

                if(node->distance>=currMinNode->distance + currDiff)
                    node->distance = currMinNode->distance + currDiff;
            }
        }
    }

    if(destNode->distance==INFINITY) cout << "-1" << endl;
    else cout << destNode->distance << endl;
}

void findQuickestPathByBFS(vector<vector<Node *>> graph, int source, int dest) {
    
    Node * sourceNode = graph[source-1][0];
    Node * destNode = graph[dest-1][0];
    bool visited[graph.size()];
    queue<Node *> explored;
    explored.push(sourceNode);

    for(vector<Node *> node : graph) {
        if(sourceNode==node[0]) node[0]->distance = 0;
        else node[0]->distance = -1;

        visited[node[0]->key-1] = false;
    }

    while (!explored.empty()) {
        Node * currentNode = explored.front();
        visited[currentNode->key-1] = true;
        explored.pop();
        for(Node * node: graph[currentNode->key-1]) {
            if(!visited[node->key-1]) {
                node->distance = currentNode->distance+1;
                explored.push(node);
            }
        }
    }

    cout << destNode->distance << endl;
}

void freeGraph(vector<vector<Node *>> graph) {

    for(vector<Node *> node : graph) free(node[0]);
}

void performOperationBasedOnQueryType(int query) {
    switch (query)
    {
    case 1: {
        // sortest path using dijkstra
        int N, M, sx, sy, vx, vy;
        cin >> N >> M >> sx >> sy >> vx >> vy;
        vector<vector<Node *>> adjList = getGraphRepresentation(N, M, -1);
        // printGraph(adjList);
        if(M!=2 && M!=4 && M!=6 && M!=8) {
            cout << "-1" << endl;
            break;
        }
        int source = (sx-1)*N + sy;
        int destination = (vx-1)*N + vy;
        findQuickestPathByDijkstra(adjList, source, destination, N);
        freeGraph(adjList);
        break;
    }
    case 2: {
        // sortest path using bfs
        int N, d, sx, sy, vx, vy;
        cin >> N >> d >> sx >> sy >> vx >> vy;
        vector<vector<Node *>> adjList = getGraphRepresentation(N, 4, d);
        int source = (sx-1)*N + sy;
        int destination = (vx-1)*N + vy;
        // printGraph(adjList);
        findQuickestPathByBFS(adjList, source, destination);
        break;
    }
    case 3: {
        // topological sort
        int N;
        cin >> N;
        // vector<vector<int>> adjMat = getGraphRepresentation(N, 0);
        break;
    }
    default:
        break;
    }
}