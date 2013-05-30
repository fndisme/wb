/*
 * =====================================================================================
 *
 *       Filename:  SearchingPlayerFleetProperty.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-2-20 15:21:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_SEARCHINGFLEET_PROPERTY_H
#define FND_WEBGAME_SEARCHINGFLEET_PROPERTY_H
#include <vector>
#include <memory>
#include	"DataQuery_SearchingFleetProperty.pb.h"
namespace WebGame
{
class SearchingFleetProperty
{
public:
    typedef std::shared_ptr<const game_connection::DataQuery_SearchingFleetProperty> value_type ;
    typedef game_connection::DataQuery_SearchingFleetProperty const& const_reference ;

    void set_property(value_type v) {
        m_property = v;
    }
    const_reference property() const {
        return *m_property ;
    }
    explicit SearchingFleetProperty(SearchingFleetProperty&& f) :
        m_property(std::move(f.m_property)) {}
    SearchingFleetProperty() :
        m_property(new game_connection::DataQuery_SearchingFleetProperty) {}
    value_type property_pointer() const {
        return m_property ;
    }
private:
    value_type m_property ;
} ;
}
#endif
