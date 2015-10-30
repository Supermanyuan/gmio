/****************************************************************************
** gmio
** Copyright Fougue (2 Mar. 2015)
** contact@fougue.pro
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

#include "string_parse.h"

#include "helper_stream.h"

void gmio_string_stream_fwd_iterator_init(gmio_string_stream_fwd_iterator_t *it)
{
    /* Trick: declaring the buffer exhausted will actually trigger the first
     * call to gmio_stream_read() inside gmio_next_char()
     */
    it->strbuff.len = 0;
    it->strbuff_ptr_end = it->strbuff.ptr;
    it->strbuff_ptr_at = it->strbuff_ptr_end;
    gmio_next_char(it);
}

gmio_eat_word_error_t gmio_eat_word(
        gmio_string_stream_fwd_iterator_t *it, gmio_string_t *str)
{
    char* str_ptr_at = str->ptr + str->len;
    const char* str_ptr_end = str->ptr + str->max_len;
    const char* stream_curr_char = NULL;

    /* assert(str != NULL && str->ptr != NULL); */

    stream_curr_char = gmio_skip_spaces(it);
    if (stream_curr_char == NULL) { /* Empty word */
        *str_ptr_at = 0;
        return GMIO_EAT_WORD_ERROR_EMPTY;
    }

    do {
        *str_ptr_at = *stream_curr_char;
        stream_curr_char = gmio_next_char(it);
        ++str_ptr_at;
    } while (stream_curr_char != NULL
             && !gmio_ascii_isspace(*stream_curr_char)
             && str_ptr_at < str_ptr_end);

    if (str_ptr_at < str_ptr_end) {
        *str_ptr_at = 0; /* End string with null byte */
        str->len = str_ptr_at - str->ptr;
        return GMIO_EAT_WORD_ERROR_OK;
    }
    return GMIO_EAT_WORD_ERROR_CAPACITY_OVERFLOW;
}

#if 0
gmio_bool_t gmio_checked_next_chars(
        gmio_string_stream_fwd_iterator_t *it, const char *str)
{
    size_t pos = 0;
    const char* curr_char = gmio_current_char(it);
    gmio_bool_t same = curr_char != NULL && *curr_char == *str;

    while (same) {
        curr_char = gmio_next_char(it);
        same = curr_char != NULL && *curr_char == str[++pos];
    }

    return same;
}
#endif
