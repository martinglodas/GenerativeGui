#pragma once

#include <QCheckBox>
#include <Scene/layer.h>
#include <vector>
#include <Object/object.h>


class LayerCheckBox: public QCheckBox {
    Q_OBJECT

public:
    LayerCheckBox() = delete;
    LayerCheckBox(std::vector<Object*>* v, const QString &label, QWidget *parent);
    ~LayerCheckBox() {}


    std::vector<Object*> * managed_vec;

public slots:
    void setState(int state);
};
