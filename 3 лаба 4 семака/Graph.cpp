#include "Graph.h"

std::string Graph::sortVertex()
{
	int* used = new int[size];
	std::string result;
	for (int i = 0; i < size; i++)
		used[i] = 0;

	for (int i = 0; i < size; i++)
		if (!used[i])
			dfsSort(i, used,result);

	return result;
}

void Graph::dfsSort(int i, int* used,std::string &result)
{
	used[i] = 1;
	for (int j = 0; j < size; j++)
		if (adjMatr[i][j] == 1)
			dfsSort(j, used,result);
	result.insert(result.begin(), i + '0');
}

void Graph::dfsComp(int i, int* used, int* components,int color)
{
	used[i] = 1;
	components[i] = color;
	for (int j = 0; j < size; j++)
		if (adjMatr[i][j] == 1)
			dfsComp(j, used, components, color);
}

Graph::Graph() :size(0)
{
	adjMatr = nullptr;
}

Graph::Graph(int _size):size(_size)
{
	adjMatr = new int* [size];
	for (int i = 0; i < size; i++)
		adjMatr[i] = new int[size];
}

Graph::Graph(int**& newMatr, int _size)
{
	clearGraph();
	adjMatr = newMatr;
	size = _size;
	newMatr = nullptr;

}

Graph::~Graph()
{
	clearGraph();
}

void Graph::addEdge(int i, int j)
{
	if (i < size && j < size && i >= 0 && j >= 0)
		adjMatr[i][j] = 1;
}

void Graph::addVertex()
{
	int** newMatr = new int* [size + 1];
	for (int i = 0; i < size + 1; i++)
		newMatr[i] = new int[size + 1];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			newMatr[i][j] = adjMatr[i][j];

	for (int i = 0; i < size; i++)
		delete adjMatr[i];
	delete[] adjMatr;

	size++;

	adjMatr = newMatr;

}

void Graph::removeEdge(int i, int j)
{
	if (i < size && j < size && i >= 0 && j >= 0)
		adjMatr[i][j] = 0;
}

void Graph::removeVertex(int i)
{
	int** newMatr = new int* [size -1];
	for (int j = 0; j < size -1; j++)
		newMatr[j] = new int[size -1];

	for (int j = 0,int x=0; j < size-1; j++) {
		if (j == i) x = 1;
		for (int n = 0; n < size-1; n++)
		{
			if (n == i) x = 1;
			newMatr[j][n] = adjMatr[j+x][n+x];
		}
	}

	for (int i = 0; i < size; i++)
		delete adjMatr[i];
	delete[] adjMatr;

	size--;

	adjMatr = newMatr;
}

void Graph::clearGraph()
{
	for (int i = 0; i < size; i++)
		delete adjMatr[i];
	delete[] adjMatr;

	adjMatr = nullptr;
	size = 0;
}

bool Graph::isEdgeExist(int i, int j)
{
	return adjMatr[i][j] == 1;
}

bool Graph::isVertexExist(int i)
{
	return i < size;
}

int Graph::getVertex_count()
{
	return size;
}

int Graph::getEdge_count()
{
	int count = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (adjMatr[i][j] == 1)
				count++;
	return count;
}

void Graph::transposeGraph()
{
	int** newMatr = new int* [size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (adjMatr[i][j] == 1)
				newMatr[j][i] = 1;

	int _size = size;
	clearGraph();
	size = _size;
	adjMatr = newMatr;
}

int* Graph::graphComp(std::string sortVer)
{
	int color = 1;
	sortVer = sortVertex();
	int* components = new int[size];

	int* used = new int[size];
	for (int i = 0; i < size; i++)
		used[i] = 0;

	for (int i = 0; i < size; i++)
	{
		color++;
		if (used[sortVer[i] - '0'] == 0)
			dfsComp(sortVer[i]-'0', used, components,color);
	}

	return components;
}


