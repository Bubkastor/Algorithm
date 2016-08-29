#pragma once
#include <string>
#include <iostream>
class Node
{
public:
	Node();
	Node(std::string name, unsigned int range);
	~Node();

	bool operator ==(const Node& compare) const;
	bool operator !=(const Node& compare) const;
	bool operator <(const Node& compare) const;
	bool operator >(const Node& compare) const;
	friend std::ostream &operator<<(std::ostream& os, const Node& node);

private:
	std::string name;
	unsigned int weigth;
};

