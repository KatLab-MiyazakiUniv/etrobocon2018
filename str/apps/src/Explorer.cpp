#include "Explorer.h"

void Explorer::createBlockArea()
{
  int nodeCount = neighborsIDList.size();

  // $B%N!<%I$N%]%$%s%?$N%j%9%H$r:n@.(B
  std::vector<Node*> nodePtrs(nodeCount);
  for (int i = 0; i < nodeCount; i++)
  {
    nodeList[i].setNodeID(i);
    nodePtrs[i] = &nodeList[i];
  }

  // $BNY@\%N!<%I$N%]%$%s%?$N%j%9%H$r%N!<%IJ,%j%9%H2=(B
  for (int i = 0; i < nodeCount; i++)
  {
    for (int nodeID : neighborsIDList[i])
    {
      neighbors[i].push_back(nodePtrs[nodeID]);
    }
  }

  // $BNY@\%N!<%I$N%]%$%s%?$N%j%9%H$r3JG<(B
  for (int i = 0; i < nodeCount; i++)
  {
    nodePtrs[i]->setNeighbors(&neighbors[i]);
  }
}
