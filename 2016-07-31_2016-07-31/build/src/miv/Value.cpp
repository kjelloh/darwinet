//
// Created by kjell-olovhogdahl on 7/31/2016.
//

#include "Value.h"

namespace miv {

    namespace value {

        void test() {
            {
                miv::value::Value<miv::model::MIVInt> int_value{2};
                // Test Delta operations available for MIVInt
            }
            {
                miv::value::Value<miv::model::MIVString > int_value{"Välkommen"};
                // Test Delta operations available for MIVString
            }
        }

    }
}
