#include "layercheckbox.h"
#include <iostream>
#include <QMouseEvent>

using namespace std;

/**
 * LayerCheckBox::LayerCheckBox constructor : Initial states is checked and the checkbox stateChanged signal is connected to its slot.
 * @param *v : pointer to the vector of objects managed by the checkbox
 * @param label : the label displayed besides the checkbox
 * @param parent : the parent widget
 * @see drawcheckbox class
 */
LayerCheckBox::LayerCheckBox(std::vector<Object*> *v, const QString &label, QWidget *parent): QCheckBox{label, parent}, managed_vec(v) {
    setChecked(true);
    connect(this, SIGNAL(stateChanged(int)), this, SLOT(setState(int)));
    //connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(rightClick(QPoint)));
}

void LayerCheckBox::setState(int state) {
    if (state == Qt::Unchecked) {
        for(auto& o: *managed_vec)
        {
            o->setHidden();
        }

    } else if (state == Qt::Checked) {
        for(auto& o: *managed_vec)
        {
            o->setVisible();
        }
    }
}


