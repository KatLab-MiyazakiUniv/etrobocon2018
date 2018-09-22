/**
 * @file Node.h
 * @brief A*アルゴリズムにおけるノードクラス
 * @author Keisuke MORI, Takuya SATO
 */
#ifndef __NODE__
#define __NODE__

#include <vector>
#include <memory>
#include <cstdlib>
#include <cstdint>

/**
 * <p> A*アルゴリズムにおけるノードクラス <p>
 *
 * <p>
 * ノード、およびノード間の関係を作成できる。
 * {@link #setNeighbors(std::vector<Node*>*)} で関係があるノードのポインタのリストのポインタを設定できる。
 * このセッターを駆使することで、双方向グラフを作成できる。
 * 作成方法は、Example1とExample2を参照すればよい。
 * </p>
 *
 * <p>
 * なお、Example1は簡単な双方向グラフのため、3つのインスタンスのポインタを直接設定している。
 * Example2はノードと関係がたくさんあるため、ノードのポインタのリストを用いて、また隣接ノードIDの二重リストを用いて、動的に生成している。
 * Example2の手法を用いれば、多角形が存在するグラフでも簡単に生成できると考えられる。
 * </p>
 *
 * <p>
 * 現在は、Node間のコストを表現できない。
 * ノードのポインタをキーに、コストを値にしたハッシュをメンバ変数に保持することで、表現できると考える。
 * 一方で、このクラスが保持する必要性は必ずしもないため、このクラスのインスタンス保持者が持てばよいという発想も間違いではない。
 * </p>
 *
 * <p> Example1 </p>
 *
 * <p>
 * Example1 <br>
 * node2に2つのneighborsが存在する場合 (node1 - node2 - node3)
 * </p>
 *
 * <pre>
 *     {@code
 *     Node node1(1);
 *     Node node2(2);
 *     Node node3(3);
 *
 *     std::vector<Node*> neighbors1 = {&node2}; // node1->node2
 *     std::vector<Node*> neighbors2 = {&node1, &node3}; // node1<-node2->node3
 *     std::vector<Node*> neighbors3 = {&node2}; // node2<-node3
 *
 *     node1.setNeighbors(&neighbors1);
 *     node2.setNeighbors(&neighbors2);
 *     node3.setNeighbors(&neighbors3);
 *
 *     auto actual1 = node1.getNeighbors();
 *     auto actual2 = node2.getNeighbors();
 *     auto actual3 = node3.getNeighbors();
 *
 *     ASSERT_EQ(&node1, actual1->at(0)->getNeighbors()->at(0)); // node1->node2->node1
 *     ASSERT_EQ(&node2, actual2->at(0)->getNeighbors()->at(0)); // node2->node1->node2
 *     ASSERT_EQ(&node2, actual2->at(1)->getNeighbors()->at(0)); // node2->node3->node2
 *     ASSERT_EQ(&node3, actual3->at(0)->getNeighbors()->at(1)); // node3->node2->node3
 *     }
 * </pre>
 *
 * <p>
 * Example2 <br>
 * ETロボコン2018のブロック並べエリアの場合<br><br>
 *
 * 0 - 1 - 2 - 3 <br>
 * |   |   |   | <br>
 * 4 - 5 - 6 - 7 <br>
 * |   |   |   | <br>
 * 8 - 9 - 10- 11<br>
 * |   |   |   | <br>
 * 12- 13- 14- 15
 * </p>
 *
 * <pre>
 *     {@code
 *     std::vector<std::vector<int>> neighborsIDList = {
 *         {1, 4},
 *         {0, 2, 5},
 *         {1, 3, 6},
 *         {2, 7},
 *         {0, 5, 8},
 *         {1, 4, 6, 9},
 *         {2, 5, 7, 10},
 *         {3, 6, 11},
 *         {4, 9, 12},
 *         {5, 8, 10, 13},
 *         {6, 9, 11, 14},
 *         {7, 10, 15},
 *         {8, 13},
 *         {9, 12, 14},
 *         {10, 13, 15},
 *         {11, 14}};
 *     int nodeCount = neighborsIDList.size();
 *
 *     std::vector<Node> nodes(nodeCount);
 *     std::vector<Node*> nodePtrs(nodeCount);
 *     for (int i = 0; i < nodeCount; i++)
 *     {
 *       nodes[i].setNodeID(i);
 *       nodePtrs[i] = &nodes[i];
 *     }
 *
 *     std::vector<std::vector<Node*>> neighbors(nodeCount);
 *     for (int i = 0; i < nodeCount; i++)
 *     {
 *       for (int nodeID : neighborsIDList[i])
 *       {
 *         neighbors[i].push_back(nodePtrs[nodeID]);
 *       }
 *     }
 *     for (int i = 0; i < nodeCount; i++)
 *     {
 *       nodePtrs[i]->setNeighbors(&neighbors[i]);
 *     }
 *
 *     auto actual0 = nodePtrs[0]->getNeighbors();
 *     auto actual1 = nodePtrs[1]->getNeighbors();
 *     auto actual2 = nodePtrs[2]->getNeighbors();
 *     auto actual3 = nodePtrs[3]->getNeighbors();
 *     auto actual4 = nodePtrs[4]->getNeighbors();
 *     auto actual5 = nodePtrs[5]->getNeighbors();
 *     auto actual6 = nodePtrs[6]->getNeighbors();
 *     auto actual7 = nodePtrs[7]->getNeighbors();
 *     auto actual8 = nodePtrs[8]->getNeighbors();
 *     auto actual9 = nodePtrs[9]->getNeighbors();
 *     auto actual10 = nodePtrs[10]->getNeighbors();
 *     auto actual11 = nodePtrs[11]->getNeighbors();
 *     auto actual12 = nodePtrs[12]->getNeighbors();
 *     auto actual13 = nodePtrs[13]->getNeighbors();
 *     auto actual14 = nodePtrs[14]->getNeighbors();
 *     auto actual15 = nodePtrs[15]->getNeighbors();
 *     }
 * </pre>
 */
