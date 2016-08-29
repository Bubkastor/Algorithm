#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

struct City
{
	string name;
	int range;
};

struct Road
{
	int in;
	int to;
	int cost;
};

struct RoadTotalCost
{
	int in;
	int to;
	int totalCost;
};

typedef vector<City> ArrayCitys;
typedef vector<Road> ArrayRoads;
typedef vector<RoadTotalCost> ArrayRoadsTotalCost;
Road GetRoad(ArrayRoads roads, int city, int to);
ArrayRoads GetRoads(ArrayRoads roads, int city, set<int> old);
ArrayRoads GetRoads(ArrayRoads roads, int city);

int SumPathCities(int start, int goal, ArrayRoads roads, ArrayCitys citys) 
{
	int result = 0;

	queue<int> queryTop;
	queryTop.push(start);
	vector<bool> used(citys.size());
	used[start] = true;

	vector<int> d(citys.size());
	vector<int> p(citys.size());
	p[start] = -1;

	set<int> oldCity;
	oldCity.insert(start);
	ArrayRoads currentRoad = GetRoads(roads, start);
	
	while (!queryTop.empty())
	{
		int vertex = queryTop.front();
		queryTop.pop();
		currentRoad = GetRoads(roads, vertex);

		for (size_t i = 0; i < currentRoad.size(); i++)
		{
			if (!used[currentRoad[i].to])
			{
				used[currentRoad[i].to] = true;
				queryTop.push(currentRoad[i].to);
				d[currentRoad[i].to] = d[currentRoad[i].in] + 1;
				p[currentRoad[i].to] = currentRoad[i].in;
			}
						
		}				
	}
	
	if (!used[goal])
		cout << "No path!";
	else {
		vector<int> path;
		for (int v = goal; v != -1; v = p[v])
			path.push_back(v);

		reverse(path.begin(), path.end());


		for (size_t i = 1; i < path.size(); ++i)
			result += GetRoad(roads, path[i - 1], path[i]).cost;
			
	}
	return result;	
}

Road GetRoad(ArrayRoads roads, int city, int to)
{
	ArrayRoads result = GetRoads(roads, city);
	Road newResult;
	for (size_t i = 0; i < result.size(); i++)
	{
		Road road = result[i];
		if (road.to == to)
		{
			newResult = road;
			break;
		}
	}

	return newResult;

}

ArrayRoads GetRoads(ArrayRoads roads, int city, set<int> old)
{
	auto arrayRoads = GetRoads(roads, city);
	ArrayRoads result;
	
	for (auto road: arrayRoads)
	{
		bool add = true;
		for (auto usedCity: old)
		{
			if (road.to == usedCity)
			{
				add = false;
				break;
			}			
		}
		if (add)
			result.push_back(road);
	}
	return result;
}

ArrayRoads GetRoads(ArrayRoads roads, int city) {
	ArrayRoads result;
	for (auto road : roads)	
		if (city == road.in) 
			result.push_back(road);
	return result;	
}

ArrayRoadsTotalCost GetTotalCostRoads(ArrayRoads roads, ArrayCitys citys, int beforeCost) {
	ArrayRoadsTotalCost result;
	for (auto it : roads) {
		result.push_back({
			it.in,
			it.to,
			it.cost + citys[it.to].range + beforeCost
		});	
	}
	return result;
}

