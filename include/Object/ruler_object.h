#ifndef RULER_OBJECT_H
#define RULER_OBJECT_H

#include <Object/childobject.h>
#include <ogr_geometry.h>
#include  <vector>

class MainWindow;

#include <Data/uniquedata.h>
class ruler_data: public UniqueData {
    bool _modified;
    std::vector<float> _vertices{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

public:
    ruler_data();
    virtual void draw();
    void update_vertices(std::vector<float> &new_vertices);
};

class ruler_object : public ChildObject {
    OGRPoint _p1;
    OGRPoint _p2;
    enum status {NO_CLICK, ONE_CLICK, TWO_CLICKS};
    status _status;
    MainWindow *_my_window;

public:
    ruler_object(View *v, MainWindow *w);
    ~ruler_object() {}
    void update_points(double x, double y);
    void click_point(double x, double y);
};

#endif // RULER_OBJECT_H
