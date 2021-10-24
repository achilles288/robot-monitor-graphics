/**
 * @file alignment.hpp
 * @brief Enumeration to determine the alignment of 2D objects
 * 
 * Supports the rendering operations for Object2D.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_ALIGNMENT_H__
#define __RMG_ALIGNMENT_H__


namespace rmg {

/**
 * @brief Horizontal alignment of 2D objects
 */
enum class HorizontalAlign {
    Left,
    Center,
    Right
};

/**
 * @brief Vertical alignment of 2D objects
 */
enum class VerticalAlign {
    Top,
    Middle,
    Bottom
};

/**
 * @brief Horizontal and vertical alignment of 2D objects
 */
enum class Alignment {
    TopLeft,
    TopCenter,
    TopRight,
    MiddleLeft,
    MiddleCenter,
    MiddleRight,
    BottomLeft,
    BottomCenter,
    BottomRight
};

typedef HorizontalAlign TextAlign; ///< Text alignment

}

#endif
