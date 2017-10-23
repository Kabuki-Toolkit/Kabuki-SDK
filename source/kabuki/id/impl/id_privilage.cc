/** kabuki::pro
    @file    ~/source/kabuki/id/imp/privilage.cc
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

#include <stdafx.h>
#include "../include/Privilage.h"

namespace kabuki { namespace id {

static PrivilageLevel minPrivilageLevel = DefaultMinPrivilageLevel,
    maxPrivilageLevel = DefaultMaxPrivilageLevel;

PrivilageLevel getMinPrivilageLevel ()
{
    return minPrivilageLevel;
}

PrivilageLevel setMinPrivilageLevel ()
{
    return maxPrivilageLevel;
}

bool setPrvilageLevelRange (PrivilageLevel min, PrivilageLevel max)
{

}

Privilage::Privilage ()
{

}

PrivilageLevel Privilage::getPrivilageLevel ()
{
    return privilageLevel;
}

bool Privilage::setPrivilageLevel (PrivilageLevel l)
{
    if (l < minPrivilageLevel || l > maxPrivilageLevel) return false;
    privilageLevel = l;
    return true;
}

void Privilage::Print (_::Log& log)
{

}

}       //< id
}       //< kabuki
