/*
 * =====================================================================================
 *
 *       Filename:  GraphDFSSearch.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/5/26 22:23:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_GRAPHDFSSEARCH_H
#define FND_WEBGAME_GRAPHDFSSEARCH_H
#include <list>
#include <stack>
#include <vector>

namespace WebGame {
  template<typename Graph>
    class GraphDFSSearch {
      private:
        enum {visited, unvisited, no_parent_assigned};
        typedef typename Graph::EdgeType EdgeType;
        typedef typename Graph::NodeType NodeType;

      private:
        const Graph& m_graph;
        std::vector<int> m_visited;
        std::vector<int> m_route;
        int m_source;
        int m_target;
        bool m_hasRoute;
      public:
        GraphDFSSearch(const Graph& g,
            int source,
            int target) :
          m_graph(g),
          m_source(source),
          m_target(target),
          m_hasRoute(false),
          m_visited(g.totalSize(), unvisited),
          m_route(g.totalSize(), -1) {
            m_hasRoute = search();
          }

        bool hasRoute() const { return m_hasRoute;}

        std::list<int> pathToTarget()  const {
          std::list<int> path;
          if (!m_hasRoute) return path;
          int nd = m_target;
          path.push_back(m_target);
          
          while (nd != m_source) {
            nd = m_route[nd];
            path.push_back(nd);
          }

          return path;
        }

      private:
        bool search() {
          std::stack<const EdgeType*> stack;
          EdgeType dummy(m_source, m_source);
          stack.push(&dummy);

          while (!stack.empty()) {
            const EdgeType* next = stack.top();
            stack.pop();

            bool ok = checkCanGoto(next->from(), next->to());
            if (ok) {
              m_route[next->to()] = next->from();
              m_visited[next->to()] = visited;

              if (next->to() == m_target) return true;

              auto& edges = m_graph.edges(next->to());

              for (auto edge : edges) {
                if (m_visited[edge->to()] == unvisited)
                  stack.push(edge.get());
              }

            }
          }

          return false;
        }

        bool checkCanGoto(int from, int to) const {
          return true;
        }
    };
}
#endif

