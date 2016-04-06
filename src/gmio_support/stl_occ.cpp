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

#include <gmio_support/stl_occ.h>

#include <cstring>
#include <StlMesh_Mesh.hxx>
#include <StlMesh_MeshTriangle.hxx>
#include <StlMesh_SequenceOfMeshTriangle.hxx>
#include <TColgp_SequenceOfXYZ.hxx>

#ifndef GMIO_SUPPORT_STL_OCC_NO_MESHVS_DATASOURCE
#  include <Handle_MeshVS_DataSource.hxx>
#  include <MeshVS_DataSource.hxx>
#  include <TColStd_PackedMapOfInteger.hxx>
#endif // !GMIO_SUPPORT_STL_OCC_NO_MESHVS_DATASOURCE

namespace internal {

/* Common */

static StlMesh_Mesh* occMeshPtr(const Handle_StlMesh_Mesh& mesh)
{
    return mesh.operator->();
}

static void occmesh_add_triangle(
        void* cookie, uint32_t tri_id, const gmio_stl_triangle* tri)
{
    StlMesh_Mesh* mesh = static_cast<StlMesh_Mesh*>(cookie);
    if (tri_id == 0)
        mesh->AddDomain();
    const gmio_vec3f& v1 = tri->v1;
    const gmio_vec3f& v2 = tri->v2;
    const gmio_vec3f& v3 = tri->v3;
    const gmio_vec3f& n = tri->n;
    mesh->AddTriangle(mesh->AddOnlyNewVertex(v1.x, v1.y, v1.z),
                      mesh->AddOnlyNewVertex(v2.x, v2.y, v2.z),
                      mesh->AddOnlyNewVertex(v3.x, v3.y, v3.z),
                      n.x, n.y, n.z);
}

static inline void gmio_stl_occ_copy_xyz(
        gmio_vec3f* vec, double x, double y, double z)
{
    vec->x = static_cast<float>(x);
    vec->y = static_cast<float>(y);
    vec->z = static_cast<float>(z);
}

static inline void gmio_stl_occ_copy_xyz(
        gmio_vec3f* vec, const gp_XYZ& coords)
{
    gmio_stl_occ_copy_xyz(vec, coords.X(), coords.Y(), coords.Z());
}

static void occmesh_get_triangle(
        const void* cookie, uint32_t tri_id, gmio_stl_triangle* tri)
{
    void* wcookie = const_cast<void*>(cookie);
    gmio_stl_occmesh_iterator* it =
            static_cast<gmio_stl_occmesh_iterator*>(wcookie);

    if (it->move_to_next_tri(tri_id)) {
        int iv1, iv2, iv3;
        double nx, ny, nz;
        const Handle_StlMesh_MeshTriangle& occTri = it->domain_tri(tri_id);
        occTri->GetVertexAndOrientation(iv1, iv2, iv3, nx, ny, nz);
        gmio_stl_occ_copy_xyz(&tri->n, nx, ny, nz);

        const TColgp_SequenceOfXYZ& vertices = it->domain_vertices();
        gmio_stl_occ_copy_xyz(&tri->v1, vertices.Value(iv1));
        gmio_stl_occ_copy_xyz(&tri->v2, vertices.Value(iv2));
        gmio_stl_occ_copy_xyz(&tri->v3, vertices.Value(iv3));
    }
}

#ifndef GMIO_SUPPORT_STL_OCC_NO_MESHVS_DATASOURCE
static void occmesh_datasource_get_triangle(
        const void* cookie, uint32_t /*tri_id*/, gmio_stl_triangle* tri)
{
    void* wcookie = const_cast<void*>(cookie);
    gmio_stl_occmesh_datasource_iterator* it =
            static_cast<gmio_stl_occmesh_datasource_iterator*>(wcookie);
    const MeshVS_DataSource* data_src = it->data_src();

    int node_count;
    MeshVS_EntityType entity_type;
    const Standard_Boolean get_geom_ok =
            data_src->GetGeom(
                it->current_element_key(),
                Standard_True, // Is element
                it->cached_element_coords(),
                node_count,
                entity_type);
    if (get_geom_ok && node_count == 3) {
        // Copy vertex coords
        const TColStd_Array1OfReal& in_coords_array = it->cached_element_coords();
        float* out_coords_ptr = &tri->v1.x;
        for (int i = 0; i < 9; ++i)
            out_coords_ptr[i] = static_cast<float>(in_coords_array.Value(i + 1));
        // Copy normal coords
        double nx, ny, nz;
        data_src->GetNormal(it->current_element_key(), 3, nx, ny, nz);
        gmio_stl_occ_copy_xyz(&tri->n, nx, ny, nz);
    }
    it->move_to_next_tri();
}
#endif // !GMIO_SUPPORT_STL_OCC_NO_MESHVS_DATASOURCE

} // namespace internal

