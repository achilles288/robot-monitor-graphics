/**
 * @file mat3.inc
 * @brief 3x3 matrix
 * 
 * Matrix multiplication operator. Matricies here are row major.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "mat3.hpp"

#include "../assert.hpp"


namespace rmg {

/**
 * @brief Constructs with detailed cell values
 * 
 * Intented to use for brace initialization
 */
inline Mat3::Mat3(Mat3Row row0, Mat3Row row1, Mat3Row row2):
    data {
      {row0.data[0], row0.data[1], row0.data[2]},
      {row1.data[0], row1.data[1], row1.data[2]},
      {row2.data[0], row2.data[1], row2.data[2]}
    } {}

/**
 * @brief Gets reference to matrix row
 */
inline Mat3Row& Mat3::operator [] (uint8_t i) {
    RMG_ASSERT(i < 3);
    return rows[i];
}

/**
 * @brief Gets reference to matrix row
 */
inline Mat3Row const& Mat3::operator [] (uint8_t i) const {
    RMG_ASSERT(i < 3);
    return rows[i];
}

/**
 * @brief Gets reference to matrix cell
 */
inline float& Mat3Row::operator [] (uint8_t i) {
    RMG_ASSERT(i < 3);
    return data[i];
}

/**
 * @brief Gets reference to matrix cell
 */
inline float const& Mat3Row::operator [] (uint8_t i) const {
    RMG_ASSERT(i < 3);
    return data[i];
}

}
