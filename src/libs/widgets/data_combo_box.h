#ifndef DATA_COMBO_BOX_H
#define DATA_COMBO_BOX_H

#include <QComboBox>
#include "widgets_global.h"

class WIDGETS_SHARED_EXPORT DataComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit DataComboBox(QWidget *parent = nullptr);

public:
    void setIndex(QVariant const &data);
};

#endif // DATA_COMBO_BOX_H
