#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define INF __INT_MAX__

vector<vector<int>> getGraphRepresentation(int N, int M, int source);
vector<vector<int>> getMST(vector<vector<int>> graph, int source);
void printMST(vector<vector<int>> mst, int root);

int main() {

    int testCases;
    cin >> testCases;
    while (testCases--) {
        int N, M, s;
        cin >> N >> M >> s;
        vector<vector<int>> graph = getGraphRepresentation(N, M, s);
        vector<vector<int>> mst = getMST(graph, s);
        printMST(mst, s);
        cout<<endl;
    }

    return 0;
}

vector<vector<int>> getGraphRepresentation(int N, int M, int source) {
    vector<vector<int>> adjMat(N);

    for(int i=0; i<N; i++) {
        vector<int> outEdges(N);
        adjMat[i] = outEdges;
    }

    for(int i=0; i<M; i++) {
        int vi, vj, edgeWeight;
        cin >> vi >> vj >> edgeWeight;

        if(adjMat[vi-1][vj-1] == 0)
            adjMat[vi-1][vj-1] = edgeWeight;
        else if(adjMat[vi-1][vj-1] > edgeWeight)
                adjMat[vi-1][vj-1] = edgeWeight;
    }
    for(int i=0; i<N; i++) adjMat[i][source-1] = 0;

    return adjMat;
}

bool isAncestor(vector<vector<int>> mst, int source, int dest, int size) {

    if(source==dest) return true;
    for(int i=0; i<size; i++) {
        if(mst[i][source]>0) return isAncestor(mst, i, dest, size);
    }
    return false;
}

bool sortPairs(const pair<int,int> &a, const pair<int,int> &b)
{
    return (a.first < b.first);
}

