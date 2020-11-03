// Program to print BFS traversal from a given 
// source vertex. BFS(int s) traverses vertices 
// reachable from s. 
#include<iostream> 
#include <fstream>
#include <list> 
#include <vector>
#include <algorithm>
#include <string>
#include <omp.h>
#include <chrono>


// This class represents a directed graph using 
// adjacency list representation 
class Graph
{
	int V; // No. of vertices 

	// Pointer to an array containing adjacency 
	// lists 
	std::list<int>* adj;
public:
	Graph(int V); // Constructor 

	// function to add an edge to graph 
	void addEdge(int v, int w);

	// prints BFS traversal from a given source s 
	std::list<int> BFS(int s);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new std::list<int>[V*2];

}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v�s list. 
}

std::list<int> Graph::BFS(int s)
{	
	
	// Mark all the vertices as not visited 
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Create a queue for BFS 
	std::list<int> queue;
	std::list<int> out_seq;
	
	// Mark the current node as visited and enqueue it 
	visited[s] = true;
	queue.push_back(s);

	// 'i' will be used to get all adjacent 
	// vertices of a vertex 
	std::list<int>::iterator i;

	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		s = queue.front();
		out_seq.push_back(s);
		queue.pop_front();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited, 
		// then mark it visited and enqueue it 


		#pragma omp parallel
		{

			for (i = adj[s].begin(); i != adj[s].end(); ++i)
			{
				//int ID = omp_get_thread_num();
				//cout << "thread id is " << ID << "\n";

				if (!visited[*i])
				{
					visited[*i] = true;
					queue.push_back(*i);
				}
			}
		}

		


	}
	return out_seq;
}

template< typename T, typename A >
void write_to_file(const std::list<T, A>& seq, const char* path2file)
{
	std::ofstream file(path2file);
	auto first = true;
	file << "[";
	for (const auto& v : seq) {
		if (!first) { file << ","; }
		first = false;
		file << v;
	}
	file << "]" << std::endl;
	file.close();
}

// Driver program for graph class 
int main(int argc, char*argv[])
{	
	//auto start = std::chrono::high_resolution_clock::now();
	
	
	// Read in data 
	std::string line;
	//std::vector<std::pair<int, int>> data;
	std::ifstream myfile(argv[1]);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			// ... Only one line
		}
		myfile.close();
	}
	
	Graph g(20000);
	
	// Store data
	//std::vector<std::pair<int, int>> data;
	// Find first comma 
	int first, second;
	unsigned int lbracket, comma, rbracket;

	lbracket = line.find("(");
	// While there is another bracket
	while (lbracket < unsigned(line.size()))
	{
		// Find indices of "(", ",", ")"
		comma = line.find(",", lbracket);
		rbracket = line.find(")", lbracket);
		
		// Read int from substring
		first = std::stoi(line.substr(lbracket + 1, comma - 1));
		second = std::stoi(line.substr(comma + 1, rbracket - 1));
		
		// Find next left bracket
		lbracket = line.find("(", lbracket + 1);
		
		// Add pair to graph
		g.addEdge(first, second);
		//data.push_back(std::make_pair(first, second));
	}
	
	std::list<int> ans = g.BFS(0);
	
	//write to file;
	write_to_file(ans, "./ans.txt");

	//auto stop = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	//std::cout << duration.count() << " milliseconds\n";

	return 0;
}
