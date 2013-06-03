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
        int m_source;
        int m_power;
      public:
        GraphBFSFill(const Graph& g,
            int source,
            int power) :
          m_graph(g),
          m_visited(g.totalSize(), unvisited),
          m_parant(g.totalSize(), -1),
          m_source(source),
          m_power(power) {
            fill();
          }

        bool hasRoute() const { return m_hasRoute;}

        std::list<int> pathToTarget()  const {
          std::list<int> path;
          return path;
        }

        std::vector<int> canMoveToNode() const {
          std::vector<int> nodes;
          for(int i = 0, size = static_cast<int>(m_parant.size()) ; i < size ; ++i) {
            if(m_parant[i] != -1) nodes.push_back(i);
          }
          return nodes;
        }

        typedef std::queue< std::pair<const EdgeType*, int>> Queue;
        typedef std::pair<bool, int> Result;

      private:
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

              auto& edges = m_graph.edges(next->to());

              for (auto edge : edges) {
                if (m_visited[edge->to()] == unvisited)
                  queue.push(std::make_pair(edge.get(), result.second));
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
    };
}
#endif

