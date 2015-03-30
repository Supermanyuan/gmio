/****************************************************************************
** GeomIO Library
** Copyright FougSys (2 Mar. 2015)
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

/* WARNING :
 *     this header has no multi-inclusion guard. It must be included only once
 *     in the translation unit of use. The reason is that all functions
 *     defined here are meant to be inlined for performance purpose
 */

#include "../stl_mesh_creator.h"

/*! Safe and convenient function for
 *  gmio_stl_mesh_creator::ascii_begin_solid_func() */
GMIO_INLINE void gmio_stl_mesh_creator_ascii_begin_solid(
        gmio_stl_mesh_creator_t* creator,
        size_t stream_size,
        const char* solid_name)
{
    if (creator != NULL && creator->ascii_begin_solid_func != NULL) {
        creator->ascii_begin_solid_func(
                    creator->cookie, stream_size, solid_name);
    }
}

/*! Safe and convenient function for
 *  gmio_stl_mesh_creator::binary_begin_solid_func() */
GMIO_INLINE void gmio_stl_mesh_creator_binary_begin_solid(
        gmio_stl_mesh_creator_t* creator,
        uint32_t tri_count,
        const uint8_t* header)
{
    if (creator != NULL && creator->binary_begin_solid_func != NULL)
        creator->binary_begin_solid_func(creator->cookie, tri_count, header);
}

/*! Safe and convenient function for
 *  gmio_stl_mesh_creator::add_triangle_func() */
GMIO_INLINE void gmio_stl_mesh_creator_add_triangle(
        gmio_stl_mesh_creator_t* creator,
        uint32_t tri_id,
        const gmio_stl_triangle_t* triangle)
{
    if (creator != NULL && creator->add_triangle_func != NULL)
        creator->add_triangle_func(creator->cookie, tri_id, triangle);
}

/*! Safe and convenient function for
 *  gmio_stl_mesh_creator::end_solid_func() */
GMIO_INLINE void gmio_stl_mesh_creator_end_solid(
        gmio_stl_mesh_creator_t* creator)
{
    if (creator != NULL && creator->end_solid_func != NULL)
        creator->end_solid_func(creator->cookie);
}
