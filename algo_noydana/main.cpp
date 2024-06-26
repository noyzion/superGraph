#include "directedGraph.h"
#include "exceptions.h"

int main()
{
	int n, m, u =0, v=0;
	cin >> n;
	cin >> m;
    try {
        DirectedGraph theGraph(n, m);

        for (int i = 0; i < m; i++) 
        {
            cin >> u >> v;
            theGraph.checkValidEdge(u, v);
            theGraph.AddEdge(u, v);
        }

        DirectedGraph superGraph = theGraph.makeSuperGraph();
        cout << superGraph.getVerticesNumber() << " " << superGraph.getEdgesNumber();
    }
    catch (InvalidValueException)
    {
        cout << "Invalid input." << endl;
        exit(1);
    }
    return 0;
}