/** The Chinese Room
    @version 0.x
    @file    /.../terminal.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough<calemccollough.github.io>

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

#ifndef CHINESEROOM_TERMINAL_H
#define CHINESEROOM_TERMINAL_H

#include "uniprinter.h"

namespace _ {

/** A IO Terminal Device with Rx Uniprinter.
    
*/
class Terminal : public Device {
    public:

    /** Default constructor that does nothing. */
    Terminal (Uniprinter* io)
    :   io_(io)
    {
    }

    ~Terminal () {
        //if (io_->type > 0) Delete<Uniprinter> (io_);
    }

    bool Contains (void* address) {
        return UniprinterContains (io_, address);
    }

    const Member* Op (Rx* rx, Tx* tx, byte index) override {
        switch (index) {
            case 0:
                break;
        }
        return 0;
    }

    private:

    Uniprinter* io_;        //< The all-in-one printer and scanner.
};

}       //< namespace _
#endif  //< CHINESEROOM_TERMINAL_H
