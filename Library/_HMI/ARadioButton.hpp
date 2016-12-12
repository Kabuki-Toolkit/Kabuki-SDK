/** Kabuki Software Development Kit
    @file    /.../KabukiSDK/_HMI/RadioButton.hpp
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2016 [Cale McCollough](calemccollough.github.io)

                            All right reserved (R).

        Licensed under the Apache License, Version 2.0 (the "License"); you may
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

#include <SymmetryStation-Config.hpp>

namespace _HMI {
    
class ARadioButton
{
    public:
    
    ARadioButton ();
    /*< Constructs a dummy object. */

    virtual ~ARadioButton ();
    /*< Virtually destructs the sub-objects. */

    int getIndex ();
    /*< Gets the currently selected choice. */

    bool setValue (int value);
    /*< Attemps to set the value to the new one and returns false upon success. */

    void hit ();
    /*< Increments the index or resets it to zero if out bounds. */

    private:

    int index;      //< The index of the radio button.
};

}   //  _HMI
