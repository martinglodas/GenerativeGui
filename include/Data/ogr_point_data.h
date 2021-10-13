#ifndef OGR_POINT_DATA_H
#define OGR_POINT_DATA_H

#include <Data/uniquedata.h>
#include <gdal/ogr_geometry.h>

/*!
 * \brief The ogr_point_data class handles one OGRPoint data conversion and loading into GPU
 */
class ogr_point_data : public UniqueData {
public:
    ogr_point_data(OGRPoint *pt = nullptr, bool transform = true);
    virtual ~ogr_point_data() {};
};

/*!
 * \brief The ogr_multipoint_data class converts and loads an OGRMultipoint instance into the GPU
 */
class ogr_multipoint_data: public UniqueData {
public:
    ogr_multipoint_data(OGRMultiPoint *pts= nullptr);
    virtual ~ogr_multipoint_data() {}
};

/*!
 * \brief The ogr_linestring_data class converts and loads an OGRLineString instance into the GPU
 */
class ogr_linestring_data: public UniqueData {
public:
    ogr_linestring_data(OGRLineString *linestring=nullptr, bool transform = true);

    virtual ~ogr_linestring_data() {}
};

/*!
 * \brief The ogr_multilinestring_data class converts and loads an OGRLineString instance into the GPU
 */
class ogr_multilinestring_data: public UniqueData {
    std::vector<GLsizei> m_indices_sizes;
    std::vector<GLvoid *> m_indices_offsets;
public:
    ogr_multilinestring_data(OGRMultiLineString *multi = nullptr);
    virtual ~ogr_multilinestring_data() {}
    virtual void draw() override;
};

class ogr_multipolygon_data: public UniqueData {
public:
    ogr_multipolygon_data(OGRMultiPolygon *polygons=nullptr);
    virtual ~ogr_multipolygon_data() {}
};

struct mesh_wrapper {
    OGRPoint origin;
    float width;
    float alpha;

    mesh_wrapper(const OGRPoint &p={0.0, 0.0}, float w=25.0, float a=1.0): origin(p), width(w), alpha(a) {}
};

class mesh_grid_data: public UniqueData {
    GLuint _alpha_buffer;
    std::vector<float> _alphas;

public:
    mesh_grid_data(const std::vector<mesh_wrapper> &grid);
    virtual ~mesh_grid_data() {};
    virtual void load() override;
    virtual void draw() override;
};

#endif // OGR_POINT_DATA_H
