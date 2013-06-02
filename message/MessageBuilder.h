#ifndef FND_GAME_MESSAGE_BUILDER_H
#define FND_GAME_MESSAGE_BUILDER_H

#ifdef _DEBUG
#include <cassert>
#include <set>
#include <iostream>
#endif
#include <string>
#include <functional>
#include <memory>
#include <boost/functional/factory.hpp>
#include <boost/noncopyable.hpp>
#include <google/protobuf/stubs/common.h>
#include <pantheios/assert.h>
#include	"webgame/utility/TinyFinder.h"
namespace google {
    namespace protobuf {
        class Message ;
    }
}
namespace WebGame {
    namespace Message {
        typedef std::function<std::shared_ptr< ::google::protobuf::Message> ( )> message_builder_type ;
        class MessageBuilder : boost::noncopyable {
            typedef MessageBuilder class_type ;
            typedef Utility::TinyFinder<int, message_builder_type> finder_type ;
            public:
            template<typename T>
                void registerBuilder(T* /*p*/ = nullptr) {
#ifdef _DEBUG

                    if(m_register_types.count(T::value)) {
                        std::cout << "register twice....." << T::value << std::endl ;
                    }
                    PANTHEIOS_ASSERT(m_register_types.count(T::value) == 0) ;
                    m_register_types.insert(T::value) ;
#endif
                    typedef boost::factory<std::shared_ptr<T>/*   , boost::fast_pool_allocator<T> */
                        > factory_type ;
                    m_builders.insert(T::value, factory_type()) ;
                }
            void registerBuilder(int type, const message_builder_type& builder) {
                m_builders.insert(type,builder) ;
            }

            std::shared_ptr< ::google::protobuf::Message> buildMessage(int type) const {
                return m_builders.value(type)() ;
            }

            template<typename T>
                std::shared_ptr< ::google::protobuf::Message> buildMessage() const {
                    return build_message(T::value) ;
                }
            void makeFinal() { m_builders.makeFinal();}
            MessageBuilder(){}
            private:
            finder_type m_builders ;
            typedef std::shared_ptr< ::google::protobuf::Message> value_type ;
#ifdef _DEBUG
            std::set<int> m_register_types ;
#endif

        } ;
    }
}

#endif
