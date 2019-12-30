//************************************************************************
// ASU CSE310 Assignment #7
// ASU ID: 1212998226
// Name: Sadman Hossain
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
//**************************************************************************

#include "Graph.h"

using namespace std;

void getArrCityInfo(string& oneArrCityInfo, string& arrCityName, double& price);
City* searchCity(City* oneCityArray[],int size, string oneCityName);
bool cityExists(City* oneCityArray[], int arraySize, string oneCityName);

int main()
{
	//number of vertices and edges
    int V, E;       

    cin >> V >> E;
    cin.ignore(20, '\n');

    //a City array used to store all vertices (Cities) of the graph
    City** cityArray = (City **)malloc(sizeof(City*)*V);

	//initalizes each City pointer in cityArray
	for (int i = 0; i < V; i++)
	{
		cityArray[i] = (City*)malloc(sizeof(City));
		cityArray[i] = NULL;
	}

    //an array used to store all edges of the graph
    Edge** edgeArray = (Edge**)malloc(sizeof(Edge*)*E);

	//initalizes each Edge pointer in edgeArray
	for (int j = 0; j < E; j++)
	{
		edgeArray[j] = (Edge*)malloc(sizeof(Edge));
		edgeArray[j] = NULL;
	}

	//index for cityArray and edgeArray
    int i = 0, j = 0;

	//initalizes city pointers for user inputted inersetion
	//and edge insertion
	struct City* city1 = (City*)malloc(sizeof(City));
	struct City* city2 = (City*)malloc(sizeof(City));

	//gets depature and arrival string for each city
    string oneLine;
    getline(cin, oneLine);

    while(oneLine.compare("End") != 0)
    {
        //gets one line of the input, extracts the depature
        //city
		string delimiter = ",";
		int pos = oneLine.find(delimiter);
		string deptCity = oneLine.substr(0, pos);

		//checks if depature City already exists in CityArray
		bool exists = cityExists(cityArray, V, deptCity);

		// if found,returns pointer from CityArray
		if (exists == true)
		{
			city1 = searchCity(cityArray, V, deptCity);
		}
		//else, a new City object is made and inserted into 
		//CityArray
		else
		{
			city1 = new City(deptCity);
			cityArray[i] = city1;
			i++;
		}
		oneLine.erase(0, pos + delimiter.length());

		while (!oneLine.empty())
		{
			if (oneLine.compare(",") != 0)
			{
				//extracts the arrival city info.
				string arrCity = " ";
				double price = 0.0;
				getArrCityInfo(oneLine, arrCity, price);

				//checks if arrival City already exists in cityArray
				bool exists = cityExists(cityArray, V, arrCity);

				// if found,returns pointer from CityArray
				if (exists == true)
				{
					city2 = searchCity(cityArray, V, arrCity);
				}
				//else, a new City object is made and inserted into 
		        //CityArray
				else
				{
					city2 = new City(arrCity);
					cityArray[i] = city2;
					i++;
				}

				//by using the two cities we got above, create a new edge, add
				//it inside edgeArray
				Edge* aNewEdge = (Edge*)malloc(sizeof(Edge));
				aNewEdge = new Edge(city1, city2, price);

				edgeArray[j] = aNewEdge;
				j++;
			}
			//no arrival cities exist in the line. The line is erased and 
			//the next line is called
			else
			{
				oneLine.erase(0, oneLine.length());
			}
		}
      //gets next line
      getline(cin, oneLine);
    } //repeat 'End' is found

	//creates new Graph object
	Graph flightPath = Graph(V, E, cityArray, edgeArray);

    //Run Kruskal MST algorithm on graph
	flightPath.MST_Kruskal();

	//deconstructs Edges and Graph as
	//program finishes
	for (int i = 0; i < E; i++)
	{
		edgeArray[i]->~Edge();
	}
	flightPath.destructor();
}

//****************************************************************
//By giving a string, for example 'Dallas(456.5)', this function
//extracts the contents and stores the arrival info (city
//name and price) into variables to be used in City and Edge object
//****************************************************************
void getArrCityInfo(string& oneArrCityInfo, string& arrCityName, double& price)
{
   //extracts city name
   string delimiter1 = "(", delimiter2 = ")";
   int pos=oneArrCityInfo.find(delimiter1);
   string token = oneArrCityInfo.substr(0,pos);
   arrCityName = token;

   //erases city names form String
   oneArrCityInfo.erase(0, pos+delimiter1.length());

   //extracts and erases flight price from String
   pos = oneArrCityInfo.find(delimiter2);
   token = oneArrCityInfo.substr(0,pos);
   price = stod(token);
   oneArrCityInfo.erase(0, pos + delimiter2.length() + 1);
}

//*********************************************************************
//By giving a string, for example 'Dallas(456.5)', this function
//searches the CityArray for an instance of that name. Returns 
//'true' if city name is found in list
//****************************************************************
bool cityExists(City* oneCityArray[], int arraySize, string oneCityName)
{
	//returns false if list is empty
	if (oneCityArray[0] == NULL)
	{
		return false;
	}

	//searches cityArray for City with given name
	for (int i = 0; i < arraySize; i++)
	{
		if (oneCityArray[i] != NULL)
		{
			//returns true if found
			if (oneCityArray[i]->cityName == oneCityName)
			{
				return true;
			}
		}
	}
	//else returns false
	return	false;
}

//*********************************************************************
//Given a city name, this function searches cityArray and it return a
//pointer points to the City if it already exists, otherwise it returns NULL
//****************************************************************
City* searchCity(City* oneCityArray[], int arraySize, string oneCityName)
{
	//searches cityArray for City with given name
	for (int i = 0; i < arraySize; i++)
	{
		//returns ponter to city if found
		if (oneCityArray[i]->cityName == oneCityName)
		{
			return oneCityArray[i];
		}
	}
	//else returns NULL
	return	NULL;
}

