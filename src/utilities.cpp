#include <Dralgeer/utilities.h>

namespace Dralgeer {
    Graph::Graph(int** edges, int numEdges, int numNodes, int maxAdj) : numNodes(numNodes), maxAdj(maxAdj) {
        adjacencyMat = new bool*[numNodes];
        for (int i = 0; i < numNodes; ++i) { adjacencyMat[i] = new bool[numNodes]; }

        // populate the adjacency matrix
        for (int i = 0; i < numEdges; ++i) {
            adjacencyMat[edges[i][0]][edges[i][1]] = 1;
            adjacencyMat[edges[i][1]][edges[i][0]] = 1;
        }
    };

    Graph::Graph(Graph const &graph) : maxAdj(graph.maxAdj) {
        if (adjacencyMat) {
            for (int i = 0; i < numNodes; ++i) { delete[] adjacencyMat[i]; }
            delete[] adjacencyMat;
        }

        numNodes = graph.numNodes;
        adjacencyMat = new bool*[numNodes];

        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                adjacencyMat[i][j] = graph.adjacencyMat[i][j];
            }
        }
    };

    Graph::Graph(Graph &&graph) : maxAdj(graph.maxAdj) {
        numNodes = graph.numNodes;
        adjacencyMat = graph.adjacencyMat;
        graph.adjacencyMat = nullptr;
    };

    Graph& Graph::operator = (Graph const &graph) {
        if (this != &graph) {
            if (adjacencyMat) {
                for (int i = 0; i < numNodes; ++i) { delete[] adjacencyMat[i]; }
                delete[] adjacencyMat;
            }

            maxAdj = graph.maxAdj;
            numNodes = graph.numNodes;
            adjacencyMat = new bool*[numNodes];

            for (int i = 0; i < numNodes; ++i) {
                for (int j = 0; j < numNodes; ++j) {
                    adjacencyMat[i][j] = graph.adjacencyMat[i][j];
                }
            }
        }

        return *this;
    };

    Graph& Graph::operator = (Graph &&graph) {
        if (this != &graph) {
            maxAdj = graph.maxAdj;
            numNodes = graph.numNodes;
            adjacencyMat = graph.adjacencyMat;
            graph.adjacencyMat = nullptr;
        }

        return *this;
    };

    Graph::~Graph() {
        for (int i = 0; i < numNodes; ++i) { delete[] adjacencyMat[i]; }
        delete[] adjacencyMat;
    };

    int* Graph::adjacentNodes(int node, int &numAdj) {
        numAdj = 0;
        int* nodes = new int[maxAdj];

        for (int i = 0; i < numNodes; ++i) { if (adjacencyMat[node][i]) { nodes[numAdj++] = i; }}
        
        return nodes;
    };
}
