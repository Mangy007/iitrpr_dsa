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
} Node;

#define INFINITY __INT_MAX__

vector<vector<Node *>> getGraphRepresentation(int N, int M, int d);
vector<vector<Node *>> getGraphRepresentationForDAG(int N);
Node * getMinDistanceNode(bool visit[], set<Node *> sortestPath);
void findQuickestPathByDijkstra(vector<vector<Node *>> graph, int source, int dest, int N);
void findQuickestPathByBFS(vector<vector<Node *>> graph, int source, int dest);
void topologicalSort(vector<vector<Node *>> graph);
void freeGraph(vector<vector<Node *>> graph);
void performOperationBasedOnQueryType(int query);

int main() {

    int testCases;
    cin >> testCases;
    while (testCases--) {
        int query;
        cin >> query;
        performOperationBasedOnQueryType(query);
        cout<<endl;
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

vector<vector<Node *>> getGraphRepresentationForDAG(int N) {
    vector<vector<Node *>> graph;
    int distances[N][N];
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            cin >> distances[i][j];
        }
    }
    vector<Node *> nodes;
    for(int i=0; i<N; i++) { 
        Node * node = (Node *) malloc(sizeof(Node));
        node->key = i+1;
        nodes.push_back(node);
    }

    for(int i=0;i<N;i++) {
        vector<Node *> listOfNodes;
        listOfNodes.push_back(nodes[i]);
        for(int j=0;j<N;j++) {
            if(distances[i][j]==1) listOfNodes.push_back(nodes[j]);
        }
        graph.push_back(listOfNodes);
    }

    return graph;
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

    if(destNode->distance==INFINITY) cout << "-1";
    else cout << destNode->distance;
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

    cout << destNode->distance;
}

void topologicalSort(vector<vector<Node *>> graph) {
    int N = graph.size();
    int inDegrees[N];
    int visitedNode = 0;
    for(int i=0; i<N; i++) {
        inDegrees[i] = 0;
    }
    for(int i=0; i<N; i++) {
        for(int j=1; j<graph[i].size();j++)
            inDegrees[graph[i][j]->key-1] += 1;
    }
    priority_queue<int, vector<int>, greater<int>> explored;
    for(int i=0; i<N; i++) {
        if(inDegrees[i]==0) explored.push(graph[i][0]->key);
    }
    string topologicalSortedSequence = "";

    while (!explored.empty()) {
        int currNode = explored.top();
        explored.pop();
        topologicalSortedSequence += to_string(currNode)+" ";
        for(Node * node: graph[currNode-1]) {
            inDegrees[node->key-1]--;
            if(inDegrees[node->key-1]==0) explored.push(node->key);
        }
        visitedNode++;
    }
    if(visitedNode!=N) cout<<"-1";
    else cout<<topologicalSortedSequence.substr(0,topologicalSortedSequence.length()-1);
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
        vector<vector<Node *>> graph = getGraphRepresentation(N, M, -1);
        if(M!=2 && M!=4 && M!=6 && M!=8) {
            cout << "-1";
            break;
        }
        int source = (sx-1)*N + sy;
        int destination = (vx-1)*N + vy;
        findQuickestPathByDijkstra(graph, source, destination, N);
        freeGraph(graph);
        break;
    }
    case 2: {
        // sortest path using bfs
        int N, d, sx, sy, vx, vy;
        cin >> N >> d >> sx >> sy >> vx >> vy;
        vector<vector<Node *>> graph = getGraphRepresentation(N, 4, d);
        int source = (sx-1)*N + sy;
        int destination = (vx-1)*N + vy;
        findQuickestPathByBFS(graph, source, destination);
        freeGraph(graph);
        break;
    }
    case 3: {
        // topological sort
        int N;
        cin >> N;
        vector<vector<Node *>> graph = getGraphRepresentationForDAG(N);
        topologicalSort(graph);
        freeGraph(graph);
        break;
    }
    default:
        break;
    }
}