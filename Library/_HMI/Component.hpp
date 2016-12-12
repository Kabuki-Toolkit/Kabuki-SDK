/** Kabuki Software Development Kit
    @file    /.../KabukiSDK/_HMI/_HMI/Components/Component.hpp
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright  (C) 2016 [Cale McCollough](calemccollough.github.io)

                            All right reserved  (R).

        Licensed under the Apache License, Version 2.0  (the "License"); you may
        not use this file except in compliance with the License. You may obtain
        a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
*/
 
#pragma once

#include <KabukiSDK-Config.hpp>
#include <FreeI2P.hpp>

namespace _HMI { namespace Components {
    
class _KabukiSDK Component
{
    public:
    
    Component ();
    /*< Constructs a dummy object. */
    
    void print (I2P::Terminal& slot);
    /*< Prints this object to a terminal. */
}

}   //< namespace Components
}   //< namespace _HMI
