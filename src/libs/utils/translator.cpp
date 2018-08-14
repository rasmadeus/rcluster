#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QLocale>
#include <QTranslator>
#include "translator.h"

Translator::Translator(Translator::Type type)
{
    load(QCoreApplication::applicationName(), translationsDir());
    load(QStringLiteral("common"));

    if (type == Type::AppAndPlugins)
        load(QStringLiteral("plugins"));
}

Translator::Translator(QString const &type)
    : Translator{}
{
    load(type, QStringLiteral("%1%2plugins").arg(translationsDir()).arg(QDir::separator()));
}

void Translator::load(QString const &fileName, QString const &dir)
{
    auto translator = new QTranslator{};
    if (translator->load(QLocale::system(), fileName, QStringLiteral("_"), dir))
    {
        if (qApp->installTranslator(translator))
        {
            qDebug() << "Translator has been loaded" << fileName << "from dir" << dir;
            return;
        }
    }

    qWarning() << "Failed to load translator" << fileName << "in directory" << dir;
    translator->deleteLater();
}

void Translator::load(QString const &subDir)
{
    auto const path = translationsDir() + QDir::separator() + subDir;
    for(auto const &fileName : QDir{ path }.entryList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot))
        load(fileName, path);
}

QString Translator::translationsDir() const
{
    return QStringLiteral("%1%2translations").arg(QCoreApplication::applicationDirPath()).arg(QDir::separator());
}
