/** kabuki::script
    @version 0.x
    @file    ~/source/script/include/collection.h
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

#ifndef SCRIPT_COLLECTION_H
#define SCRIPT_COLLECTION_H

#include "types.h"

namespace _ {

/** Interface for a Script Set.
    Set Types:

    | Name       | Code | Description                                  |
    |-----------:|:----:|:---------------------------------------------|
    |      Array | ARY  | A packed c-style array of POD number types.  |
    |      Stack | STK  | A stack of POD number types.                 |
    |       List | LST  | A stack of Type-Value tuples.                |
    |        Map | MAP  | A one-to-one map of Id-{Type-Value} tuples.  |
    |       Book | BOK  | An unordered map of Key-{Type-Value} tuples. |
    | Dictionary | DIC  | A one-to-one map of Key-{Type-Value} tuples. |
    |   Observer | OBV  | A Observer with Subscriber List.             |
*/
struct Set {

    /** Clears the Set without wiping the memory. */
    virtual void Clear () = 0;

    /** Clears the Set and wipes the memory. */
    virtual void Wipe () = 0;

    /** Adds the given object to this Set. */
    virtual bool Add (TType Type, void* data) = 0;

    /** Merges the given Set into this one. */
    virtual bool Merge (TType Type, void* data) = 0;

    /** Removes the given object from this collection. */
    virtual bool Remove (TType Type, void* data) = 0;

    /** Removes the given index from this collection. */
    virtual bool Remove (uintptr_t) = 0;

    /** Gets the element at the given index. */
    virtual void* Get (uintptr_t index) = 0;

    /** Returns true if this Set contains this given Type-Value. */
    virtual uintptr_t FindIndex (TType type, void* data) = 0;

    /** Searches for the data of the given type and returns a pointer to it.
        @return Returns nullptr if the Set does not contain the given data. */
    virtual void* Find (TType type, void* data) = 0;

    /** Gets the size_t of the object being stored. */
    virtual uintptr_t GetSize () = 0;

    /** Gets the size_t of the object being stored. */
    virtual uintptr_t GetSizeWidth () = 0;
};
}       //< namespace _
#endif  //< SCRIPT_COLLECTION_H
