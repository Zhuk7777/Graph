#pragma once
#include<string>

class Graph
{
	int size;
	int** adjMatr;

	std::string sortVertex();
	void dfsSort(int i, int* used, std::string& result);
	void dfsComp(int i, int* used, int* components, int color);

public:
	Graph();
	Graph(int _size);
	Graph(int**& newMatr, int _size);
	~Graph();

	void addEdge(int i, int j);
	void addVertex();
	
	void removeEdge(int i, int j);
	void removeVertex(int i);

	void clearGraph();

	bool isEdgeExist(int i, int j);
	bool isVertexExist(int i);

	int getVertex_count();
	int getEdge_count();

	void transposeGraph();
	int* graphComp(std::string sortVer);


};
