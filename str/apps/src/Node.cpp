#include "Node.h"

void Node::setNeighbors(std::vector<Node*>* nodes)
{
  neighbors = nodes;
}

std::vector<Node*>* Node::getNeighbors()
{
  return neighbors;
}

void Node::setNodeID(std::int8_t nodeNumber)
{
  nodeID = nodeNumber;
}

std::int8_t Node::getNodeID()
{
  return nodeID;
}

void Node::setHasBlock(bool exists)
{
  blockExists = exists;
}

bool Node::hasBlock()
{
  return blockExists;
}

void Node::setPosition(std::int8_t x, std::int8_t y)
{
  position.x = x;
  position.y = y;
}

std::int8_t Node::getPositionX()
{
  return position.x;
}

std::int8_t Node::getPositionY()
{
  return position.y;
}
