#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "main.h"
#include "util.h"
#include "data_structures.h"
#include "stack.h"
#include "heap.h"
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printUsage();
        return 1;
    }

    const char* filename = argv[1];
    const char* graphType = argv[2];
    int flag = atoi(argv[3]);

    if ((strcmp(graphType, "DirectedGraph") != 0 && strcmp(graphType, "UndirectedGraph") != 0) ||
        (flag != 0 && flag != 1)) {
        printUsage();
        return 1;
    }

    readGraph(filename, graphType, flag);
    runInstructions(); 

    return 0;
}

void runInstructions() {
    string command;
    int s, t;

    while (cin >> command) {
        if (command == "Stop") {
            break;
        } else if (command == "PrintADJ") {
            printAdj();
        } else if (command == "SinglePair") {
            cin >> s >> t;
            dijkstra(s, t);
        } else if (command == "SingleSource") {
            cin >> s;
            dijkstra(s, -1);
	else if (command == "PrintPath") {
    cin >> s >> t;
    if (!ranDijkstra || lastSource != s) {
        dijkstra(s, -1); // run Dijkstra again with the correct source
        lastSource = s;
        ranDijkstra = true;
    }
    printPath(s, t);
        } else if (command == "PrintLength") {
            cin >> s >> t;
            printLength(s, t);
        } else {
            cerr << "Invalid instruction." << endl;
        }
    }
}
