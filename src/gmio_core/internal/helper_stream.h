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

#ifndef GMIO_INTERNAL_HELPER_STREAM_H
#define GMIO_INTERNAL_HELPER_STREAM_H

#include "../stream.h"

/*! Safe and convenient function for gmio_stream::func_at_end() */
GMIO_INLINE gmio_bool_t gmio_stream_at_end(gmio_stream_t* stream)
{
    if (stream != NULL && stream->func_at_end != NULL)
        return stream->func_at_end(stream->cookie);
    return GMIO_FALSE;
}

/*! Safe and convenient function for gmio_stream::func_error()  */
GMIO_INLINE int gmio_stream_error(gmio_stream_t* stream)
{
    if (stream != NULL && stream->func_error != NULL)
        return stream->func_error(stream->cookie);
    return 0;
}

/*! Safe and convenient function for gmio_stream::func_read() */
GMIO_INLINE size_t gmio_stream_read(
        gmio_stream_t* stream, void *ptr, size_t size, size_t count)
{
    if (stream != NULL && stream->func_read != NULL)
        return stream->func_read(stream->cookie, ptr, size, count);
    return 0;
}

/*! Safe and convenient function for gmio_stream::func_write() */
GMIO_INLINE size_t gmio_stream_write(
        gmio_stream_t* stream, const void *ptr, size_t size, size_t count)
{
    if (stream != NULL && stream->func_write != NULL)
        return stream->func_write(stream->cookie, ptr, size, count);
    return 0;
}

/*! Safe and convenient function for gmio_stream::func_size() */
GMIO_INLINE size_t gmio_stream_size(gmio_stream_t* stream)
{
    if (stream != NULL && stream->func_size != NULL)
        return stream->func_size(stream->cookie);
    return 0;
}

/*! Safe and convenient function for gmio_stream::func_rewind() */
GMIO_INLINE void gmio_stream_rewind(gmio_stream_t* stream)
{
    if (stream != NULL && stream->func_rewind != NULL)
        stream->func_rewind(stream->cookie);
}

#endif /* GMIO_INTERNAL_HELPER_STREAM_H */
