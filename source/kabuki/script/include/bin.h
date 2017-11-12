/** kabuki::script
    @version 0.x
    @file    ~/source/kabuki/script/include/bin.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <calemccollough@gmail.com>;
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

#ifndef SCRIPT_BIN_H
#define SCRIPT_BIN_H

#include "operation.h"

namespace _ {

/** Calculates the used ring buffer space.
    @param  Start The start of the data.
    @param  Stop  The stop of the data.
    @param  Size The size of the buffer. */
KABUKI uint_t SlotLength (byte* start, byte* stop, uint_t size);

/** Calculates the space left in the given ring buffer.
    @param  Start The start of the data.
    @param  Stop  The stop of the data.
    @param  Size  The size of the buffer. */
KABUKI uint_t SlotSpace (byte* start, byte* stop, uint_t size);

/*< A*B B-Input Slot.
    A B-Input Slot is functionally identical to a input port in TCP.
*/
struct KABUKI Bin {
    /** List of B-Input Errors. */
    typedef enum {
        BufferOverflowError      = 0,
        BufferUnderflowError     = 1,
        VarintOverflowError      = 2,
        InvalidHashError         = 3,
        InvalidTypeError         = 4,
        InvalidIndexError        = 5,
        InvalidEnqueryError      = 6,
        InvalidArgumentError     = 7,
        InvalidDoorError         = 8,
        TooManyParametersError   = 9,
        StackOverflowError       = 10,
        InvalidSubetError        = 11,
        TooManyPopsError         = 12,
        StringOverflowError      = 13,
        InvalidErrorHandlerError = 14,
        InvalidOpeartionError    = 15,
        ArrayOverflowError       = 16,
        InvalidOperationError    = 17,
        Utf8Error                = 18,
        Utf16Error               = 19,
        Utf32Error               = 20,
        LockedError              = 21,
        RoomError                = 22,
    } Error;

    /** List of Finite Bin States.
        @see Script Protocol RFC for list of states. */
    typedef enum States {
        AddressState = 0,   //< State  0: Scanning address.
        ArgsState,          //< State  1: Scanning arguments.
        Utf8State,          //< State  2: Scanning STR.
        Utf16State,         //< State  3: Scanning ST2.
        Utf32State,         //< State  4: Scanning ST8.
        VarintState,        //< State  5: Scanning varint.
        Obj8State,          //< State  6: 8-bit OB1 state.
        Obj16State,         //< State  7: 16-bit OB2 state.
        Obj32State,         //< State  8: 32-bit OB4 state.
        Obj64State,         //< State  9: 64-bit OB8 state.
        HashState,          //< State 10: Stand the 32-bit hash.
        ErrorState,         //< State 11: Handling an error state.
        DisconnectedState,  //< State 12: Disconnected state.
        AckState,           //< State 13: Awaiting connection ACK.
        LockedState,        //< State 14: Locked state.
        PodState,           //< State 15: Scanning plain-old-data.
    } State;

    uint_t          size,   //< The size of the buffer.
                    start;  //< The starting index of the ring buffer data.
    volatile uint_t stop;   //< The stopping index of the ring buffer data.
    uint_t          read;   //< The read variable.
};

/** Get's the B-Input's buffer.*/
KABUKI byte* BinBuffer (Bin* bin);

/** Gets a a char for printing out the bin_state. */
KABUKI const char* BinStateString (Bin::State state);

inline const char* BinStateString (byte state) {
    return BinStateString ((Bin::State)state);
}

/** Used to return an erroneous result from a B-Input.

    @param error The error type.
    @return Returns a Static Error Operation Result. */
KABUKI const Operation* BinResult (Bin* bin, Bin::Error error);

/** Used to return an erroneous result from a B-Input.
    @param  bin     The source Bin.
    @param  error   The error type.
    @param  header  The B-Sequence Header.
    @param  offset  The offset to the type in error in the B-Sequence.
    @param  address The address of the byte in error.
    @return         Returns a Static Error Operation Result. */
KABUKI const Operation* BinResult (Bin* bin, Bin::Error error,
                                   const uint_t* header);

/** Used to return an erroneous result from a B-Input.
    @param  bin     The source Bin.
    @param  error   The error type.
    @param  header  The B-Sequence Header.
    @param  offset  The offset to the type in error in the B-Sequence.
    @param  address The address of the byte in error.
    @return         Returns a Static Error Operation Result. */
KABUKI const Operation* BinResult (Bin* bin, Bin::Error error,
                                   const uint_t* header,
                                   uint_t offset);

/** Used to return an erroneous result from a B-Input.
    @param  bin     The source Bin.
    @param  error   The error type.
    @param  header  The B-Sequence Header.
    @param  offset  The offset to the type in error in the B-Sequence.
    @param  address The address of the byte in error.
    @return         Returns a Static Error Operation Result. */
KABUKI const Operation* BinResult (Bin* bin, Bin::Error error,
                                   const uint_t* header,
                                   uint_t offset,
                                   byte* address);

/** Initializes the Bin struct KABUKI to an empty buffer. */
KABUKI Bin* BinInit (uintptr_t* buffer, uint_t size);

/** Gets the rx buffer length. */
KABUKI uint_t BinSpace (Bin* bin);

/** Gets the end address of the rx buffer. */
KABUKI byte* BinEndAddress (Bin* bin);

/** Returns true if the Bin buffer contains any data.
    @warning Function does not do any error checking for speed. */
KABUKI bool BinIsReadable (Bin* bin);

/** Prints out the given object to the std::out. */
KABUKI void BinPrint (Bin* bin);

/** Scans a message with the given params to the given Bin.
    The data in the Bin is word-aligned, unlike the Slot. It also 
    doesn't have a hash with an escape sequence.
    
    @param rx The Bin socket.
    @param params The parameters.
    @param args   The arguments.
    @return       Returns 0 upon success and an ErrorList ticket number upon 
                  failure. */
KABUKI const Operation* BinRead (Bin* bin, const uint_t* params, void** args);

}       //< namespace _
#endif  //< SCRIPT_BIN_H
