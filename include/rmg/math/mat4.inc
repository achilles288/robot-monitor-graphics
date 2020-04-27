/**
 * @file mat4.inc
 * @brief 4x4 matrix
 * 
 * Matrix multiplication operator. Matricies here are row major.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include <cassert>


namespace rmg {

/**
 * @brief Constructs with detailed cell values
 * 
 * Intented to use for brace initialization
 */
inline Mat4::Mat4(Mat4Row row0, Mat4Row row1, Mat4Row row2, Mat4Row row3):
    data {
      {row0.data[0], row0.data[1], row0.data[2], row0.data[3]},
      {row1.data[0], row1.data[1], row1.data[2], row1.data[3]},
      {row2.data[0], row2.data[1], row2.data[2], row2.data[3]},
      {row3.data[0], row3.data[1], row3.data[2], row3.data[3]}
    } {}

/**
 * @brief Gets reference to matrix row
 * 
 * @param i Row index
 * 
 * @return Reference to matrix row
 */
inline Mat4Row& Mat4::operator [] (uint8_t i) {
    assert(i < 4);
    return rows[i];
}

/**
 * @brief Gets reference to matrix row
 * 
 * @param i Row index
 * 
 * @return Reference to matrix row
 */
inline Mat4Row const& Mat4::operator [] (uint8_t i) const {
    assert(i < 4);
    return rows[i];
}

/**
 * @brief Gets reference to matrix cell
 * 
 * @param i Column index
 * 
 * @return Reference to matrix cell
 */
inline float& Mat4Row::operator [] (uint8_t i) {
    assert(i < 4);
    return data[i];
}

/**
 * @brief Gets reference to matrix cell
 * 
 * @param i Column index
 * 
 * @return Reference to matrix cell
 */
inline float const& Mat4Row::operator [] (uint8_t i) const {
    assert(i < 4);
    return data[i];
}

}