class Node{
  /**
   * <p> ポジション構造体 </p>
   */
  struct Position {
    /**
     * <p> ノード位置のX軸 </p>
     */
    std::int8_t x;
    /**
     * <p> ノード位置のY軸 </p>
     */
    std::int8_t y;
    Position()
        : x(0), y(0) {}
  };

 public:
  /**
   * <p> 隣接ノードが {@code nullptr} のデフォルトコンストラクタ </p>
   *
   * <p>
   * {@link Node} 型の {@link std::vector} を作る際などにご利用ください。
   * </p>
   */
  Node()
      : nodeID(0), blockExists(false), neighbors(nullptr), parentNode(nullptr), score(99), closed(false) {}

  /**
   * <p> ノードIDを設定できるコンストラクタ </p>
   */
  explicit Node(std::int8_t id)
      : nodeID(id), blockExists(false), neighbors(nullptr), parentNode(nullptr), score(99), closed(false) {}

  /**
   * <p> 隣接ノードを設定できるコンストラクタ </p>
   */
  explicit Node(std::vector<Node*>* nodes)
      : nodeID(0), blockExists(false), neighbors(nodes), parentNode(nullptr), score(99), closed(false) {}

  /**
   * <p> オブジェクトのポインタが等しい場合に真を返す </p>
   */
  bool operator==(Node& obj)
  {
    return this == &obj;
  }

  /**
   * <p> オブジェクトのポインタが等しくない場合に真を返す </p>
   */
  bool operator!=(Node& obj)
  {
    return this != &obj;
  }



  /**
   * <p> 隣接ノードを設定する </p>
   *
   * @param nodes 隣接するノードポインタのポインタ
   */
  void setNeighbors(std::vector<Node*>* nodes);

  /**
   * <p> 隣接ノードを取得する </p>
   *
   * @return 隣接するノードポインタのポインタ
   */
  std::vector<Node*>* getNeighbors();

  /**
   * <p> ノードIDを設定する </p>
   *
   * <p>
   * できるだけ別のノードと異なる、一意の数値が望ましい。
   * 一意性は、このクラスのインスタンス保持者が責任を持つ。
   * </p>
   *
   * @param nodeNumber ノードIDの番号
   */
  void setNodeID(std::int8_t nodeNumber);

  /**
   * <p> ノードIDを設定する </p>
   *
   * <p>
   * 別のノードと異なる、一意のIDであるか否かは未検証である。
   * 一意性は、このクラスのインスタンス保持者が責任を持つ。
   * </p>
   *
   * @return ノードIDの番号
   */
  std::int8_t getNodeID();

  /**
   * <p> ブロックを保持している場合は真を返す真偽値を設定する </p>
   *
   * @param exists ブロックを保持している場合は真を返す真偽値
   */
  void setHasBlock(bool exists);

  /**
   * <p> ブロックを保持している場合は真を返す真偽値を取得する </p>
   *
   * @return ブロックを保持している場合は真を返す真偽値
   */
  bool hasBlock();

  /**
   * <p> ノード位置を設定する </p>
   *
   * <p>
   * 他のノードとの相対的な位置であり、絶対的な指標は存在しない。
   * このため、設定する際は他のノードについても考える必要がある。
   * </p>
   *
   * @param x ノード位置のX軸
   * @param y ノード位置のY軸
   */
  void setPosition(std::int8_t x, std::int8_t y);

  /**
   * <p> ノード位置のX軸を取得する </p>
   *
   * <p>
   * {@link Position} 構造体はクラス内にネスト化しているため、これだけでは利用価値が小さい。
   * {@link #getPositionY()} も参照する必要がある。
   * </p>
   *
   * @return ノード位置のX軸
   */
  std::int8_t getPositionX();

  /**
   * <p> ノード位置のY軸を取得する </p>
   *
   * <p>
   * {@link Position} 構造体はクラス内にネスト化しているため、これだけでは利用価値が小さい。
   * {@link #getPositionX()} も参照する必要がある。
   * </p>
   *
   * @return ノード位置のY軸
   */
  std::int8_t getPositionY();

  void setParentNode(Node* parent);

  Node* getParentNode();

  void setScore(std::int32_t score_);

  std::int32_t getScore();

  void setRealCost(std::int32_t cost);

  std::int32_t getRealCost();

  void setBeClosed(bool closed_);

  bool isClosed();

 private:
  /**
   * ノードID (一意である保証はない)
   */
  std::int8_t nodeID;

  /**
   * ブロックがこのノードに存在している可能性
   */
  bool blockExists;

  /**
   * 隣接するノードポインタのポインタ
   */
  std::vector<Node*>* neighbors;

  /**
   * ノードの位置
   */
  Position position;

  Node* parentNode;

  std::int32_t score;

  std::int32_t realCost;

  bool closed;
};

#endif // NODE
