#include "directedGraph.h"
int currentRoot;

DirectedGraph::DirectedGraph(int verticesNumber, int edgesNumber) : verticesNumber(verticesNumber),
edgesNumber(edgesNumber)
{
    if (verticesNumber < 0 || edgesNumber < 0 || edgesNumber > verticesNumber * (verticesNumber - 1))
        throw InvalidValueException();
    for (int i = 0; i <= verticesNumber; i++)
    {
        vertices.push_back(i);
    }
}

//Returns the number of vertices in the graph.
int DirectedGraph::getVerticesNumber() const
{
    return verticesNumber;
}

//Returns the number of edges in the graph.
int DirectedGraph::getEdgesNumber() const
{
    return edgesNumber;
}

//Clears the graph and creates an empty graph with n vertices.
void DirectedGraph::MakeEmptyGraph(int n)
{
	this->verticesNumber = n;
	this->edgesNumber = 0;
    vertices.clear();
    for (int i = 0; i <= n; i++)
    {
        vertices.push_back(i);        
    }
}

//Checks if there is a directed edge from vertex u to vertex 
bool DirectedGraph::IsAdjacent(int u, int v)  
{
    for (vertex vertex : vertices[u].getAdjList())
    {
        if (vertex.getValue() == v)
        {
            return true;
        }
    }
    return false;
}

//Returns the adjacency list of vertex u.
list<int> DirectedGraph::GetAdjList(int u)
{
    return vertices[u].getAdjList();

}

//Adds a directed edge from vertex u to vertex v.
void DirectedGraph::AddEdge(int u, int v)
{
    vertices[u].getAdjList().push_back(v);
}

//Removes the directed edge from vertex u to vertex v.
void DirectedGraph::RemoveEdge(int u, int v)
{
    auto& adjList = vertices[u].getAdjList();
    adjList.remove(v);
}

//check edge validation
void DirectedGraph::checkValidEdge(int u, int v)
{
    if (u > verticesNumber || u < 1 || v > verticesNumber || v < 1 )
    {
        throw OutOfBoundsException();
    }
    if (u == v || IsAdjacent(u, v))
    {
        throw NotSimpleGraph();
    }

}

// Returns the transposed graph of the current graph.
DirectedGraph DirectedGraph::transposedGraph()
{
    DirectedGraph Gtranspose(verticesNumber, edgesNumber);
    for (int i = 1; i <= verticesNumber; i++)
    {
        for (int vertex : vertices[i].getAdjList())
        {
            Gtranspose.AddEdge(vertex, i);
        }
    }
    return Gtranspose;
}

//DFS functions
// return a list of vertices in the order they finish
// and dfs trees
list<int> DirectedGraph::DFS(list<int> mainLoop, DirectedGraph& tempGraph)
{
    vector<colors> colors(verticesNumber+1); // 0 - white, 1 - gray, 2 - black
    vector<int> roots(verticesNumber+1);
    list<int> finishList;

    for (int u = 1; u <= verticesNumber; u++)
    {
        colors[u] = colors::white;
    }
    for (int u : mainLoop)
    {
        if (colors[u] == colors::white)
        {
            currentRoot = u;
            visit(u, colors, roots, finishList, tempGraph);
            tempGraph.vertices[u].getAdjList().push_front(-1);
        }

    }
    return finishList;
}

//Helper function for DFS.
void DirectedGraph::visit(int u, vector<colors>& colors, vector<int>& roots,    
                          list<int>& finishLoop, DirectedGraph& tempGraph)
{
    roots[u] = currentRoot;
    colors[u] = colors::gray;
    for (int v : vertices[u].getAdjList())
    {
        if (colors[v] == colors::black && roots[v] != roots[u])
        {
            checkIfNewRoot(tempGraph, roots, v);
        }
        if (colors[v] == colors::white)
            visit(v, colors, roots, finishLoop, tempGraph);

    }
    colors[u] = colors::black;
    finishLoop.push_back(u);

}

//Creates and returns the supergraph of the current graph.
DirectedGraph DirectedGraph::makeSuperGraph()
{
    DirectedGraph tempGraph;
    tempGraph.MakeEmptyGraph(verticesNumber);

    //build main loop
    list<int> mainLoop;
    for (int i = 1; i <= verticesNumber; i++)
        mainLoop.push_back(i);

    //dfs - using the finish list
   list<int> finishList = DFS(mainLoop, tempGraph);
   //reverse the finish list for the next main loop for the dfs
   finishList.reverse();
   //G transpose
   tempGraph.MakeEmptyGraph(verticesNumber);
   DirectedGraph gTransopse = transposedGraph();
   //dfs on the reverse finish list and gTransopse - return dfs trees
   gTransopse.DFS(finishList, tempGraph);

   //building the super graph
   DirectedGraph superGraph;
   superGraph.edgesNumber = tempGraph.edgesNumber;
   checkAdjListAndAddToGraph(superGraph, tempGraph);

   return superGraph;
}

//Helper function for creating the supergraph.
void DirectedGraph::checkAdjListAndAddToGraph(DirectedGraph& superGraph, DirectedGraph& tempGraph)
{

    for (int i = 1; i <= verticesNumber; i++)
    {
        list<int> adjList = tempGraph.GetAdjList(i);
        if (!adjList.empty())
        {
            tempGraph.RemoveEdge(i, -1); //flag edge
            vertex newV(i, tempGraph.GetAdjList(i)); 
            superGraph.vertices.push_back(newV); 
            superGraph.verticesNumber++;
        }

    }
}

//Helper function for creating the supergraph - if the vertex is not already
// in the graph, add new edge
void DirectedGraph::checkIfNewRoot(DirectedGraph& tempGraph, vector<int>& roots, int v)
{
    if (!tempGraph.vertices[roots[v]].getAdjList().empty())
    {
        if (tempGraph.vertices[roots[v]].getAdjList().back() != currentRoot)
        {
            tempGraph.AddEdge(roots[v], currentRoot);
            tempGraph.edgesNumber++;
        }
    }
    else
    {
        tempGraph.AddEdge(v, currentRoot);
        tempGraph.edgesNumber++;
    }
}