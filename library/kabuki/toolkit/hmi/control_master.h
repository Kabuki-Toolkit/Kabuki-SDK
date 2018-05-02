/** Kabuki Toolkit
    @file    ~/source/hmi/master_controls.h
    @author  Cale McCollough <calemccollough.github.io>
    @license Copyright (C) 2014-2017 Cale McCollough <calemccollough@gmail.com>;
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
#if MAJOR_SEAM >= 2 && MINOR_SEAM >= 1

#ifndef HEADER_FOR_KABUKI_TOOLKIT_HMI_MASTERCONTROLS
#define HEADER_FOR_KABUKI_TOOLKIT_HMI_MASTERCONTROLS

#include "parameter.h"

namespace kt { namespace hmi {

/** Master control for an isymmetric control surface.
*/
class ControlMaster {
    public:
    
    /** Constructs a blank set of master controls. */
    ControlMaster ();
    
    /** Prints this object to a terminal. */
    inline Printer& Print (Printer& printer) const;
    
    private:

    Parameter<int>* a,
                  * b,
                  * c,
                  * d;
};

}       //< namespace hmi
}       //< namespace toolkit
}       //< namespace kabuki
#endif  //< HEADER_FOR_KABUKI_TOOLKIT_HMI_MASTERCONTROLS
#endif  //< #if MAJOR_SEAM >= 2 && MINOR_SEAM >= 1