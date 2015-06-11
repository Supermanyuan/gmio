/****************************************************************************
** gmio
** Copyright Fougue (2 Mar. 2015)
** contact@fougsys.fr
**
** This software is a reusable library whose purpose is to provide complete
** I/O support for various CAD file formats (eg. STL)
**
** This software is governed by the CeCILL-B license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-B
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html".
****************************************************************************/

#ifndef GMIO_INTERNAL_STRING_UTILS_H
#define GMIO_INTERNAL_STRING_UTILS_H

#include "../global.h"

#ifdef GMIO_STRINGUTILS_CTYPE_H
#  include <ctype.h>
#endif

/*! Returns non-zero if \p c is a space (for C-locale), zero otherwise */
GMIO_INLINE int gmio_clocale_isspace(char c)
{
#if defined(GMIO_STRINGUTILS_DIRECT_TESTS)
    /* 0x20 : space (SPC)
     * 0x09 : horizontal tab (TAB)
     * 0x0a : newline (LF)
     * 0x0b : vertical tab (VT)
     * 0x0c : feed (FF)
     * 0x0d : carriage return (CR) */
    return c == 0x20 || ((uint8_t)(c - 0x09) < 5);
#elif defined(GMIO_STRINGUTILS_C_ARRAYS)
    static const unsigned char space_chars[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    return space_chars[c];
#elif defined(GMIO_STRINGUTILS_CTYPE_H)
    return isspace(c);
#endif
}

/*! Returns non-zero if \p c is an uppercase letter (for C-locale), zero
 *  otherwise */
GMIO_INLINE int gmio_clocale_isupper(char c)
{
#if defined(GMIO_STRINGUTILS_DIRECT_TESTS)
    return 65 <= c && c <= 90;
#elif defined(GMIO_STRINGUTILS_C_ARRAYS)
    static const unsigned char upper_chars[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    return upper_chars[c];
#elif defined(GMIO_STRINGUTILS_CTYPE_H)
    return isupper(c);
#endif
}

/*! Returns non-zero if \p c is a lowercase letter (for C-locale), zero
 *  otherwise */
GMIO_INLINE int gmio_clocale_islower(char c)
{
#if defined(GMIO_STRINGUTILS_DIRECT_TESTS)
    return 97 <= c && c <= 122;
#elif defined(GMIO_STRINGUTILS_C_ARRAYS)
    static const unsigned char lower_chars[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    return lower_chars[c];
#elif defined(GMIO_STRINGUTILS_CTYPE_H)
    return islower(c);
#endif
}

/*! Returns the lowercase letter converted to uppercase */
GMIO_INLINE char gmio_clocale_toupper(char c)
{
    return gmio_clocale_islower(c) ? c - 32 : c;
}

/*! Returns the uppercase letter converted to lowercase */
GMIO_INLINE char gmio_clocale_tolower(char c)
{
    return gmio_clocale_isupper(c) ?  c + 32 : c;
}

/*! Returns true if \p c1 compare equals to \p c2
 *
 *  Comparison is case-insensitive
 */
GMIO_INLINE gmio_bool_t gmio_clocale_char_iequals(char c1, char c2)
{
    return c1 == c2 || (gmio_clocale_toupper(c1) == gmio_clocale_toupper(c2));
}

/*! Returns 0 if \p str1 and \p str2 compare equal, non-zero otherwise
 *
 *  Comparison is case-insensitive
 */
GMIO_INLINE int gmio_stricmp(const char* str1, const char* str2)
{
    while (*str1 != 0 && *str2 != 0) {
        if (gmio_clocale_char_iequals(*str1, *str2) == GMIO_FALSE)
            return 1;
        ++str1;
        ++str2;
    }
    return *str1 == 0 && *str2 == 0 ? 0 : 1;
}

/*! Returns true if \p str starts with string \p begin
 *
 *  Comparison is case-insensitive
 */
GMIO_INLINE gmio_bool_t gmio_istarts_with(const char* str, const char* begin)
{
    while (*begin != 0) {
        if (*str == 0
                || gmio_clocale_char_iequals(*str, *begin) == GMIO_FALSE)
        {
            return GMIO_FALSE;
        }
        ++str;
        ++begin;
    }
    return GMIO_TRUE;
}

#endif /* GMIO_INTERNAL_STRING_UTILS_H */
