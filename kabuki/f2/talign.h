/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    ~/kabuki/f2/talign.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <stdafx.h>

#if SEAM >= SEAM_00_00_00__00_01
#ifndef INCLUDED_CRABS_TALIGN
#define INCLUDED_CRABS_TALIGN 1

namespace _ {

/* Aligns the given pointer up to a sizeof (T) byte boundary.
@return The aligned value.
@param  ptr The address to align.
@desc Algorithm works by inverting the bits, mask of the LSbs and adding 1.
This allows the algorithm to word align without any if statements. The
algorithm works the same for all memory widths as proven by the truth
tables bellow.

@code
// The convention KT uses is that the unsigned size always comes first
// because it's the first byte of an ASCII OBJ.
int32_t signed_example = 7;
signed_example = AlignUp<int64_t, uint32_t, int32_t> (signed_example);

uint16_t unsigned_example = 3;
unsgiend_example = AlignUp<int32_t, uint16_t, uint16_t> (unsigned_example);

// 64-bit alignment example:
// ~000 = 111 => 000 + 111 + 1 = 0x1000
// ~001 = 110 => 001 + 110 + 1 = 0x1000
// ~010 = 101 => 010 + 101 + 1 = 0x1000
// ~011 = 100 => 011 + 100 + 1 = 0x1000
// ~100 = 011 => 100 + 011 + 1 = 0x1000
// ~101 = 010 => 101 + 010 + 1 = 0x1000
// ~110 = 001 => 110 + 001 + 1 = 0x1000
// ~111 = 000 => 111 + 000 + 1 = 0x1000
// //
// 32-bit alignment example:
// ~00 = 11 => 00 + 11 + 1 = 0x100
// ~01 = 10 => 01 + 10 + 1 = 0x100
// ~10 = 01 => 10 + 01 + 1 = 0x100
// ~11 = 00 => 11 + 00 + 1 = 0x100
// //
// 16-bit alignment example:
// ~0 = 1 => 0 + 1 = 1
// ~1 = 0 => 1 + 0 = 0
// //
// 8-bit example:
// value + ((~value) + 1) & (sizeof (int8_t) - 1) = value
@endcode */
template <typename I = uintptr_t, typename UI = I>
inline I AlignUpOffset(I value, I mask = sizeof(I) * 8 - 1) {
  I result = (~(UI)value) + 1;
  return result & mask;
}

/* Aligns the given pointer to a power of two boundary.
@warning Function does not check if the boundary is a power of 2! */
template <typename T = char>
inline T* AlignUp(void* pointer, uintptr_t mask = sizeof(void*) - 1) {
  uintptr_t value = reinterpret_cast<uintptr_t>(pointer);
  return reinterpret_cast<T*>(value + AlignUpOffset<>(pointer, mask));
}

/* Aligns the given pointer to the sizeof (WordBoundary) down..
@param  value The value to align.
@return The aligned value. */
template <typename I = uintptr_t>
inline I AlignDownOffset(I value, I mask = sizeof(void*) - 1) {
  return value & mask;
}

/* Aligns the given pointer to the sizeof (WordBoundary) down..
@param  value The value to align.
@return The aligned value. */
template <typename I = uintptr_t>
inline I AlignDown(I value, I mask = sizeof(void*) - 1) {
  return value - AlignDownOffset<>(value, mask);
}

/* Calculates the offset to align the given pointer to a 16-bit word boundary.
@return A vector you add to a pointer to align it. */
template <typename T = char>
inline T* AlignUp2(void* pointer) {
  // Mask off lower bit and add it to the ptr.
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return reinterpret_cast<T*>(ptr + (ptr & 0x1));
}

/* Calculates the offset to align the given pointer to a 16-bit word boundary.
    @return A vector you add to a pointer to align it. */
template <typename T = char>
inline T* AlignUp2(const void* pointer) {
  // Mask off lower bit and add it to the ptr.
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return reinterpret_cast<T*>(ptr + (ptr & 0x1));
}

}  // namespace _
#endif  //< INCLUDED_CRABS_TALIGN

#endif  //< #if SEAM >= SEAM_00_00_00__00_01