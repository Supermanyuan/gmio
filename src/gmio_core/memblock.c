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

#include "memblock.h"

#include <stdlib.h>

GMIO_INLINE gmio_memblock_t gmio_memblock_null()
{
    gmio_memblock_t buff = {0};
    return buff;
}

gmio_memblock_t gmio_memblock(
        void* ptr, size_t size, void (*func_deallocate)(void*))
{
    gmio_memblock_t buff;
    buff.ptr = ptr;
    buff.size = ptr != NULL ? size : 0;
    buff.func_deallocate = func_deallocate;
    return buff;
}

gmio_memblock_t gmio_memblock_malloc(size_t size)
{
    return gmio_memblock(malloc(size), size, &free);
}

gmio_memblock_t gmio_memblock_calloc(size_t num, size_t size)
{
    return gmio_memblock(calloc(num, size), num * size, &free);
}

gmio_memblock_t gmio_memblock_realloc(void* ptr, size_t size)
{
    return gmio_memblock(realloc(ptr, size), size, &free);
}

void gmio_memblock_deallocate(gmio_memblock_t *mblock)
{
    if (mblock != NULL && mblock->func_deallocate != NULL)
        mblock->func_deallocate(mblock->ptr);
}

static gmio_memblock_t gmio_memblock_default_internal_ctor()
{
    return gmio_memblock_malloc(128 * 1024); /* 128 KB */
}

/* Warning: global variable ... */
static gmio_memblock_constructor_func_t gmio_global_mblock_ctor =
        gmio_memblock_default_internal_ctor;

void gmio_memblock_set_default_constructor(gmio_memblock_constructor_func_t ctor)
{
    if (ctor != NULL)
        gmio_global_mblock_ctor = ctor;
}

gmio_memblock_constructor_func_t gmio_memblock_default_constructor()
{
    return gmio_global_mblock_ctor;
}

gmio_memblock_t gmio_memblock_default()
{
    return gmio_global_mblock_ctor();
}