/**
 * @file assert.hpp
 * @brief Verifies assumptions made by the program
 * 
 * To verify assumptions made by the program and print a diagnostic message
 * if this assumption is false.
 */


#pragma once
#ifndef __RMG_ASSERT_H__
#define __RMG_ASSERT_H__ /**< Header guard */


#ifndef NDEBUG

/**
 * @brief Verifies assumptions made by the program
 * 
 * To verify assumptions made by the program and print a diagnostic message
 * if this assumption is false. The assert macro cleans the resources and
 * exit on failure.
 * 
 * @param e Assumption to be verified
 */
#define RMG_ASSERT(e) __rmg_assert(e, #e, __FILE__, __LINE__)

/**
 * @brief Verifies assumptions made by the program
 * 
 * To verify assumptions made by the program and print a diagnostic message
 * if this assumption is false. The expect macro does not terminate program
 * on failure.
 * 
 * @param e Assumption to be verified
 */
#define RMG_EXPECT(e) __rmg_expect(e, #e, __FILE__, __LINE__)


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
void __rmg_assert(bool v, const char *e, const char *file, int line);

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
void __rmg_expect(bool v, const char *e, const char *file, int line);


#else
#define RMG_ASSERT(e)
#define RMG_EXPECT(e)
#endif

#include "assert.inc"

#endif
