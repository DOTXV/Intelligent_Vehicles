#include<iostream> 
#include <list> 
#include <limits.h> 
#include <assert.h>

using namespace std; 
int vertex;
int edge;
list<int> ans;

class Graph 
{ 
	int V; // No. of vertices 
	list<int> *adj; // Pointer to an array containing adjacency lists 
	bool isCyclicUtil(int v, bool visited[], bool *rs); // used by isCyclic() 
public: 
	Graph(int V); // Constructor 
	void addEdge(int v, int w); // to add an edge to graph 
	bool isCyclic(); // returns true if there is a cycle in this graph 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); // Add w to v’s list. 
} 

bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack) 
{ 
	if(visited[v] == false) 
	{ 
		// Mark the current node as visited and part of recursion stack 
		visited[v] = true; 
		recStack[v] = true; 

		// Recur for all the vertices adjacent to this vertex 
		list<int>::iterator i; 
		for(i = adj[v].begin(); i != adj[v].end(); ++i) 
		{ 
			if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
            {
                //cout << *i << endl; 
                ans.push_back(*i);
				return true;
            } 
			else if (recStack[*i])
            {
                //cout << *i << endl;
                ans.push_back(*i);
				return true; 
            }
		} 

	} 
	recStack[v] = false; // remove the vertex from recursion stack 
	return false; 
} 

// Returns true if the graph contains a cycle, else false. 
// This function is a variation of DFS() in https://www.geeksforgeeks.org/archives/18212 
bool Graph::isCyclic() 
{ 
	// Mark all the vertices as not visited and not part of recursion 
	// stack 
	bool *visited = new bool[V]; 
	bool *recStack = new bool[V]; 
	for(int i = 0; i < V; i++) 
	{ 
		visited[i] = false; 
		recStack[i] = false; 
	} 

	// Call the recursive helper function to detect cycle in different 
	// DFS trees 
	for(int i = 0; i < V; i++) 
		if (isCyclicUtil(i, visited, recStack)) 
			return true; 

	return false; 
} 

int main() 
{ 
    int source, target;
    FILE *fptr;
    fptr = fopen("Input2.dat", "r");

    fscanf(fptr, "%d%d", &vertex, &edge);

	// Create a graph given in the above diagram 
	Graph g(vertex);

    for (int i = 0; i < edge; i++)
    {
        fscanf(fptr, "%d%d", &source, &target);
        //cout << source << " " << target << endl;
        g.addEdge(source, target);
    }
	//g.addEdge(0, 1); 

	if(g.isCyclic())
    { 
		cout << "Yes\n" << ans.back();
        ans.pop_back();
        cout << " " << ans.back() << "\n";
    }
    else
		cout << "No\n"; 
	return 0;
     
} 
