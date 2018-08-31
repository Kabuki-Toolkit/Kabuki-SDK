/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    ~/kabuki/crabs/crabs_decimal.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <stdafx.h>
#include <cmath>

#include "binary_64.h"
#include "tbinary.h"

#if SEAM == SEAM_0_0_0
#include "debug.h"
namespace _ {
inline void PrintBinaryTable(uint32_t value) {
  enum { kSize = sizeof(uint32_t) * 8 };

  Print("\n    ");
  for (int i = kSize; i > 0; --i) {
    char c = (char)('0' + (value >> (kSize - 1)));
    Print(c);
    value = value << 1;
  }

  Print(
      "\n    bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
      "\n    33222222222211111111110000000000"
      "\n    10987654321098765432109876543210"
      "\n    ||  |  |   |  |  |   |  |  |   |"
      "\n    |1  0  0   0  0  0   0  0  0   0"
      "\n    |0  9  8   7  6  5   4  3  2   1");
}
}  // namespace _

#define PRINT(item) Print(item)
#define PRINTF(format, ...) Printf(format, __VA_ARGS__)
#define PRINT_PRINTED                                                   \
  ;                                                                     \
  sprintf_s(buffer, 24, "%u", value);                                   \
  *end = 0;                                                             \
  Printf("\n    Printed \"%s\" leaving value:\"%s\":%u", begin, buffer, \
         (uint)strlen(buffer))
#define PRINT_BINARY \
  Print("\n    ");   \
  PrintBinary(value);
#define PRINT_BINARY_TABLE PrintBinaryTable(value);
#define PRINT_HEADER                   \
  for (int i = 0; i < 10; ++i) {       \
    *(cursor + i) = 'x';               \
  }                                    \
  *(cursor + 21) = 0;                  \
  Char* begin = cursor;                \
  Char buffer[256];                    \
  sprintf_s(buffer, 256, "%u", value); \
  Printf("Expecting %s:%u", buffer, (uint)strlen(buffer));
#define BEGIN_PUFF_ALGORITHM \
  Print('\n');               \
  for (int i = 80; i > 0; --i) Print('-')
#else
#define PRINT(item)
#define PRINTF(x, ...)
#define PRINT_PRINTED
#define PRINT_HEADER
#define PRINT_HEADING
#endif

inline void FloatBytes(float value, char& byte_0, char& byte_1, char& byte_2,
                       char& byte_3) {
  uint32_t ui_value = *reinterpret_cast<uint32_t*>(&value);
  byte_0 = (char)(ui_value);
  byte_1 = (char)(ui_value >> 8);
  byte_2 = (char)(ui_value >> 16);
  byte_3 = (char)(ui_value >> 24);
}

