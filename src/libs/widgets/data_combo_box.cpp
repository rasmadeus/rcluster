#include "data_combo_box.h"

DataComboBox::DataComboBox(QWidget *parent)
    : QComboBox{ parent }
{
}

void DataComboBox::fill(QJsonArray const &restApiJson)
{
    clear();
    addItem(tr("None"));

    std::vector<std::pair<QString, int>> values;
    for(auto const &value : restApiJson)
    {
        auto const record = value.toObject();
        values.emplace_back(record.value(QStringLiteral("name")).toString(), record.value(QStringLiteral("id")).toInt());
    }
    std::sort(values.begin(), values.end(), [](auto const &left, auto const &right){ return right.second < left.second; });

    for(auto const &value : values)
        addItem(QStringLiteral("[%1] %2").arg(value.second).arg(value.first), value.second);

    setEnabled(count() > 1);
}

void DataComboBox::fill(Config const &config, QVector<QUuid> const &ids)
{
    clear();
    addItem(tr("None"));

    QVector<QPair<QString, QUuid>> data;
    for(auto const &id : ids)
        data << qMakePair(config.node(id).name(), id);

    std::sort(data.begin(), data.end(), [](auto const &left, auto const &right){ return left.first < right.first; });

    for(auto const & record : data)
        addItem(record.first, record.second);

    setEnabled(count() > 1);
}

void DataComboBox::fill(Config const &config, QString const &type)
{
    fill(config, config.nodes(type));
}

void DataComboBox::fillWithLocals(Config const &config, QString const &type, QUuid const &local)
{
    auto const computer = config.parent(local, QStringLiteral("COMPUTER"));
    fill(config, config.descendants(computer, type));
}

void DataComboBox::setIndex(QVariant const &data)
{
    setCurrentIndex(std::max(0, findData(data)));
}

void DataComboBox::setIndex(QVariantList const &data)
{
    for(auto const &value : data)
    {
        auto const index = findData(value.toUuid());
        if (index != -1)
        {
            setCurrentIndex(index);
            break;
        }
    }
}
