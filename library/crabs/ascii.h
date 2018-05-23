/** Kabuki Toolkit
    @version 0.x
    @file    ~/library/crabs/memory.h
    @author  Cale McCollough <https://calemccollough.github.io>
    @license Copyright (C) 2014-8 Cale McCollough <calemccollough@gmail.com>;
             All right reserved (R). Licensed under the Apache License, Version 
             2.0 (the "License"); you may not use this file except in 
             compliance with the License. You may obtain a copy of the License 
             [here](http://www.apache.org/licenses/LICENSE-2.0). Unless 
             required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS,
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
             implied. See the License for the specific language governing 
             permissions and limitations under the License. */

#pragma once
#include <stdafx.h>

#ifndef HEADER_FOR_CRABS_ASCII
#define HEADER_FOR_CRABS_ASCII

namespace _ {
enum {
    NUL = 0,    //< 0
    SOH,        //< 1
    STX,        //< 2
    ETX,        //< 3
    EOT,        //< 4
    ENQ,        //< 5
    ACK,        //< 6
    BEL,        //< 7
    BS,         //< 8
    TAB,        //< 9
    LF,         //< 10
    VT,         //< 11
    FF,         //< 12
    CR,         //< 13
    SO,         //< 14
    SI,         //< 15
    DLE,        //< 16
    DC1,        //< 17
    DC2,        //< 18
    DC3,        //< 19
    DC4,        //< 20
    NAK,        //< 21
    SYN,        //< 22
    ETB,        //< 23
    CAN,        //< 24
    EM,         //< 25
    SUB,        //< 26
    //ESC,      //< 27
    FS,         //< 28
    GS,         //< 29
    RS,         //< 30
    US,         //< 31
    DEL = 128
};
}       //< namespace _
#endif  //< HEADER_FOR_CRABS_ASCII
