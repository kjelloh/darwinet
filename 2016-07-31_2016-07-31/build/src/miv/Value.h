//
// Created by kjell-olovhogdahl on 7/31/2016.
//

#ifndef DARWINET_VALUE_H
#define DARWINET_VALUE_H

#include "Instance.h"

namespace miv {

    namespace value {

        template <typename V>
        struct Value {
            typedef V value_type;
            value_type m_v;
        };

        namespace delta {

            template <typename V>
            struct Delta {
                typedef typename V::value_type value_type;
                value_type m_v;
            };
        }
    }

}



#endif //DARWINET_VALUE_H
