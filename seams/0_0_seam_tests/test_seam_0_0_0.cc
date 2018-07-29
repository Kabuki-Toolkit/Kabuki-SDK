/* Kabuki Toolkit
@version 0.x
@file    $kabuki-toolkit/seams/0_0_seam_tests/test_seam_0_0_0.cc
@author  Cale McCollough <calemccollough.github.io>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <stdafx.h>
#include <random>
#include "../../kabuki/crabs/debug.h"
#include "../../kabuki/crabs/global.h"
#include "test_seam_0.h"

#if SEAM_MAJOR > 0 || SEAM_MAJOR == 0 && SEAM_MINOR >= 0

using namespace _;

#if SEAM_MAJOR == 0 && SEAM_MINOR == 0
#define PRINT(item)  // Print(item);
#define PRINTF(format, ...) Printf(format, __VA_ARGS__)
#define PAUSE(message)         \
  Printf("\n\n%s\n", message); \
  Pause();
#else
#define PRINT(item)
#define PRINTF(x, ...)
#define PAUSE(message)
#endif

TEST_GROUP(SEAM_0_0){void setup(){} void teardown(){PAUSE("\n")}};

TEST(SEAM_0_0, SEAM_0_0_0) {
  PRINT("\n    Testing SEAM_0_0... ");

  static const uint32_t k10ToThe[20] = {
      1,           //< 10^0
      10,          //< 10^1
      100,         //< 10^2
      1000,        //< 10^3
      10000,       //< 10^4
      100000,      //< 10^5
      1000000,     //< 10^6
      10000000,    //< 10^7
      100000000,   //< 10^8
      1000000000,  //< 10^9
  };

  static const uint32_t test_value[] = {
      1,
      12,
      123,
      1234,
      12345,
      123456,
      1234567,
      12345678,
      123456789,
      k10ToThe[0] - 1,
      k10ToThe[0],
      k10ToThe[0] + 1,
      k10ToThe[1] - 1,
      k10ToThe[1],
      k10ToThe[1] + 1,
      k10ToThe[1] + k10ToThe[1] / 2,
      k10ToThe[2] - 1,
      k10ToThe[2],
      k10ToThe[2] + 1,
      k10ToThe[2] + k10ToThe[2] / 2,
      k10ToThe[3] - 1,
      k10ToThe[3],
      k10ToThe[3] + 1,
      k10ToThe[3] + k10ToThe[3] / 2,
      k10ToThe[4] - 1,
      k10ToThe[4],
      k10ToThe[4] + 1,
      k10ToThe[4] + k10ToThe[4] / 2,
      k10ToThe[5] - 1,
      k10ToThe[5],
      k10ToThe[5] + 1,
      k10ToThe[5] + k10ToThe[5] / 2,
      k10ToThe[6] - 1,
      k10ToThe[6],
      k10ToThe[6] + 1,
      k10ToThe[6] + k10ToThe[6] / 2,
      k10ToThe[7] - 1,
      k10ToThe[7],
      k10ToThe[7] + 1,
      k10ToThe[7] + k10ToThe[7] / 2,
      k10ToThe[8] - 1,
      k10ToThe[8],
      k10ToThe[8] + 1,
      k10ToThe[8] + k10ToThe[8] / 2,
      k10ToThe[9] - 1,
      k10ToThe[9],
      k10ToThe[9] + 1,
      k10ToThe[9] + k10ToThe[9] / 2,
  };

  /*
  PRINTF ("\nTesting quick MSD lookup...\n    Length 1:");
  static const uint32_t delta_one_bits[] = { 4, 7, 10, 14, 17, 20, 24, 27, 30 };
  uint32_t max,
           num_bits,
           msd_bit_range;
  PRINTF ("\n| Length | MSD Offset | Min Value  |"
          "\n|:------:|:----------:|:----------:|");
  for (int length = 3; length < 10; ++length) {
      num_bits = delta_one_bits[length - 2];
      msd_bit_range = (length == 10 || length == 20) ? 16: 8;
      for (uint32_t i = 1;  i <= 8; ++i) {
          PRINTF ("\n|   %u    |     %u      | %10u |", length, i, i <<
  num_bits);
      }
  }
  Print ('\n');
  system ("PAUSE");*/

  static const uint32_t problem_children[] = {
      0,
  };
  enum { kNumProblemChildren = 0, kSize = 24 };

  char text[kSize + 1], expecting[kSize + 1];
  char* result;
  uint32_t value;

  // Setup C++1x random number generator.
  std::random_device rd;
  std::mt19937_64 eng(rd());
  std::uniform_int_distribution<uint32_t> distr;

  PRINTF("\n\nTesting Script ItoS Algorithm...\n\n");

  // PrintDigits99To99Lut ();

  PRINTF("\n\nTesting problem children...\n\n");
  for (int i = 0; i < kNumProblemChildren; ++i) {
    value = problem_children[i];
    sprintf_s(expecting, 24, "%u", value);
    PRINTF("\n%i.) Expecting \"%s\":%u", i + 1, expecting,
           (uint)strlen(expecting));
    result = Print(text, text + kSize, value);
    if (!result) {
      PAUSE("An error occurred :-(")
      break;
    }
    *result = 0;
    if (strcmp(expecting, text)) {
      PRINTF("\n\nERROR: Expecting \"%s\":%u and found \"%s\":%u", expecting,
             (uint)strlen(expecting), text, (uint)strlen(text));
      PAUSE("\n")
    }
  }

  PRINT("\n\nTesting edge conditions...\n\n");
  for (int i = 0; i < 28; ++i) {
    value = test_value[i];
    sprintf_s(expecting, 24, "%u", value);
    PRINTF("\n%i.) ", i + 1);
    result = Print(text, text + kSize, value);
    if (!result) {
      PAUSE("An error occurred :-(")
      break;
    }
    *result = 0;
    if (strcmp(expecting, text)) {
      PRINTF("\n\nERROR: Expecting \"%s\":%u and found \"%s\":%u", expecting,
             (uint)strlen(expecting), text, (uint)strlen(text));
      PAUSE("\n")
    }
  }

  PRINTF("\n\nTesting random numbers...\n\n");

  for (int i = 0; i < 0x0000ffff; ++i) {
    value = distr(eng);
    sprintf_s(expecting, 24, "%u", value);
    result = Print(text, text + kSize, value);
    if (!result) {
      PAUSE("An error occurred :-(")
      break;
    }
    *result = 0;
    if (strcmp(expecting, text)) {
      PRINTF("\n\nERROR: Expecting \"%s\":%u and found \"%s\":%u", expecting,
             (uint)strlen(expecting), text, (uint)strlen(text));
      PAUSE("\n")
    }
  }

  PRINTF("\n Done testing ItoS :)\n\n");

  PRINTF("\nTesting ScanUnsigned<Char, I> (const Char*, const char*, I);");

  for (int i = 0; i < 1 << 6; ++i) {
    uint32_t result, value = distr(eng);
    char buffer[25];
    Print(buffer, buffer + 24, value);
    CHECK(Scan(buffer, result));
    CHECK_EQUAL(value, result);
  }
}

#undef PRINT
#undef PRINTF
#undef PAUSE
#else
void TestSeam_1_1() {}
#endif  //< #if SEAM_MAJOR > 0 || SEAM_MAJOR == 0 && SEAM_MINOR >= 0