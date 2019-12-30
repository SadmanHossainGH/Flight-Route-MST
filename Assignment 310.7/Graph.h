//********************************************************************
// ASU CSE310 Assignment #7
// Name of Author:
// ASU ID:
// Description: This is the header file that defines an undirected graph
//********************************************************************

#include "Edge.h"

using namespace std;

class Graph
{
   private:
      int V, E;   //number of vertices and edges in the graph
      City** setOfCities;   //an array of cities
      Edge** setOfEdges; //an array of edges

   public:
      Graph(int numOfCities, int numOfEdges, City* cityArray[], Edge* edgeArray[]);
      void destructor();
      void make_set(City* aCity);
      City* find_set(City* aCity);
      void link(City* aCity, City* bCity);
      void Union(City* aCity, City* bCity);
      void printEdgeArray();
      void MergeSortEdges();
      void mergeSort(Edge* edgeArray[], int start, int end);
      void merge(Edge* edgeArray[], int start, int mid, int end);

      void MST_Kruskal();
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfCities, int numOfEdges, City* cityArray[], Edge* edgeArray[])
{
	this->V = numOfCities;
	this->E = numOfEdges;
	setOfCities = cityArray;
	setOfEdges = edgeArray;
}

//*******************************************************************
//Destructor
void Graph::destructor()
{
	for (int i = 0; i < E; i++)
	{
		setOfEdges[i]->~Edge();
	}
}

//*******************************************************************
//Given a City, this function creates a new set whose only member is
//the City.
//*******************************************************************
void Graph::make_set(City* aCity)
{
	aCity->parent = aCity;
	aCity->rank = 0;
}

//*******************************************************************
//Given a City, this function returns a pointer to the representative
//of the (unique) set containing 'aCity
//*******************************************************************
City* Graph::find_set(City* aCity)
{
	//if the city is not the representative of the set,
    //find_set is recursed until the reprsentative is found
	if ((aCity->cityName) != (aCity->parent->cityName))
	{
		aCity->parent = find_set(aCity->parent);
	}
	return aCity->parent;
}

//*******************************************************************
//Given two cities, this function checks the dynamic sets that contain
//'aCity' and 'bCity' and update their rank and parent info. accordingly
//*******************************************************************
void Graph::link(City* aCity, City* bCity)
{
	//if cities are disjoint, the alpahabetcially
	//higher vertex is combined with the lower
	//vertex
	if ((aCity->cityName) != (bCity->cityName))
	{
		if ((aCity->cityName) > (bCity->cityName))
		{
			bCity->parent = aCity;
		}
		else 
		{
			aCity->parent = bCity;
			//rank increases to keep balance
			if ((aCity->cityName) < (bCity->cityName))
			{
				bCity->rank = bCity->rank +1;
			}
		}
	}
}

//*******************************************************************
//Given two cities, this function unites the dynamic sets that contain
//'aCity' and 'bCity' into a new set that is the union of the two sets.
//*******************************************************************
void Graph::Union(City* aCity, City* bCity)
{
	link(find_set(aCity), find_set(bCity));
}

//*******************************************************************
//This function print each of the edges of edge array. It can be
//used as an auxillary function to check the MergeSort result
//*******************************************************************
void Graph::printEdgeArray()
{
	for (int i = 0; i < E; i++)
	{
		setOfEdges[i]->printEdge();
	}
}

//*******************************************************************
//This function performs the Merge Sort on the graph edges according
//to the weight. Sort all edges in non-decreasing order
//*******************************************************************
void Graph::MergeSortEdges()
{
	mergeSort(setOfEdges, 0, E-1);
}

//*******************************************************************
//This function performs the Merge Sort on a sub edgeArray.
//*********************************************************************
void Graph::mergeSort(Edge* edgeArray[], int start, int end)
{
	if (start < end)
	{
		//middle values of edgeArray
		int mid = start + (end - start) / 2;

		//splits edgeArray into two subproblems
		mergeSort(edgeArray, start, mid);
		mergeSort(edgeArray, mid + 1, end);

		//merges two sorted subproblems
		merge(edgeArray, start,mid,end);
	}
}

//*******************************************************************
//This function merges the two sorted sub edgeArray.
//*******************************************************************
void Graph::merge(Edge* edgeArray[], int start, int mid, int end)
{

  //get the length of the first half subarray
  int n1 = mid-start+1;
  //get the length of the second half subarray
  int n2 = end-mid; 

  //Dynamically create two new arrays each stored the sorted half
  Edge** left = (Edge **)malloc(sizeof(Edge*) * n1);
  Edge** right = (Edge**)malloc(sizeof(Edge*) * n2);
  
  //initalizes Edges both subarrays 
  for (int i = 0; i < n1; i++)
  {
	  left[i] = (Edge*)malloc(sizeof(Edge));
  }
  for (int j = 0; j < n2; j++)
  {
	  right[j] =  (Edge*)malloc(sizeof(Edge));
  }
  
  //fills both subarrays with half of edgeArray each
  for (int i = 0; i < n1 ; i++)
  {
	  left[i] = edgeArray[start + i];
  }
  for (int j = 0 ; j < n2; j++)
  {
	  right[j] = edgeArray[(mid + 1) +j];
  }

  //travel integer for first subarray
  int s1 = 0;
  //travel integer for second subarray
  int s2 = 0;
  //travel integer for merged array
  int t = start;

  while ((s1 < n1) && (s2 < n2))
  {
	  //fills the merged array with the current smallest 
	  //value between two subarrays
	  if ((left[s1]->getPrice()) <= (right[s2]->getPrice()))
	  {
		 edgeArray[t] = left[s1];
		 s1++;
	  }
	  else
	  {
		 edgeArray[t] = right[s2];
		 s2++;
	  }
	  t++;
  }

  //fills remainder of edgeArray slots
  //with remaining subarray edges
  while (s1 < n1)
  {
	  edgeArray[t] = left[s1];
	  t++;
	  s1++;
  }
  while (s2 < n2)
  {
	  edgeArray[t] = right[s2];
	  t++;
	  s2++;
  }

  //at the end, release the memory left and right subarrays
  free(left);
  free(right);
}


//*******************************************************************
//This function performs the Kruskal algorithm on the graph.
//*******************************************************************
void Graph::MST_Kruskal()
{
   cout << "MST Kruskal Algorithm Result\n" << endl;
   double totalWeight = 0.0;

   //creates a set for each edge in flight path
   for (int i = 0; i < V; i++)
   {
	   make_set(setOfCities[i]);
   }

   //sorts edges by non-decreasing weight
   MergeSortEdges();

   for (int j = 0; j < E; j++)
   {
	   City* aCity = (setOfEdges[j]->getCity1());
	   City* bCity = (setOfEdges[j]->getCity2());

	   //if the represenatives of each disjoint set
	   //are not identical,a new path can be found
	   //with minimum gain
	   if (find_set(aCity) != find_set(bCity))
	   {
		   //the edge is added in MST set as 
		   //part of the path
		   Union(aCity, bCity);

		   //the weight of the new edge is added to the 
		   //path weight
		   totalWeight = totalWeight + setOfEdges[j]->getPrice();
		   setOfEdges[j]->printEdge();
	   }
   }

   cout << "=================================================" << endl;
   cout << "Total Price: " << totalWeight << endl;
}
