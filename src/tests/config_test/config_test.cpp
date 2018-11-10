#include <memory>
#include <QString>
#include <QtTest>
#include <config.h>

class ConfigTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testAppend_data();
    void testAppend();

private:
    std::unique_ptr<Config> makeConfig() const;
};

std::unique_ptr<Config> ConfigTest::makeConfig() const
{
    auto config = std::make_unique<Config>();

    Node node0;
    node0.setId(QUuid::createUuid());
    node0.setType(QStringLiteral("SLAVE_0"));

        Node node01;
        node01.setId(QUuid::createUuid());
        node01.setType(QStringLiteral("SLAVE_01"));
        node01.setParent(node0.id());

        Node node02;
        node02.setId(QUuid::createUuid());
        node02.setType(QStringLiteral("SLAVE_01"));
        node02.setParent(node0.id());

        Node node03;
        node03.setId(QUuid::createUuid());
        node03.setType(QStringLiteral("SLAVE_02"));
        node03.setParent(node0.id());

    config->append(node0);
    config->append(node01);
    config->append(node02);
    config->append(node03);

    return config;
}

void ConfigTest::testAppend_data()
{
    auto config = makeConfig();

    QTest::addColumn<int>("actualSize");
    QTest::addColumn<int>("expectedSize");
    QTest::newRow("0") << config->nodes(QStringLiteral("SLAVE_01")).size() << 2;
    QTest::newRow("1") << config->nodes(QStringLiteral("SLAVE_02")).size() << 1;
    QTest::newRow("2") << config->nodes(QStringLiteral("SLAVE_0")).size() << 1;
}

void ConfigTest::testAppend()
{
    QFETCH(int, actualSize);
    QFETCH(int, expectedSize);
    QCOMPARE(actualSize, expectedSize);
}

QTEST_APPLESS_MAIN(ConfigTest)

#include "config_test.moc"
