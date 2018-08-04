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

    Slave slave0;
    slave0.setId(QUuid::createUuid());
    slave0.setType(QStringLiteral("SLAVE_0"));

        Slave slave01;
        slave01.setId(QUuid::createUuid());
        slave01.setType(QStringLiteral("SLAVE_01"));
        slave01.setParent(slave0.id());

        Slave slave02;
        slave02.setId(QUuid::createUuid());
        slave02.setType(QStringLiteral("SLAVE_01"));
        slave02.setParent(slave0.id());

        Slave slave03;
        slave03.setId(QUuid::createUuid());
        slave03.setType(QStringLiteral("SLAVE_02"));
        slave03.setParent(slave0.id());

    config->append(slave0);
    config->append(slave01);
    config->append(slave02);
    config->append(slave03);

    return config;
}

void ConfigTest::testAppend_data()
{
    auto config = makeConfig();

    QTest::addColumn<int>("actualSize");
    QTest::addColumn<int>("expectedSize");
    QTest::newRow("0") << config->slaves(QStringLiteral("SLAVE_01")).size() << 2;
    QTest::newRow("1") << config->slaves(QStringLiteral("SLAVE_02")).size() << 1;
    QTest::newRow("2") << config->slaves(QStringLiteral("SLAVE_0")).size() << 1;
}

void ConfigTest::testAppend()
{
    QFETCH(int, actualSize);
    QFETCH(int, expectedSize);
    QCOMPARE(actualSize, expectedSize);
}

QTEST_APPLESS_MAIN(ConfigTest)

#include "config_test.moc"