vector<City> A(int start, int goal, ArrayRoads roads, ArrayCitys citys) {

	ArrayRoadsTotalCost myPath;
	ArrayRoadsTotalCost otherPath;

	set<int> usedCity;
	usedCity.insert(start);
	int beforeCost = 0;
	int currentCity = start;

	while (currentCity != goal) {
		ArrayRoads currentRoad = GetRoads(roads, currentCity, usedCity);

		ArrayRoadsTotalCost currentRoadsTotlCost = GetTotalCostRoads(currentRoad, citys, beforeCost);

		RoadTotalCost min_before;


		RoadTotalCost min_iterator = *min_element(currentRoadsTotlCost.begin(), currentRoadsTotlCost.end(), [](RoadTotalCost a, RoadTotalCost b) -> bool {
			return (a.totalCost < b.totalCost);
		});

		
		
		for(size_t i= 0; i < currentRoadsTotlCost.size(); i++)
		{
			RoadTotalCost it = currentRoadsTotlCost[i];
			if ((it.in == min_iterator.in)
				&& (it.to == min_iterator.to)
				&& (it.totalCost == min_iterator.totalCost))
			{
				currentRoadsTotlCost.erase(currentRoadsTotlCost.begin() + i);
				break;
			}
		}	
		myPath.push_back(min_iterator);

		otherPath.insert(otherPath.end(), currentRoadsTotlCost.begin(), currentRoadsTotlCost.end());
		if (!otherPath.empty())
			min_before = *min_element(otherPath.begin(), otherPath.end(), [](RoadTotalCost a, RoadTotalCost b) -> bool {
			return (a.totalCost < b.totalCost);
		});

		if (min_before.totalCost < min_iterator.totalCost) {
			otherPath.push_back(min_iterator);
			min_iterator = min_before;
			for (size_t i = 0; i < otherPath.size(); i++)
			{
				RoadTotalCost it = otherPath[i];
				if ((it.in == min_iterator.in)
					&& (it.to == min_iterator.to)
					&& (it.totalCost == min_iterator.totalCost))
				{
					otherPath.erase(otherPath.begin() + i);
					break;
				}
			}
		}
		currentCity = min_iterator.to;
		usedCity.insert(min_iterator.to);
		beforeCost = SumPathCities(start, min_iterator.to, roads, citys);
	
		
		std::cout <<  citys[min_iterator.to].name[0] << "-";
		
	}
	std::cout << endl;
	
	return vector<City>();
}

void main()
{
	ArrayCitys citys = {
		{ "Arard", 366 },	    //0
		{ "Bucharest", 0 },     //1
		{ "Craiova", 160 },	    //2
		{ "Drobeta", 242 },		//3
		{ "Eforie", 161 },		//4
		{ "Fagaras", 176 },		//5
		{ "Giurgiu", 77 },		//6
		{ "Hirsiva", 151 },		//7
		{ "Iasi", 226 },		//8
		{ "Lugoj", 244 },		//9
		{ "Mehadia", 241 },		//10
		{ "Neamt", 234 },		//11
		{ "Oradea", 380 },		//12
		{ "Pitesti", 100 },		//13
		{ "RimnicuVilcea", 193 },//14
		{ "Sibiu", 253 },		//15
		{ "Timisoara", 329 },	//16
		{ "Urziceni", 80 },		//17
		{ "Vaslui", 199 },		//18
		{ "Zerind", 374 }		//19
	};
	
	ArrayRoads roads = {
		{ 0, 15, 140 }, { 0, 16, 118 }, { 0, 19, 75 },
		{ 1, 5, 211 }, { 1, 6, 90 }, { 1, 13, 101 },  { 1, 17, 85 },
		{ 2, 3, 120 }, { 2, 13, 138 }, { 2, 14, 146 },
		{ 3, 2, 120 }, { 3, 10, 75 },
		{ 4, 7, 86 },
		{ 5, 1, 211 }, { 5, 15, 99 },
		{ 6, 1, 90 },
		{ 7, 4, 86 }, { 7, 17, 98 },
		{ 8, 11, 87 }, { 8, 18, 92 },
		{ 9, 10, 70 }, { 9, 16, 111 },
		{ 10, 3, 75 }, { 10, 9, 70 },
		{ 11, 8, 87 },
		{ 12, 15, 151 }, { 12, 19, 71 },
		{ 13, 1, 101 }, { 13, 2, 138 }, { 13, 14, 97 },
		{ 14, 2, 146 }, { 14, 13, 97 }, { 14, 15, 80 },
		{ 15, 0, 140 }, { 15, 5, 99 }, { 15, 12, 151 }, { 15, 14, 80 },
		{ 16, 0, 118 }, { 16, 9, 111 },
		{ 17, 1, 85 }, { 17, 7, 98 }, { 17, 18, 142 },
		{ 18, 8, 92 }, { 18, 17, 142 },
		{ 19, 0, 75 }, { 19, 12, 71 }
	};

	//cout << SumPathCities(0, 1, roads, citys);
	int start = 0;
	int goal = 1;
	std::cout << citys[start].name[0] << "-";
	A(start, goal, roads, citys);
}