gmio_stl_mesh gmio_stl_occmesh(const gmio_stl_occmesh_iterator& it)
{
    gmio_stl_mesh mesh = {};
    mesh.cookie = &it;
    const int domain_count = it.mesh() != NULL ? it.mesh()->NbDomains() : 0;
    for (int dom_id = 1; dom_id <= domain_count; ++dom_id)
        mesh.triangle_count += it.mesh()->NbTriangles(dom_id);
    mesh.func_get_triangle = internal::occmesh_get_triangle;
    return mesh;
}

#ifndef GMIO_SUPPORT_STL_OCC_NO_MESHVS_DATASOURCE
gmio_stl_mesh gmio_stl_occmesh(const gmio_stl_occmesh_datasource_iterator& it)
{
    gmio_stl_mesh mesh = {};
    mesh.cookie = &it;
    mesh.triangle_count =
            it.data_src() != NULL ?
                it.data_src()->GetAllElements().Extent() : 0;
    mesh.func_get_triangle = internal::occmesh_datasource_get_triangle;
    return mesh;
}
#endif // !GMIO_SUPPORT_STL_OCC_NO_MESHVS_DATASOURCE

gmio_stl_mesh_creator gmio_stl_occmesh_creator(StlMesh_Mesh* mesh)
{
    gmio_stl_mesh_creator creator = {};
    creator.cookie = mesh;
    creator.func_add_triangle = internal::occmesh_add_triangle;
    return creator;
}

gmio_stl_mesh_creator gmio_stl_occmesh_creator(const Handle_StlMesh_Mesh &hnd)
{
    return gmio_stl_occmesh_creator(internal::occMeshPtr(hnd));
}

gmio_stl_occmesh_iterator::gmio_stl_occmesh_iterator()
{
    this->init(NULL);
}

gmio_stl_occmesh_iterator::gmio_stl_occmesh_iterator(const StlMesh_Mesh *mesh)
{
    this->init(mesh);
}

gmio_stl_occmesh_iterator::gmio_stl_occmesh_iterator(const Handle_StlMesh_Mesh &hnd)
{
    this->init(internal::occMeshPtr(hnd));
}

void gmio_stl_occmesh_iterator::init(const StlMesh_Mesh* mesh)
{
    m_mesh = mesh;
    m_domain_id = 0;
    m_domain_count = m_mesh != NULL ? m_mesh->NbDomains() : 0;
    m_domain_triangles = NULL;
    m_domain_vertices = NULL;
    m_domain_first_tri_id = 0;
    m_domain_last_tri_id = 0;
    if (m_domain_count > 0)
        this->cache_domain(1);
}

void gmio_stl_occmesh_iterator::cache_domain(int dom_id)
{
    m_domain_id = dom_id;
    m_domain_triangles = &m_mesh->Triangles(dom_id);
    m_domain_vertices = &m_mesh->Vertices(dom_id);
    const int dom_tricnt = m_domain_triangles->Length();
    m_domain_first_tri_id =
            dom_tricnt > 0 ? m_domain_last_tri_id : m_domain_first_tri_id;
    m_domain_last_tri_id +=
            dom_tricnt > 0 ? dom_tricnt - 1 : 0;
}

bool gmio_stl_occmesh_iterator::move_to_next_tri(uint32_t tri_id)
{
    if (tri_id > m_domain_last_tri_id) {
        if (m_domain_id < m_domain_count) {
            ++m_domain_id;
            this->cache_domain(m_domain_id);
            return true;
        }
        return false;
    }
    return true;
}

#ifndef GMIO_SUPPORT_STL_OCC_NO_MESHVS_DATASOURCE
gmio_stl_occmesh_datasource_iterator::gmio_stl_occmesh_datasource_iterator()
    : m_data_src(NULL),
      m_element_coords(1, 1)
{ }

gmio_stl_occmesh_datasource_iterator::gmio_stl_occmesh_datasource_iterator(
        const MeshVS_DataSource *data_src)
    : m_data_src(data_src),
      m_element_coords(1, 9)
{
    if (m_data_src != NULL)
        m_element_it.Initialize(m_data_src->GetAllElements());
}

gmio_stl_occmesh_datasource_iterator::gmio_stl_occmesh_datasource_iterator(
        const Handle_MeshVS_DataSource &hnd)
    : m_data_src(hnd.operator->()),
      m_element_coords(1, 9)
{
    if (m_data_src != NULL)
        m_element_it.Initialize(m_data_src->GetAllElements());
}
#endif /* GMIO_SUPPORT_STL_OCC_NO_MESHVS_DATASOURCE */
