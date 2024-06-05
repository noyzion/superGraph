#include "directedGraph.h"
int currentRoot;

DirectedGraph::DirectedGraph(int verticesNumber, int edgesNumber) : verticesNumber(verticesNumber),
                                                                    edgesNumber(edgesNumber)
{
    for (int i = 0; i <= verticesNumber; i++)
    {
        vertices.push_back(i);
    }
}

int DirectedGraph::getVerticesNumber()
{
    return verticesNumber;
}

int DirectedGraph::getEdgesNumber()
{
    return edgesNumber;
}

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

list<int> DirectedGraph::GetAdjList(int u)
{
    return vertices[u].getAdjList();

}

void DirectedGraph::AddEdge(int u, int v)
{
    vertices[u].getAdjList().push_back(v);
}

void DirectedGraph::RemoveEdge(int u, int v)
{
    auto& adjList = vertices[u].getAdjList();
    adjList.remove(v);
}


void DirectedGraph::checkValidEdge(int u, int v)
{
    if (u > verticesNumber || u < 1 || v > verticesNumber || v < 1 || u == v || IsAdjacent(u, v))
    {
        cout << "Invalid input.";
        exit(1);
    }

}

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

void DirectedGraph::visit(int u, vector<colors>& colors, vector<int>& roots,    
                          list<int>& finishLoop, DirectedGraph& tempGraph)
{
    roots[u] = currentRoot;
    colors[u] = colors::gray;
    for (int v : vertices[u].getAdjList())
    {
        if (colors[v] == colors::black && roots[v] != roots[u])
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
        if (colors[v] == colors::white)
            visit(v, colors, roots, finishLoop, tempGraph);

    }
    colors[u] = colors::black;
    finishLoop.push_back(u);

}

DirectedGraph DirectedGraph::makeSuperGraph()
{
    DirectedGraph tempGraph;
    tempGraph.MakeEmptyGraph(verticesNumber);

    list<int> mainLoop;
    for (int i = 1; i <= verticesNumber; i++)
        mainLoop.push_back(i);

   list<int> finishList = DFS(mainLoop, tempGraph);
   finishList.reverse();
   tempGraph.MakeEmptyGraph(verticesNumber);
   DirectedGraph gTransopse = transposedGraph();
   gTransopse.DFS(finishList, tempGraph);

   DirectedGraph superGraph;
   superGraph.edgesNumber = tempGraph.edgesNumber;

   for (int i = 1; i <= verticesNumber; i++)
   {
       list<int> adjList = tempGraph.GetAdjList(i);
       if(!adjList.empty())
       {
           tempGraph.RemoveEdge(i, -1);
           vertex newV(i, tempGraph.GetAdjList(i));
           superGraph.vertices.push_back(newV);
           superGraph.verticesNumber++;
       }

   }

   return superGraph;
}
