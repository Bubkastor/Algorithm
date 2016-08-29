#include "Node.h"

Node::Node()
{
}

Node::Node(std::string name, unsigned int weigth)
	:name(name)
	, weigth(weigth)
{	
}


Node::~Node()
{
}

bool Node::operator==(const Node & compare) const
{
	return name.compare(compare.name) != 0 && weigth != compare.weigth;
}

bool Node::operator!=(const Node & compare) const
{
	return !(*this == compare);
}

bool Node::operator<(const Node & compare) const
{
	return weigth < compare.weigth;
}

bool Node::operator>(const Node & compare) const
{
	return weigth > compare.weigth;
}

std::ostream & operator<<(std::ostream & os, const Node& node)
{
	os << "{ Name: " << node.name << " range: " << node.weigth << " }";
	return os;
}