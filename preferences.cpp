#include "preferences.h"
#include "languagemanager.h"
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
#include <QVariantMap>
#include <QDebug>


Preferences *Preferences::instance()
{
    static Preferences instance;
    return &instance;
}

Preferences::Preferences()
{
    // [1] 系统数据目录创建配置文件
    QString strDataDir = dataLocation();
    QDir dataDir(strDataDir);
    if (!dataDir.exists())
        dataDir.mkpath(QStringLiteral("."));
    QString fileName = strDataDir + "/config.ini";
    mSettings = new QSettings(fileName, QSettings::IniFormat, this);
}

Preferences::~Preferences()
{

}

QString Preferences::language() const
{
    return mSettings->value("Interface/Language").toString();
}

void Preferences::setLanguage(const QString &language)
{
    mSettings->setValue(QLatin1String("Interface/Language"), language);
    LanguageManager::instance()->installTranslators();
    emit languageChanged();
}

QString Preferences::dataLocation()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
}

