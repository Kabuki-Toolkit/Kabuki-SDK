/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    ~/kabuki/f2/test.h
@author  Cale McCollough <cale.mccollough@gmail.com>
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

#if SEAM >= SEAM_00_00_00__00_00
#ifndef INCLUDED_KABUKI_F2_TEST
#define INCLUDED_KABUKI_F2_TEST SEAM_00_00_00__00_00

namespace _ {

/* Class for storing information about a failed assertion. */
struct API TestResult {
  const char *name,  //< The file the assertion occurred at.
      *description;  //< An optional description to print.
  int code,          //< The test result code.
      line;          //< The line the assertion failed at.
};

int TestFailure()

}  // namespace _

typedef const char* (*SeamNode)(_::TestResult& test_result, const char* args);

namespace _ {

/* Tests an array of SeamNode(s).
@return 0 upon success or an app exit code upon failure. */
int Test(TestResult& test_result, const char* args, SeamNode* seams,
         int node_count);

void TestSeamTreeEnd(const char* function_name) {
  Print("\nDone testing ", function_name, ". (:-)-+=<");
}

/* Assert check if the given condition is true
@return false if the condition is false.
@param condition The condition to check. */
API bool Assert(bool condition);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(const char* a, const char* b);

/* Tests if the two pointers are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(const void* a, const void* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(uint8_t a, uint8_t b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(int8_t a, int8_t b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(uint8_t a, uint8_t b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(int16_t a, int16_t b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(uint16_t a, uint16_t b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(int32_t a, int32_t b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(uint32_t a, uint32_t b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(int64_t a, int64_t b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(uint64_t a, uint64_t b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(float a, float b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API bool Test(double a, double b);

/* Tests if the two pointers are equal.
@return false if the condition is false.
@param  value The value to test.  */
API bool Test(const void* value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test.
@param  b Parameter b. */
API bool Test(uint8_t value, uint8_t b);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API bool Test(int8_t value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API bool Test(uint8_t value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API bool Test(int16_t value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API bool Test(uint16_t value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API bool Test(int32_t value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API bool Test(uint32_t value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API bool Test(int64_t value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API bool Test(uint64_t value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API bool Test(float value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API bool Test(double value);

/* Handles an assert by printing a debug statement and locks up the system.
@return True upon failure.
@param  line    The line the program failed at.
@param  file    The file the error occurred at.
@param  message An optional message to print. */
API bool AssertHandle(const char* file, int line,
                      const char* message = nullptr);
}  // namespace _

#if SEAM > 0 && SEAM <= SEAM_N
#define ASSERT(condition) \
  if (Assert(condition)) _::AssertHandle(__FILE__, __LINE__)
#define TEST1(item) \
  if (Test(item)) _::AssertHandle(__FILE__, __LINE__)
#define TEST(a, b) \
  if (Test(a, b)) _::AssertHandle(__FILE__, __LINE__)
#else
#define ASSERT(condition)
#define TEST1(item)
#define TEST(a, b)
#endif

#endif  //< #ifndef INCLUDED_KABUKI_F2_TEST
#endif  //< #if SEAM >= SEAM_00_00_00__00_01