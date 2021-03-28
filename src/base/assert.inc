/**
 * @file assert.inc
 * @brief Verifies assumptions made by the program
 * 
 * To verify assumptions made by the program and print a diagnostic message
 * if this assumption is false.
 */


#ifndef NDEBUG

#include "assert.hpp"

#include <cstdio>
#include <cstdlib>


/**
 * @brief Verifies assumptions made by the program
 * 
 * To verify assumptions made by the program and print a diagnostic message
 * if this assumption is false.
 * 
 * @param v Whether the assumption is verified
 * @param e Assumption to be verified
 * @param file Path to source code
 * @param line Line number
 */
inline void __rmg_assert(bool v, const char *e, const char *file, int line) {
    if(v)
        return;
    
    #ifdef _WIN32
    printf("%s:%u: error: failed assertion '%s'\n", file, line, e);
    #else
    printf("\033[0;1m%s:%u: \033[0;1;31merror: \033[0m", file, line);
    printf("failed assertion \033[0;1m'%s'\033[0m\n", e);
    #endif
    abort();
}

/**
 * @brief Verifies assumptions made by the program
 * 
 * To verify assumptions made by the program and print a diagnostic message
 * if this assumption is false. The expect macro does not terminate program
 * on failure.
 * 
 * @param v Whether the assumption is verified
 * @param e Assumption to be verified
 * @param file Path to source code
 * @param line Line number
 */
inline void __rmg_expect(bool v, const char *e, const char *file, int line) {
    if(v)
        return;
    
    #ifdef _WIN32
    printf("%s:%u: warning: failed assertion '%s'\n", file, line, e);
    #else
    printf("\033[0;1m%s:%u: \033[0;1;33mwarning: \033[0m", file, line);
    printf("failed assertion \033[0;1m'%s'\033[0m\n", e);
    #endif
}

#endif
