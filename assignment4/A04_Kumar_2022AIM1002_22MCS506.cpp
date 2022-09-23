#include <iostream>
#include <vector>

using namespace std;

typedef struct Node {
    int key;
    int height;
} Node;

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

vector<vector<Node *>> getGraphRepresentation(int N, int M) {
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
        // adjList.push_back(i+1);
        for(int j=0; j<N; j++) {
            vector<Node *> nodes;
            nodes.push_back(heights[i][j]);
            if(M==2) {
                if(j+1<N) nodes.push_back(heights[i][j+1]);
                if(i+1<N) nodes.push_back(heights[i+1][j]);
            }
            else if(M==4) {
                if(j-1>0) nodes.push_back(heights[i][j-1]);
                if(i-1>0) nodes.push_back(heights[i-1][j]);
                if(j+1<N) nodes.push_back(heights[i][j+1]);
                if(i+1<N) nodes.push_back(heights[i][j+1]);
            }
            else if(M==6) {
                if(j-1>0) nodes.push_back(heights[i][j-1]);
                if(i-1>0) nodes.push_back(heights[i-1][j]);
                if(j+1<N) nodes.push_back(heights[i][j+1]);
                if(i+1<N) nodes.push_back(heights[i][j+1]);
                if(i-1>0 && j+1<N) nodes.push_back(heights[i-1][j+1]);
                if(i+1<N && j+1<N) nodes.push_back(heights[i+1][j+1]);
            }
            else if(M==8) {
                if(j-1>0) nodes.push_back(heights[i][j-1]);
                if(i-1>0) nodes.push_back(heights[i-1][j]);
                if(j+1<N) nodes.push_back(heights[i][j+1]);
                if(i+1<N) nodes.push_back(heights[i][j+1]);
                if(i-1>0 && j+1<N) nodes.push_back(heights[i-1][j+1]);
                if(i+1<N && j+1<N) nodes.push_back(heights[i+1][j+1]);
                if(i-1>0 && j-1>0) nodes.push_back(heights[i-1][j-1]);
                if(i+1<N && j-1>0) nodes.push_back(heights[i+1][j-1]);
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
    // for(auto i=adjList.begin(); i!=adjList.end(); i++) {
    //     for(auto j=(*i).begin(); j!=(*i).end(); j++) {
    //         cout << (*j)->key << "(" << (*j)->height << ") ->";
    //     }
    //     cout << endl;
    // }
}

void findQuickestPath(vector<vector<Node *>> graph, int source, int dest) {

}

void performOperationBasedOnQueryType(int query) {
    switch (query)
    {
    case 1: {
        // sortest path by time
        int N, M, sx, sy, vx, vy;
        cin >> N >> M >> sx >> sy >> vx >> vy;
        vector<vector<Node *>> adjList = getGraphRepresentation(N, M);
        printGraph(adjList);
        int source = (sx-1)*N + sy;
        int destination = (vx-1)*N + vy;
        findQuickestPath(adjList, source, destination);
        break;
    }
    case 2: {
        // bfs
        int N, d, sx, sy, vx, vy;
        cin >> N >> d >> sx >> sy >> vx >> vy;
        // vector<vector<int>> adjMat = getGraphRepresentation(N, 4);
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