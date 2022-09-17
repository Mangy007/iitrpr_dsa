#include <iostream>
#include <vector>

using namespace std;

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

vector<vector<int>> getGraphRepresentationInAdjacencyMatrix(int N, int M) {
    vector<vector<int>> adjMat;
    for(int i=0;i<N;i++) {
        vector<int> row;
        for(int j=0;j<M;j++) {
            int input;
            cin >> input;
            row.push_back(input);
        }
        adjMat.push_back(row);
    }
    return adjMat;
}

//test function: later to be deleted
void printGraph(vector<vector<int>> adjMat) {
    for(auto i=adjMat.begin(); i!=adjMat.end(); i++) {
        for(auto j=(*i).begin(); j!=(*i).end(); j++) {
            cout << *j <<" ";
        }
        cout << endl;
    }
}

void findQuickestPathBasedOnM(vector<vector<int>> adjMat, int M, int sx, int sy, int vx, int vy) {
    
}

void performOperationBasedOnQueryType(int query) {
    switch (query)
    {
    case 1: {
        // sortest path by time
        int N, M, sx, sy, vx, vy;
        cin >> N >> M >> sx >> sy >> vx >> vy;
        vector<vector<int>> adjMat = getGraphRepresentationInAdjacencyMatrix(N, N);
        printGraph(adjMat);
        findQuickestPathBasedOnM(adjMat, M, sx, sy, vx, vy);
        break;
    }
    case 2: {
        // bfs
        int N, d, sx, sy, vx, vy;
        cin >> N >> d >> sx >> sy >> vx >> vy;
        vector<vector<int>> adjMat = getGraphRepresentationInAdjacencyMatrix(N, N);
        break;
    }
    case 3: {
        // topological sort
        int N;
        cin >> N;
        vector<vector<int>> adjMat = getGraphRepresentationInAdjacencyMatrix(N, N);
        break;
    }
    default:
        break;
    }
}