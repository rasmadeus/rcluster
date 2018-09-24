#ifndef DATA_COMBO_BOX_H
#define DATA_COMBO_BOX_H

#include <QComboBox>
#include <QUuid>
#include <config.h>
#include <slave.h>
#include "widgets_global.h"

class Config;

class WIDGETS_SHARED_EXPORT DataComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit DataComboBox(QWidget *parent = nullptr);

public:
    void fill(Config const &config, QVector<QUuid> const &ids);
    void fill(Config const &config, QString const &type);
    void fillWithLocals(Config const &config, QString const &type, QUuid const &local);

public:
    void setIndex(QVariant const &data);
    void setIndex(QVariantList const &data);
};

#endif // DATA_COMBO_BOX_H
