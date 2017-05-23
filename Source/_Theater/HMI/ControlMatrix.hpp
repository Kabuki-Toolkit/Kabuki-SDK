/** Kabuki Theater
    @file    /.../Source/_Theater/HMI/ControlMatrix.hpp
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <https://calemccollough.github.io>

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

#include <KabukiTheater-Config.hpp>
#include "ControlArray.hpp"

namespace _Theater { namespace HMI {

/** A grid of Controls.
    Each AVControl Layer on the Symmetry Live can either have 8 pots or encoders, or can have 4 pots and 4 encoders.
    This class _KabukiTheater_ helps us swap the values out quickly and efficiently.

    A ControlMatrix must have the option of being bifurcated.
*/
class _KabukiTheater_ ControlMatrix
{
    public:

    static const int MinNumRows = 1,                    //< The min number of rows.
        MinNumColumns = 2,                              //< The min number of columns.
        MaxNumRows    = ControlArray::MaxNumElements,   //< The max number of rows.
        MaxNumColumns = ControlArray::MaxNumElements;   //< The max number of columns.

    ControlMatrix (int newNumColumns = 8, int newNumRows = 6);
    /*< Default constructor. */
    
    ControlMatrix (const ControlMatrix& o);
    //< Copy constructor.
    
    virtual ~ControlMatrix ();
    //< Virtual Destructor.

    int getNumRows () const;
    //< gets the number of rows.
    
    int getNumColumns () const;
    //< gets the number of columns.

    void setControl (int column, int row, AVControl* NewKnob);
    /*< Sets the pointer to knobs[index] pointer to the newKnob. */
    
    ControlArray* getRow (int row);
    /*< Gets the row at the given index.
        @return gets nullptr if the index is invalid. */
    
    inline void print(_::Log& log);
    /*< Prints this object to a terminal. */
    
    private:

    int numRows,            //< The number of rows.
        numColumns;         //< The number of columns.

    ControlArray* rows;     //< The rows of control array columns.
};

}   //  _Theater/HMI
