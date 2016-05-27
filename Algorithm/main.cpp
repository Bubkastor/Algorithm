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
ArrayRoads GetRoads(ArrayRoads roads, int city, set<int> oldCity);
ArrayRoads GetRoads(ArrayRoads roads, int city);

int SumPathCities(int start, int goal, ArrayRoads roads, ArrayCitys citys) 
{
	int result = 0;
	int currentCity = start;	
	bool isFinding = false;

	queue<int> queryTop;
	queryTop.push(start);
	vector<bool> used(citys.size());
	used[start] = true;

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
			}
						
		}		
		currentRoad.clear();
		for (auto it: oldCity)
		{
			auto newRoad = GetRoads(roads, it, oldCity);
			currentRoad.insert(currentRoad.end(), newRoad.begin(), newRoad.end());
		}
		
	}
	std::cout << "findid";

	return 1;

	
}

ArrayRoads GetRoads(ArrayRoads roads, int city, set<int> oldCity)
{
	ArrayRoads result = GetRoads(roads, city);
	ArrayRoads newResult;
	for (size_t i = 0; i < result.size(); i++)
	{
		Road road = result[i];
		bool add = true;
		for (auto it: oldCity)
			if (road.to == it)
			{
				add = false;
				break;
			}
		if (add)
			newResult.push_back(result[i]);
	}

	return newResult;

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
	ArrayRoads allRoads;
	int beforeCost = 0;
	int currentCity = start;

	while (currentCity != goal) {
		ArrayRoads currentRoad = GetRoads(roads, currentCity);
		allRoads.insert(allRoads.end(), currentRoad.begin(), currentRoad.end());

		ArrayRoadsTotalCost currentRoadsTotlCost = GetTotalCostRoads(currentRoad, citys, beforeCost);

		RoadTotalCost min_before;


		RoadTotalCost min_iterator = *min_element(currentRoadsTotlCost.begin(), currentRoadsTotlCost.end(), [](RoadTotalCost a, RoadTotalCost b) -> bool {
			return (a.totalCost < b.totalCost);
		});

		
		
		for(int i= 0; i < currentRoadsTotlCost.size(); i++)
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
			for (int i = 0; i < otherPath.size(); i++)
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
		for (auto it : allRoads)
			if ((it.in == min_iterator.in) && (it.to == min_iterator.to))
				beforeCost += it.cost;
		
		std::cout << citys[min_iterator.in].name << "-" << citys[min_iterator.to].name << "-" << min_iterator.totalCost << endl;

		
	}
	std::cout << endl;
	for (auto it : myPath)
		std::cout << citys[it.in].name << "-" << citys[it.to].name << "-" << it.totalCost << endl;
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

	SumPathCities(0, 2, roads, citys);
	//answer =  A(0, 1, roads, citys);



}
