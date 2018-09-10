#include "data_combo_box.h"

DataComboBox::DataComboBox(QWidget *parent)
    : QComboBox{ parent }
{
}

void DataComboBox::setIndex(QVariant const &data)
{
    setCurrentIndex(std::max(0, findData(data)));
}
