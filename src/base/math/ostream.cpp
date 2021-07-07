/**
 * @file ostream.cpp
 * @brief Print functions for mathematical data structures
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "../rmg/math/euler.hpp"
#include "../rmg/math/mat3.hpp"
#include "../rmg/math/mat4.hpp"
#include "../rmg/math/vec.hpp"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif


namespace rmg {

/**
 * @brief Prints a screen coordinate
 * 
 * @param os Output stream
 * @param rect The rectangular dimension
 * 
 * @return Reference of passed output stream
 */
std::ostream& operator << (std::ostream& os, const Rect& rect) {
    return os << '(' << rect.x << ", " << rect.y << ')';
}

/**
 * @brief Prints a 2D vector
 * 
 * @param os Output stream
 * @param v The vector to print
 * 
 * @return Reference of passed output stream
 */
std::ostream& operator << (std::ostream& os, const Vec2& v) {
    os << '(';
    char buff[11];
    
    if(fabs(v.x) < 10000.0000f)
        snprintf(buff, 11, "%.4f", v.x);
    else
        snprintf(buff, 11, "%.3e", v.x);
    os << buff << ", ";
    
    if(fabs(v.y) < 10000.0000f)
        snprintf(buff, 11, "%.4f", v.y);
    else
        snprintf(buff, 11, "%.3e", v.y);
    os << buff;
    
    return os << ')';
}

/**
 * @brief Prints a 3D vector
 * 
 * @param os Output stream
 * @param v The vector to print
 * 
 * @return Reference of passed output stream
 */
std::ostream& operator << (std::ostream& os, const Vec3& v) {
    os << '(';
    for(int i=0; ; i++) {
        char buff[11];
        if(fabs(v[i]) < 10000.0000f)
            snprintf(buff, 11, "%.4f", v[i]);
        else
            snprintf(buff, 11, "%.3e", v[i]);
        
        if(i == 2) {
            os << buff;
            break;
        }
        os << buff << ", ";
    }
    return os << ')';
}

/**
 * @brief Prints a 4D vector
 * 
 * @param os Output stream
 * @param v The vector to print
 * 
 * @return Reference of passed output stream
 */
std::ostream& operator << (std::ostream& os, const Vec4& v) {
    os << '(';
    for(int i=0; ; i++) {
        char buff[11];
        if(fabs(v[i]) < 10000.0000f)
            snprintf(buff, 11, "%.4f", v[i]);
        else
            snprintf(buff, 11, "%.3e", v[i]);
        
        if(i == 3) {
            os << buff;
            break;
        }
        os << buff << ", ";
    }
    return os << ')';
}




/**
 * @brief Prints a tuple of Euler angles
 * 
 * @param os Output stream
 * @param euler The Euler angles
 * 
 * @return Reference of passed output stream
 */
std::ostream& operator << (std::ostream& os, const Euler& euler) {
    const float *data = &euler.roll;
    os << '(';
    for(int i=0; ; i++) {
        char buff[11];
        if(fabs(data[i]) < 10000.0000f)
            snprintf(buff, 11, "%.4f", data[i]);
        else
            snprintf(buff, 11, "%.3e", data[i]);
        
        if(i == 2) {
            os << buff;
            break;
        }
        os << buff << ", ";
    }
    return os << ')';
}

}




static void printMatrix(std::ostream& os, const float *data, int row, int col);


namespace rmg {

/**
 * @brief Prints a matrix with UTF-8 encoded characters
 * 
 * @param os Output stream
 * @param M The matrix to print
 * 
 * @return Reference of passed output stream
 */
std::ostream& operator << (std::ostream& os, const Mat3& M) {
    printMatrix(os, &M.data[0][0], 3, 3);
    return os;
}

/**
 * @brief Prints a matrix with UTF-8 encoded characters
 * 
 * @param os Output stream
 * @param M The matrix to print
 * 
 * @return Reference of passed output stream
 */
std::ostream& operator << (std::ostream& os, const Mat4& M) {
    printMatrix(os, &M.data[0][0], 4, 4);
    return os;
}

}

void printMatrix(std::ostream& os, const float *data, int row, int col)
{
    #ifdef _WIN32
    UINT WINAPI cp = GetConsoleOutputCP();
    SetConsoleOutputCP(65001);
    #endif

    char cells[4][4][11];
    int col_width[4];
    int line_width = 2*(col-1);
    for(int i=0; i<col; i++) {
        int m = 0;
        for(int j=0; j<row; j++) {
            if(std::isnan(data[j * col + i]))
                snprintf(cells[j][i], 11, "nan");
            else if(fabs(data[j * col + i]) < 10000.0000f)
                snprintf(cells[j][i], 11, "%.4f", data[j*col + i]);
            else
                snprintf(cells[j][i], 11, "%.3e", data[j*col + i]);
            int c = (int) strlen(cells[j][i]);
            if(c > m)
                m = c;
        }
        col_width[i] = m;
        line_width += col_width[i];
    }
    
    os << "\xe2\x94\x8c\xe2\x94\x80" << std::string(line_width, ' ')
       << "\xe2\x94\x80\xe2\x94\x90" << std::endl;
    
    for(int i=0; i<row; i++) {
        std::string line(line_width, ' ');
        char *p = &line[0];
        
        for(int j=0; ; j++) {
            int cell_width = (int) strlen(cells[i][j]);
            p += col_width[j] - cell_width;
            memcpy(p, cells[i][j], cell_width);
            p += cell_width;
            
            if(j == col-1)
                break;
            *p = ',';
            p += 2;
        }
        os << "\xe2\x94\x82 " << line << " \xe2\x94\x82" << std::endl;
    }
    
    os << "\xe2\x94\x94\xe2\x94\x80" << std::string(line_width, ' ')
       << "\xe2\x94\x80\xe2\x94\x98" << std::endl;

    #ifdef _WIN32
    SetConsoleOutputCP(cp);
    #endif
}
