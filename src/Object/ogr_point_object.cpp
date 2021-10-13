#include <Object/ogr_point_object.h>
#include <OpenGL/loadingmanager.h>

/*!
 * \brief ogr_point_object::ogr_point_object constructor
 * \param ogr_pt_data data that will be managed by the object
 * \param ogr_pt_mat material that will be managed by the object. Shall define point size and color for points, line width and color for lines.
 * \param v the view to be linked to (required for the geologic GUI framework to display points and lines)
 */
ogr_point_object::ogr_point_object(std::shared_ptr<Data> ogr_pt_data, std::shared_ptr<Material> ogr_pt_mat, type ogr_type, View *v): ChildObject("OGRPoint") {
    switch(ogr_type)
    {
        case point :
            m_render_layer = v->addRenderObject("ogr_points", this);
        break;
        case ligne :
            m_render_layer = v->addRenderObject("ogr_lignes", this);
        break;
        case multiligne :
            m_render_layer = v->addRenderObject("ogr_multilignes", this);
        break;
        case multipolygon :
            m_render_layer = v->addRenderObject("ogr_multipolygons", this);
        break;
        case other :
            m_render_layer = v->addRenderObject("ogr_others", this);
        break;
        case meshgrid :
            m_render_layer = v->addRenderObject("grid_mesh", this);
        break;
        default:;
    }
    setData(ogr_pt_data);
    setMaterial(ogr_pt_mat);
    LoadingManager::getInstance()->load(ogr_pt_data);
    ogr_pt_data->setPreloaded(true);
}

