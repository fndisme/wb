/*
 * =====================================================================================
 *
 *       Filename:  GraphBFSFill.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/3 16:22:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_GRAPHBFSFILL_H
#define FND_WEBGAME_GRAPHBFSFILL_H
#include <list>
#include <queue>
#include <vector>
#include <utility>

namespace WebGame {
  template<typename Graph>
    class GraphBFSFill {
      private:
        enum {visited, unvisited, no_parent_assigned};
        typedef typename Graph::EdgeType EdgeType;
        typedef typename Graph::NodeType NodeType;

      private:
        const Graph& m_graph;
        std::vector<int> m_visited;
        std::vector<int> m_parant;
        std::vector<int> m_moveLeftPower;
        int m_source;
        int m_power;
      public:

        typedef std::pair<int, bool> InfluencePoint;

        GraphBFSFill(const Graph& g,
            int source,
            int power) :
          m_graph(g),
          m_visited(g.totalSize(), unvisited),
          m_parant(g.totalSize(), -1),
          m_moveLeftPower(g.totalSize(), 0),
          m_source(source),
          m_power(power) {
            fill();
            caculateCanMoveNodes();
          }

        void refill(int source, int power) {
          m_source = source;
          m_power = power;
          m_visited.assign(m_visited.size(), unvisited);
          m_parant.assign(m_parant.size(), -1);
          m_moveLeftPower.assign(m_moveLeftPower.size(), 0);
          m_canInfluenceNodes.clear();
          m_canMoveNodes.clear();
          fill();
          caculateCanMoveNodes();
        }

        //bool hasRoute() const { return m_hasRoute;}

        std::vector<int> pathToTarget(int target)  const {

          std::vector<int> path;
          if(target < 0 || target >= static_cast<int>(m_parant.size())) return path;
          int nd = target;
          path.push_back(nd);
          while (nd != m_source) {
            nd = m_parant[nd];
            path.push_back(nd);
          }

          return path;
        }

        const std::set<int>& canMoveToNode() const {
          return m_canMoveNodes;
        }

        void debugPrint() const {
          for(int i = 0 ; i < m_graph.height(); ++i) {
            for(int j = 0 ; j < m_graph.width() ; ++j) {
              if(m_parant[i * m_graph.width() + j] != -1)
                std::cout << " . " ;
              else
                std::cout << " * " ;
            }
            std::cout << std::endl;
          }
        }

        typedef std::queue< std::pair<const EdgeType*, int>> Queue;
        typedef std::pair<bool, int> Result;
        void caculateCanInfluenceNodes(int type) {
          // just think up down left right
          for(MoveNodesType::const_iterator iter = m_canMoveNodes.begin(),
              iter_end = m_canMoveNodes.end() ; iter != iter_end; ++iter) {
            std::map<int, bool> singleInfluence = singleInfluenced(*iter, type);
            m_canInfluenceNodes.insert(singleInfluence.begin(), singleInfluence.end());
          }
        }

        const std::map<int, bool>& influencedNodes() const {
          return m_canInfluenceNodes;
        }

      private:
        void caculateCanMoveNodes() {
          for(int i = 0, size = static_cast<int>(m_parant.size()) ; i < size ; ++i) {
            if(m_parant[i] != -1) m_canMoveNodes.insert(i);
          }
        }

        std::map<int, bool> singleInfluenced(int nodeIndex, int type) {
          std::map<int, bool> nodes;
          typedef typename Graph::PropertyType PropertyType;
          const PropertyType& graphProperty = m_graph.property();
          if(!graphProperty.hasAttackType(type)) return nodes;

          int x = m_graph.node(nodeIndex)->x();
          int y = m_graph.node(nodeIndex)->y();
          typedef typename PropertyType::AttackNeighbourType NeightBourType;
          const NeightBourType& moveIndexs = graphProperty.attackType(type);
          for(typename NeightBourType::const_iterator iter = moveIndexs.begin(),
              iter_end = moveIndexs.end() ;
              iter != iter_end ;
              ++iter) {
            int attackDeltaX = (*iter).first;
            int attackDeltaY = (*iter).second;

            if(m_graph.hasNode(x + attackDeltaX, y + attackDeltaY)) {
              auto node = m_graph.node(x + attackDeltaX, y + attackDeltaY);
              nodes.insert(std::make_pair(node->index(),
                    m_canMoveNodes.count(node->index()) == 0));
            }
          }
          return nodes;
        }

        void fill() {
          Queue queue;
          EdgeType dummy(m_source, m_source);
          queue.push(std::make_pair(&dummy, m_power));

          while (!queue.empty()) {
            auto value = queue.front();
            queue.pop();
            auto next = value.first;
            auto power = value.second;

            auto result = checkCanGoto(next->from(), next->to(), power);
            if (result.first) {
              std::cout << " from " << next->from() << " to " << next->to() << std::endl;
              m_parant[next->to()] = next->from();
              m_visited[next->to()] = visited;
              m_moveLeftPower[next->to()] = result.second;

              auto& edges = m_graph.edges(next->to());

              for (auto edge : edges) {
                if (m_visited[edge->to()] == unvisited)
                  queue.push(std::make_pair(edge.get(), result.second));
                else if(m_visited[edge->to()] == visited &&
                    m_moveLeftPower[edge->to()] < result.second) {
                  m_moveLeftPower[edge->to()] = result.second;
                  queue.push(std::make_pair(edge.get(), result.second));
                }
              }
            }
          }
        }

        Result checkCanGoto(int from, int to, int currentPower) const {

          if(from == to) return std::make_pair(true, currentPower);
          int type = m_graph.node(to)->type();
          int needPower = movePowerByType(type);
          if(needPower > currentPower) return std::make_pair(false, currentPower);
          return std::make_pair(true, currentPower - needPower);

        }

        int movePowerByType(int type) const {
          return 1;
        }


        typedef std::set<int> MoveNodesType;
        MoveNodesType m_canMoveNodes;
        std::map<int, bool> m_canInfluenceNodes;
    };
}
#endif
