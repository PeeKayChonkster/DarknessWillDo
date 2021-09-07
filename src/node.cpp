#include "node.h"
#include "tools.h"
#include "app.h"
#include <ranges>

const std::string Node::type = "Node";

Node::Node() : children(), parent(nullptr)
{
}

Node::Node(Node* parent) : parent(parent) 
{
	if(parent)
		parent->addChild(this);
}

Node::~Node() 
{ 
	if (parent) parent->removeChild(this); 
}

void Node::addChild(Node* node)
{
	if (auto result = std::ranges::find(children, node); result != children.end()) return;	// return if already have this child
	children.push_back(node);
	if (!node->parent) node->start();
	node->parent = this;
	//node->setPosition(getPosition() + node->getPosition());
	//node->setRotation(getRotation() + node->getRotation());
	//node->setScale(getScale() * node->getScale());
}
void Node::removeChild(Node* node)
{
	if (auto result = std::ranges::find(children, node); result != children.end())
	{
		children.erase(result);
		if (node->parent) node->parent = nullptr;
	}
}

void Node::start()
{
}

void Node::update(float deltaTime)
{
}



Node* Node::getParent() const noexcept
{
	return parent;
}
std::vector<Node*>* Node::getChildren()
{
	return &children;
}
Node* Node::getChild(unsigned int index)
{
	return children.size() > index + 1? children[index] : nullptr;
}
////////////////////