namespace _ {

char* Print(char* begin, uint16_t chars) {
#if ALIGN_MEMORY
  *reinterpret_cast<uint16_t*>(chars);
  return begin + 2;
#else
  *reinterpret_cast<uint16_t*>(chars);
  return begin + 2;
#endif
}

char* Print(char* begin, char byte_0, char byte_1) {
#if ALIGN_MEMORY
  if (reinterpret_cast<uintptr_t>(begin) & 1) {
    begin[0] = byte_1;
    begin[1] = '\0';
  }
  if (align == 0) begin[0] = byte_0;
  begin[0] = byte_0;
  begin[1] = '\0';
#else
  *reinterpret_cast<uint16_t*>(begin) = byte_0 | (((uint16_t)byte_1) << 8);
#endif
  return &begin[2];
}

char* Print(char* begin, char* end, char byte_0, char byte_1, char byte_2) {
#if ALIGN_MEMORY
  switch (reinterpret_cast<uintptr_t>(begin) & 3) {
    case 0: {
      *reinterpret_cast<uint32_t*>(begin) =
          ((uint32_t)byte_0) | ((uint32_t)byte_1) << 8 |
          ((uint32_t)byte_1) << 16 | ((uint32_t)byte_1) << 24;
      return &begin[4];
    }
    case 1: {
      uint32_t* ptr = reinterpret_cast<uint32_t*>(begin) - 1;
      uint32_t word = (*ptr) & ((uint32_t)0xff)
                                   << 24;  //< Mask off byte_0 byte.
      *ptr = word;
      begin[3] = 0;
      return &begin[4];
    }
    case 2: {
      uint16_t ptr = *reinterpret_cast<uint16_t*>(begin);
      *ptr++ = ((uint16_t)byte_0) | ((uint16_t)byte_1) << 8;
      *ptr++ = ((uint16_t)byte_2) | ((uint16_t)byte_3) << 8;
      return reinterpret_cast<char*>(ptr);
    }
    case 3: {
      *begin = byte_0;
      uint32_t* ptr = reinterpret_cast<uint32_t*>(begin) - 1;
      uint32_t word = (*ptr) & ((uint32_t)0xff)
                                   << 24;  //< Mask off byte_0 byte.
      word |= ((uint32_t)byte_0) | ((uint32_t)byte_0) << 8 |
              ((uint32_t)byte_0) << 16;  //< OR together three.
      begin[3] = 0
    }
  }
#else
  *reinterpret_cast<uint32_t*>(begin) =
      ((uint32_t)byte_0) | ((uint32_t)byte_1) << 8 | ((uint32_t)byte_1) << 16 |
      ((uint32_t)byte_1) << 24;
#endif
  return &begin[4];
}

char puff_lut[2 * 100 + (8 + 2) * 87];

const uint16_t* PuffDigits() {}

inline const uint16_t* IEEE754Exponents() {}

inline const uint64_t* Binary64Pow10() {}

void NumberRealLutGenerate(char* buffer, size_t size) {
  /* Lookup table of ASCII Char pairs for 00, 01, ..., 99 in little-endian
  format. */
  static const uint16_t kDigits00To99[100] = {
      0x3030, 0x3130, 0x3230, 0x3330, 0x3430, 0x3530, 0x3630, 0x3730, 0x3830,
      0x3930, 0x3031, 0x3131, 0x3231, 0x3331, 0x3431, 0x3531, 0x3631, 0x3731,
      0x3831, 0x3931, 0x3032, 0x3132, 0x3232, 0x3332, 0x3432, 0x3532, 0x3632,
      0x3732, 0x3832, 0x3932, 0x3033, 0x3133, 0x3233, 0x3333, 0x3433, 0x3533,
      0x3633, 0x3733, 0x3833, 0x3933, 0x3034, 0x3134, 0x3234, 0x3334, 0x3434,
      0x3534, 0x3634, 0x3734, 0x3834, 0x3934, 0x3035, 0x3135, 0x3235, 0x3335,
      0x3435, 0x3535, 0x3635, 0x3735, 0x3835, 0x3935, 0x3036, 0x3136, 0x3236,
      0x3336, 0x3436, 0x3536, 0x3636, 0x3736, 0x3836, 0x3936, 0x3037, 0x3137,
      0x3237, 0x3337, 0x3437, 0x3537, 0x3637, 0x3737, 0x3837, 0x3937, 0x3038,
      0x3138, 0x3238, 0x3338, 0x3438, 0x3538, 0x3638, 0x3738, 0x3838, 0x3938,
      0x3039, 0x3139, 0x3239, 0x3339, 0x3439, 0x3539, 0x3639, 0x3739, 0x3839,
      0x3939,
  };

  /* Precomputed powers of 10 exponents for Grisu. */
  static const int16_t kCachedPowersE[] = {
      -1220, -1193, -1166, -1140, -1113, -1087, -1060, -1034, -1007, -980, -954,
      -927,  -901,  -874,  -847,  -821,  -794,  -768,  -741,  -715,  -688, -661,
      -635,  -608,  -582,  -555,  -529,  -502,  -475,  -449,  -422,  -396, -369,
      -343,  -316,  -289,  -263,  -236,  -210,  -183,  -157,  -130,  -103, -77,
      -50,   -24,   3,     30,    56,    83,    109,   136,   162,   189,  216,
      242,   269,   295,   322,   348,   375,   402,   428,   455,   481,  508,
      534,   561,   588,   614,   641,   667,   694,   720,   747,   774,  800,
      827,   853,   880,   907,   933,   960,   986,   1013,  1039,  1066};

  /* Precomputed powers of ten integral portions: 10^-348, 10^-340, ..., 10^340.
  Size bytes is 87 elements * 8 bytes/element = 696 bytes. */
  static const uint64_t kCachedPowersF[] = {
      0xfa8fd5a0081c0288, 0xbaaee17fa23ebf76, 0x8b16fb203055ac76,
      0xcf42894a5dce35ea, 0x9a6bb0aa55653b2d, 0xe61acf033d1a45df,
      0xab70fe17c79ac6ca, 0xff77b1fcbebcdc4f, 0xbe5691ef416bd60c,
      0x8dd01fad907ffc3c, 0xd3515c2831559a83, 0x9d71ac8fada6c9b5,
      0xea9c227723ee8bcb, 0xaecc49914078536d, 0x823c12795db6ce57,
      0xc21094364dfb5637, 0x9096ea6f3848984f, 0xd77485cb25823ac7,
      0xa086cfcd97bf97f4, 0xef340a98172aace5, 0xb23867fb2a35b28e,
      0x84c8d4dfd2c63f3b, 0xc5dd44271ad3cdba, 0x936b9fcebb25c996,
      0xdbac6c247d62a584, 0xa3ab66580d5fdaf6, 0xf3e2f893dec3f126,
      0xb5b5ada8aaff80b8, 0x87625f056c7c4a8b, 0xc9bcff6034c13053,
      0x964e858c91ba2655, 0xdff9772470297ebd, 0xa6dfbd9fb8e5b88f,
      0xf8a95fcf88747d94, 0xb94470938fa89bcf, 0x8a08f0f8bf0f156b,
      0xcdb02555653131b6, 0x993fe2c6d07b7fac, 0xe45c10c42a2b3b06,
      0xaa242499697392d3, 0xfd87b5f28300ca0e, 0xbce5086492111aeb,
      0x8cbccc096f5088cc, 0xd1b71758e219652c, 0x9c40000000000000,
      0xe8d4a51000000000, 0xad78ebc5ac620000, 0x813f3978f8940984,
      0xc097ce7bc90715b3, 0x8f7e32ce7bea5c70, 0xd5d238a4abe98068,
      0x9f4f2726179a2245, 0xed63a231d4c4fb27, 0xb0de65388cc8ada8,
      0x83c7088e1aab65db, 0xc45d1df942711d9a, 0x924d692ca61be758,
      0xda01ee641a708dea, 0xa26da3999aef774a, 0xf209787bb47d6b85,
      0xb454e4a179dd1877, 0x865b86925b9bc5c2, 0xc83553c5c8965d3d,
      0x952ab45cfa97a0b3, 0xde469fbd99a05fe3, 0xa59bc234db398c25,
      0xf6c69a72a3989f5c, 0xb7dcbf5354e9bece, 0x88fcf317f22241e2,
      0xcc20ce9bd35c78a5, 0x98165af37b2153df, 0xe2a0b5dc971f303a,
      0xa8d9d1535ce3b396, 0xfb9b7cd9a4a7443c, 0xbb764c4ca7a44410,
      0x8bab8eefb6409c1a, 0xd01fef10a657842c, 0x9b10a4e5e9913129,
      0xe7109bfba19c0c9d, 0xac2820d9623bf429, 0x80444b5e7aa7cf85,
      0xbf21e44003acdd2d, 0x8e679c2f5e44ff8f, 0xd433179d9c8cb841,
      0x9e19db92b4e31ba9, 0xeb96bf6ebadf77d9, 0xaf87023b9bf0ee6b};

  enum { kFpPowersCount = 87 };

  ASSERT(size);

  if (size != ((100 + kFpPowersCount) * 2 + kFpPowersCount * 8)) return;
  uint16_t* ui2_ptr = reinterpret_cast<uint16_t*>(buffer);

  for (char tens = '0'; tens <= '9'; ++tens)
    for (int ones = '0'; ones <= '9'; ++ones)
#if ENDIAN == LITTLE
      *ui2_ptr++ = (tens << 8) | ones;
#else
      *ui2_ptr++ = (ones << 8) | tens;
#endif

  for (int i = 0; i < 87; ++i) *ui2_ptr = kCachedPowersE[i];

  uint64_t* ui8_ptr = reinterpret_cast<uint64_t*>(ui2_ptr);

  for (int i = 0; i < 87; ++i) *ui8_ptr = kCachedPowersF[i];
}

const uint16_t* DigitsLut(const char* puff_lut) {
  return reinterpret_cast<const uint16_t*>(puff_lut);
}

const uint16_t* PuffLutExponents(char* puff_lut) {
  return reinterpret_cast<const uint16_t*>(puff_lut + 200);
}

const uint64_t* PufLutPow10(char* puff_lut) {
  return reinterpret_cast<const uint64_t*>(puff_lut + 374);
}

int FloatDigitsMax() { return 8; }  //< 3 + FLT_MANT_DIG - FLT_MIN_EXP;

inline uint32_t Value(float value) {
  return *reinterpret_cast<uint32_t*>(&value);
}

inline uint64_t Value(double value) {
  return *reinterpret_cast<uint64_t*>(&value);
}

float FloatDecimalPower(int decimal_count) {
  static const float kDecimals[] = {0.1f,       0.01f,      0.001f,
                                    0.0001f,    0.00001f,   0.000001f,
                                    0.0000001f, 0.00000001f};

  if (decimal_count < 1 || decimal_count > FloatDigitsMax()) return 0.0f;
  return kDecimals[decimal_count - 1];
}

int DoubleDigitsMax() { return 16; }  //< 3 + DBL_MANT_DIG - DBL_MIN_EXP;

double DoubleDecimalPower(int decimal_count) {
  if (decimal_count < 0 || decimal_count > DoubleDigitsMax()) return 0.0;
  return PuffDigits()[decimal_count];
}

template <typename UI>
inline UI NanUnsigned() {
  return ~0;
}

template <typename SI, typename UI>
inline SI NanSigned() {
  return (SI)(((UI)1) << (sizeof(SI) * 8 - 1));
}

bool IsNaNPositive(int8_t value) { return value > NanUnsigned<int8_t>(); }
bool IsNaNNegative(int8_t value) { return value > NanUnsigned<int8_t>(); }
bool IsNaN(int8_t value) {
  return (value > NanUnsigned<int8_t>()) &&
         (value > NanSigned<int8_t, uint8_t>());
}

bool IsNaN(uint8_t value) { return value > NanUnsigned<uint8_t>(); }

bool IsNaN(int16_t value) { return value > NanSigned<int16_t, uint16_t>(); }

bool IsNaN(uint16_t value) { return value > NanUnsigned<uint16_t>(); }

bool IsNaN(int32_t value) { return value > NanSigned<int32_t, uint32_t>(); }

bool IsNaN(uint32_t value) { return value > NanUnsigned<uint32_t>(); }

bool IsNaN(int64_t value) { return value > NanSigned<int64_t, uint64_t>(); }

bool IsNaN(uint64_t value) { return value > NanUnsigned<uint64_t>(); }

bool IsNaN(float value) { return isnan(value); }

bool IsNaN(double value) { return isnan(value); }

bool IsFinite(float value) { return isfinite(value); }

bool IsFinite(double value) { return isfinite(value); }

bool IsInfinite(float value) { return isinf(value); }

bool IsInfinite(double value) { return isinf(value); }

/* Checks if the given value is an even power of 2.
KABUKI bool IsPowerOfTen (int8_t value);* /

/* Checks if the given value is an even power of 2.
KABUKI bool IsPowerOfTen (uint8_t value); */

/* Checks if the given value is an even power of 2.
KABUKI bool IsPowerOfTen (int16_t value); */

/* Checks if the given value is an even power of 2.
KABUKI bool IsPowerOfTen (uint16_t value); */

/* Checks if the given value is an even power of 2.
KABUKI bool IsPowerOfTen (int32_t value); */

/* Checks if the given value is an even power of 2.
KABUKI bool IsPowerOfTen (uint32_t value); */

/* Checks if the given value is an even power of 2.
KABUKI bool IsPowerOfTen (int64_t value); */

/* Checks if the given value is an even power of 2.
KABUKI bool IsPowerOfTen (uint64_t value); */

/*
bool IsPowerOfTen(int8_t value) {
  return IsPowerOfTenSigned<uint8_t, int8_t>(value);
}

bool IsPowerOfTen(uint8_t value) { return IsPowerOfTen<uint8_t>(value); }

bool IsPowerOfTen(int16_t value) {
  return IsPowerOfTenSigned<uint16_t, int16_t>(value);
}

bool IsPowerOfTen(uint16_t value) { return IsPowerOfTen<uint16_t>(value); }

bool IsPowerOfTen(int32_t value) {
  return IsPowerOfTenSigned<uint32_t, int32_t>(value);
}

bool IsPowerOfTen(uint32_t value) { return IsPowerOfTen<uint32_t>(value); }

bool IsPowerOfTen(int64_t value) {
  return IsPowerOfTenSigned<uint64_t, int64_t>(value);
}

bool IsPowerOfTen(uint64_t value) { return IsPowerOfTen<uint64_t>(value); }
*/

/* Masks the lower bits using faster bit shifting.
@brief The algoirhm has you enter the highest bit rather than bit count because
it would introduct an extra instruction and you should do that manually if you
wish to do so.
@param value The value to mask.
@param mab The Most Significant bit, or one less than the number of bits to
mask off. */
template <typename UI>
inline UI ShiftLeftRight(UI value, int left_bits, int right_bits) {
  value = value << left_bits;
  return value >> right_bits;
}

/* Creates a mask with the given number of zeros in the MSb(s).
@param msb_zero_count The number of zeros in the Most Significant bits. */
template <typename UI>
inline UI CreateMaskLSb(UI msb_zero_count) {
  UI mask = 0;
  return (~mask) >> msb_zero_count;
}

/* Masks off the lower bits.
@param msb_zero_count The number of zeros in the Most Significant bits. */
template <typename UI>
inline UI MaskLSb(UI value, UI msb_zero_count) {
  return value & CreateMaskLSb<UI>(msb_zero_count);
}

/* Retruns 2^n.
@brief Funciton forces the compiler to create the mask without a LDR
instruciton. */
template <typename I>
inline I PowerOf2(I n) {
  I value = 1;
  return value << n;
}

uint64_t ComputePow10(int e, int alpha, int gamma) {
  double pow_10 = 0.30102999566398114,  //< 1/lg(10)
      alpha_minus_e_plus_63 = static_cast<double>(alpha - e + 63),
         ceiling = Ceiling(alpha_minus_e_plus_63 * pow_10);
  return *reinterpret_cast<uint64_t*>(&pow_10);
}

/* Calculates the ceiling of the given value to the next highest integer.
@warning I jacked this off StackOverflow and have not tested it.
@param value The value to take the ceiling of.
@return The ceiling to the next highest integer. */
template <typename Float, typename UI>
Float Ceiling(Float value) {
  UI integer = *reinterpret_cast<UI*>(&value);

  // Extract sign, exponent and coefficient bias is removed from exponent.
  UI sign = integer >> kFpBits,
     exponent_mask = ShiftLeftRight<UI>(integer, 1, kMantissaBitCount),
     exponent = ((integer & 0x7fffffff) >> kMantissaMSb) - kExponentMask,
     coefficient = integer & 0x7fffff, comparator;

  if (exponent < 0) {  // value is in the open interval (-1, 1)
    if (value <= 0.0)
      return 0.0;
    else
      return 1.0;
  } else {
    // Mask the fractional part of the coefficient.
    UI mask = CreateMaskLSb<UI>(kMantissaMSb) >>
              exponent;  //< mask should be 0x7fffff

    if ((coefficient & mask) == 0)  // The mantissa is zero so it's an integer.
      return value;
    else {
      if (sign == 0) {
        // It's positive so add 1 to it before clearing the fractional bits.
        coefficient += ((UI)1) << (kMantissaMSb - exponent);

        comparator = PowerOf2<UI>(kFpBits);

        // Check for coefficient overflow...
        if (coefficient & comparator) {
          // The coefficient can only overflow if all the integer bits were
          // previously 1, so we can just clear out the coefficient and
          // increment the exponent.
          coefficient = 0;
          ++exponent;
        }
      }

      // Clear the fractional bits.
      coefficient &= ~mask;
    }
  }

  // Put sign, exponent and coefficient together again
  integer = (sign << kFpBits) | ((exponent + kExponentMask) << kMantissaMSb) |
            coefficient;

  return *reinterpret_cast<Float*>(&integer);
}

struct diy_fp {
  uint64_t f;
  int32_t e;
};

#define TEN9 1000000000

void digit_gen(diy_fp Mp, diy_fp delta, char* buffer, int* len, int* K) {
  uint32_t div;
  int32_t d, kappa;
  diy_fp one;
  one.f = ((uint64_t)1) << -Mp.e;
  one.e = Mp.e;
  uint32_t p1 = (uint32_t)(Mp.f >> -one.e);
  uint64_t p2 = Mp.f & (one.f - 1);
  *len = 0;
  kappa = 10;
  div = TEN9;
  while (kappa > 0) {
    d = p1 / div;
    if (d || *len) buffer[(*len)++] = '0' + d;
    p1 %= div;
    kappa--;
    div /= 10;
    if ((((uint64_t)p1) << -one.e) + p2 <= delta.f) {
      *K += kappa;
      return;
    }
  }
  do {
    p2 *= 10;
    d = (uint32_t)(p2 >> -one.e);
    if (d || *len) buffer[(*len)++] = '0' + d;
    p2 &= one.f - 1;
    kappa--;
    delta.f *= 10;
  } while (p2 > delta.f);
  *K += kappa;
}

float Ceiling(float value) {
  // return Ceiling<float, uint32_t>(value);
  return ceil(value);
}

double Ceiling(double value) {
  // return Ceiling<double, uint64_t>(value);
  return ceil(value);
}

union float_int {
  float f;
  int i;
};

inline float myceil(float x) {
  float_int val;
  val.f = x;

  // Extract sign, exponent and coefficient
  // Bias is removed from exponent
  int sign = val.i >> 31;
  int exponent = ((val.i & 0x7fffffff) >> 23) - 127;
  int coefficient = val.i & 0x7fffff;

  // Is the exponent less than zero?
  if (exponent < 0) {
    // In this case, x is in the open interval (-1, 1)
    if (x <= 0.0f)
      return 0.0f;
    else
      return 1.0f;
  } else {
    // Construct a bit mask that will mask off the
    // fractional part of the coefficient
    int mask = 0x7fffff >> exponent;

    // Is x already an integer (i.e. are all the
    // fractional bits zero?)
    if ((coefficient & mask) == 0)
      return x;
    else {
      // If x is positive, we need to add 1 to it
      // before clearing the fractional bits
      if (!sign) {
        coefficient += 1 << (23 - exponent);

        // Did the coefficient overflow?
        if (coefficient & 0x800000) {
          // The coefficient can only overflow if all the
          // integer bits were previously 1 -- so we can
          // just clear out the coefficient and increment
          // the exponent
          coefficient = 0;
          exponent++;
        }
      }

      // Clear the fractional bits
      coefficient &= ~mask;
    }
  }

  // Put sign, exponent and coefficient together again
  val.i = (sign << 31) | ((exponent + 127) << 23) | coefficient;

  return val.f;
}

}  // namespace _

#undef PRINT
#undef PRINTF
#undef PRINT_PRINTED
#undef PRINT_HEADER
#undef PRINT_HEADING
#undef BEGIN_PUFF_ALGORITHM
