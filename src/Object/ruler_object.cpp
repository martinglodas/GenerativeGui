#include <Object/ruler_object.h>
#include <QPushButton>
#include <QLabel>
#include <string>
#include <OpenGL/loadingmanager.h>
#include <iostream>
#include <geologic-core/utils/customToolbox.h>
#include <mainwindow.h>

using namespace std;

ruler_object::ruler_object(View *v, MainWindow *w):
    ChildObject("ruler_object"), _status(NO_CLICK), _my_window(w) {
    m_render_layer = v->addRenderObject("ogr_points", this);
    auto rlr_mat = make_shared<Material>("Ruler material");
    rlr_mat->setColor("diffuse", QVector4D{1.0, 1.0, 1.0, 1.0});
    rlr_mat->setLineWidth(2.0f);
    rlr_mat->setDisplayMode(GL_LINE);
    rlr_mat->setOption(GL_DEPTH_TEST, false);
    setMaterial(rlr_mat);
    m_hidden = true;
    auto rlr_data = make_shared<ruler_data>();
    LoadingManager::getInstance()->load(rlr_data);
    rlr_data->setPreloaded(true);
    setData(rlr_data);
}

void ruler_object::update_points(double x, double y) {
    if (_my_window == nullptr) {
        cout << "Null pointer to window" << endl;
        return;
    }
    if (!_my_window->get_ruler_button()->isChecked()) {
        _status = NO_CLICK;
        m_hidden = true;
        return;
    }

    double distance;
    vector<float> vertices;
    ruler_data *data;

    switch (_status) {
    case NO_CLICK:
        // Do nothing
        break;

    case ONE_CLICK:
        _p2.setX(x);
        _p2.setY(y);
        distance = _p1.Distance(&_p2);
        _my_window->setRulerLabel(customToolbox::str(distance, 2).c_str());
        vertices = {static_cast<float>(_p1.getX()), static_cast<float>(_p1.getY()), 0.0f,
                    static_cast<float>(_p2.getX()), static_cast<float>(_p2.getY()), 0.0f};
        data = reinterpret_cast<ruler_data *>(m_data.get());
        data->update_vertices(vertices);
        break;

    case TWO_CLICKS:
        // No update required
        break;
    }
}

void ruler_object::click_point(double x, double y) {
    if (!_my_window->get_ruler_button()->isChecked()) {
        _status = NO_CLICK;
        m_hidden = true;
        return;
    }

    if (_status == NO_CLICK) {
        _status = ONE_CLICK;
        m_hidden = false;
        _p1.setX(x);
        _p1.setY(y);
        vector<float> vertices{static_cast<float>(_p1.getX()), static_cast<float>(_p1.getY()), 0.0f,
                              static_cast<float>(_p1.getX()), static_cast<float>(_p1.getY()), 0.0f};
        ruler_data *data = reinterpret_cast<ruler_data *>(m_data.get());
        data->update_vertices(vertices);
    } else if (_status == ONE_CLICK) {
        _status = TWO_CLICKS;
        _p2.setX(x);
        _p2.setY(y);
        m_hidden = false;
        vector<float> vertices{static_cast<float>(_p1.getX()), static_cast<float>(_p1.getY()), 0.0f,
                              static_cast<float>(_p2.getX()), static_cast<float>(_p2.getY()), 0.0f};
        ruler_data *data = reinterpret_cast<ruler_data *>(m_data.get());
        data->update_vertices(vertices);
    }
}

ruler_data::ruler_data(): UniqueData("Ruler"), _modified(false) {
    setVertices(_vertices);
    setStructureType(GL_LINES);
}

void ruler_data::draw() {
    if (_modified) {
        glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 6*sizeof(float), _vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        _modified = false;
    }
    bind();
    if(m_indices.size()) {
        glDrawElements(m_structureType, m_indices.size(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(m_structureType, 0, m_vertices.size()/3);
    }
    glBindVertexArray(0);
}

void ruler_data::update_vertices(std::vector<float> &new_vertices) {
    swap(_vertices, new_vertices);
    _modified = true;
}
