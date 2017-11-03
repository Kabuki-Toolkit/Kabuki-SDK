/** kabuki::script
    @version 0.x
    @file    ~/source/kabuki/script/include/a.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <calemccollough.github.io>;
             All right reserved (R). Licensed under the Apache License, Version 
             2.0 (the "License"); you may not use this file except in 
             compliance with the License. You may obtain a copy of the License 
             [here](http://www.apache.org/licenses/LICENSE-2.0). Unless 
             required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS,
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
             implied. See the License for the specific language governing 
             permissions and limitations under the License.
*/

#pragma once
#include <stdafx.h>

#ifndef SCRIPT_A_H
#define SCRIPT_A_H

#include "room.h"

namespace _ {

/** The A in A*B.
    
*/
struct A: public Room {
    public:

    A ():
        Room (1024)
    {

    }
};

}       //< namespace _
#endif  //< SCRIPT_A_H