vector<vector<int>> getMST(vector<vector<int>> graph, int source) {
    
    int size = graph.size();
    bool marked[size];
    vector<vector<int>> mst(size);
    for(int i=0;i<size; i++) marked[i] = false;
    marked[source-1] = true;
    for(int i=0; i<size; i++) {
        vector<int> outEdges(size);
        mst[i] = outEdges;
    }

    // nodes with only incoming edges are added first
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if(graph[j][i]>0) count++;
        }
        if(count==1) {
            marked[i] = true;
            for (int j = 0; j < size; j++) mst[j][i] = graph[j][i];
        }
    }

    for (int i = 0; i < size; i++) {
        int min = INF;
        pair<int, int> index = make_pair(source-1,source-1);
        // sort by pair can be used
        for (int j = 0; j < size; j++) {
            if(!marked[j] && min>graph[i][j] && graph[i][j]>0 && !isAncestor(mst, i, j, size)) {
                min = graph[i][j];
                index = make_pair(i,j);
            }
        }
        if(!(index.first==source-1 && index.second==source-1)) {
            marked[index.second] = true;
            for (int j = 0; j < size; j++) {
                if(j==index.first) mst[j][index.second] = graph[index.first][index.second]; 
                else  mst[j][index.second] = 0;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        if(!marked[i]) {
            vector<pair<int,int>> incomingEdges;
            for(int j = 0; j < size; j++) {
                if(graph[j][i]>0) incomingEdges.push_back(make_pair(graph[j][i], j));
            }
            sort(incomingEdges.begin(), incomingEdges.end());
            // sort(incomingEdges.begin(), incomingEdges.end(), sortPairs);
            for(int j=0; j<incomingEdges.size(); j++) {
                int outEdgeVertex = incomingEdges[j].second;
                if(!isAncestor(mst, outEdgeVertex, i, size)) {
                    mst[outEdgeVertex][i] = incomingEdges[j].first;
                    marked[i] = true;
                    break;
                }
            }
        }
    }

    vector<pair<int,int>> currentMST;
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(mst[j][i]>0) currentMST.push_back(make_pair(j, i));
        }
    }


    for (int i = 0; i < size; i++) {
        bool isIncomingEdgeFromSource = false;

        for(int j=0; j < currentMST.size(); j++) {
            if(currentMST[j].second==i && currentMST[j].first==source-1) {
                isIncomingEdgeFromSource = true;
                break;
            }
        }
        if(isIncomingEdgeFromSource) continue;
        else {
            vector<pair<int,int>> incomingEdges;
            for(int j = 0; j < size; j++) {
                if(graph[j][i]>0) incomingEdges.push_back(make_pair(graph[j][i], j));
            }
            
            sort(incomingEdges.begin(), incomingEdges.end());

            for(int j=0; j < incomingEdges.size(); j++) {
                int currentMSTInEdgeWeight;
                for(int k=0; k < size; k++) {
                    if(mst[k][i]>0) currentMSTInEdgeWeight = mst[k][i];
                }
                if(currentMSTInEdgeWeight>incomingEdges[j].first) {

                    int outEdgeVertex = incomingEdges[j].second;
                    if(!isAncestor(mst, outEdgeVertex, i, size)) {
                        mst[outEdgeVertex][i] = incomingEdges[j].first;
                        for(int k=0; k < currentMST.size(); k++) {
                            if(currentMST[k].second==i) {
                                mst[currentMST[k].first][currentMST[k].second] = 0;
                                currentMST[k].second = incomingEdges[j].first;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    return mst;
}


int getCostFromSource(vector<pair<int,int>> mstSourceDestPairs, vector<vector<int>> mst, int source, int dest, int root) {

    int minCostFromSource = mst[source][dest];
    int prevSource;
    if(source==root-1) return minCostFromSource;
    while(source!=root-1) {
        prevSource = source;
        for(int i=0; i<mstSourceDestPairs.size(); i++) {
            if(mstSourceDestPairs[i].second==source) {
                minCostFromSource += mst[mstSourceDestPairs[i].first][mstSourceDestPairs[i].second];
                source = mstSourceDestPairs[i].first;
                dest = mstSourceDestPairs[i].second;
                break;
            }
        }
        if(prevSource==source) break;
    }
    return minCostFromSource;
}

void printMST(vector<vector<int>> mst, int root) {

    int size = mst.size();
    int minCost = 0;
    for(int i=0; i<size; i++) {
        for (int j = 0; j < size; j++) {
            // cout << "    " << mst[i][j];
            minCost += mst[i][j];
        }
        // cout<<endl;
    }
    cout<< minCost << " ";

    vector<pair<int,int>> mstSourceDestPairs;
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(mst[j][i]>0) mstSourceDestPairs.push_back(make_pair(j, i));
        }
    }
    
    for(int i=0;i<size;i++) {
        int costFromSource = 0;
        // if(i==root-1) {
        //     cout << costFromSource << " ";
        //     continue;
        // }
        if(isAncestor(mst, i, root-1, size)) {
            for(int j=0; j<mstSourceDestPairs.size(); j++) {
                if(mstSourceDestPairs[j].second==i) {
                    costFromSource = getCostFromSource(mstSourceDestPairs, mst, mstSourceDestPairs[j].first, 
                                                            mstSourceDestPairs[j].second, root);
                    break;
                }
            }
        }
        else {
            costFromSource = -1;
        }
        // for(int j=0;j<size;j++) {
        //     if(mst[j][i]>0) costFromSource = getCostFromSource(mstSourceDestPairs, mst, j, i, source);
        // }
        cout << costFromSource << " "; 
    }
    cout << "# ";
    for(int i=0;i<size;i++) {
        if(i==root-1) {
            cout << "0 ";
            continue;
        }
        if(isAncestor(mst, i, root-1, size)) {
            for(int j=0;j<mstSourceDestPairs.size();j++) {
                if(mstSourceDestPairs[j].second==i) cout << mstSourceDestPairs[j].first+1 << " ";
            }
        }
        else {
            cout << "-1 ";
        }
    }
}