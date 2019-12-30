//********************************************************************
// ASU CSE310 Assignment #7
// Name of Author: Sadman Hossain
// ASU ID:1212998226
// Description: this header file defines an edge in the graph. Each edge
//              has 3 attributes, namely two Cities and the air ticket
//              price between them.
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//City represents one vertex of the graph
struct City
{
	//atriutes for disjoint vertices
    string cityName;
    int rank;
    struct City* parent;

    //constructor
    City(string name)
    {
       cityName = name;
       rank = 0;
       parent = NULL;
    }
};

//class Edge represents one edge of the graph
class Edge
{
    private:
       struct City* city1;
       struct City* city2;
       double price;

	public:
	  Edge(City* city1, City* city2, double price);
      ~Edge();
      City* getCity1();
      City* getCity2();
      double getPrice();
      void printEdge();
};

//constructor
Edge::Edge(City* newCity1, City* newCity2, double newPrice)
{
     city1 = newCity1;
	 city2 = newCity2;
	 price = newPrice;
}

//Destructor
Edge::~Edge()
{
	city1 = NULL;
	city2 = NULL;
	price = 0;
}

//Accessor for city1
City* Edge::getCity1()
{
	return city1;
}

//Accessor for city2
City* Edge::getCity2()
{
	return city2;
}

//Accessor for price
double Edge::getPrice()
{
	return price;
}

//prints vertieces of edge in desired format
void Edge::printEdge()
{
   cout << left;
   cout << setw(15) << city1->cityName
        << setw(8) << "<--->"
        << setw(15) << city2->cityName
        << setw(3) << " = "
        << setw(8) << right << fixed << setprecision(2) << getPrice()
        << endl;
}
