#include "languagemanager.h"
#include "preferences.h"
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>


LanguageManager *LanguageManager::instance()
{
    static LanguageManager instance;
    return &instance;
}

LanguageManager::LanguageManager()
    : mQtTranslator(nullptr)
    , mAppTranslator(nullptr)
{
    // 根据不同的系统设置翻译文件的路径
    mTranslationsDir = QCoreApplication::applicationDirPath();
#if defined(Q_OS_WIN32)
    mTranslationsDir += QLatin1String("/translations");
#elif defined(Q_OS_MAC)
    mTranslationsDir += QLatin1String("/../Translations");
#else
    mTranslationsDir += QLatin1String("/../share/tiled/translations");
#endif
}

LanguageManager::~LanguageManager() = default;

void LanguageManager::installTranslators()
{
    mQtTranslator.reset(new QTranslator);
    mAppTranslator.reset(new QTranslator);

    // 获取配置文件的语言，Preferences是QSetting的配置文件
    QString language = Preferences::instance()->language();
    qDebug() << "LanguageManager" << language;

    // 获取系统语言
    if (language.isEmpty())
        language = QLocale::system().name();

    const QString qtTranslationsDir =
            QLibraryInfo::location(QLibraryInfo::TranslationsPath);

    if (mQtTranslator->load(QLatin1String("qt_") + language,
                            qtTranslationsDir)) {
        QCoreApplication::installTranslator(mQtTranslator.get());
    } else {
        mQtTranslator.reset();
    }

    if (mAppTranslator->load(QLatin1String("tiled_") + language,
                             mTranslationsDir)) {
        QCoreApplication::installTranslator(mAppTranslator.get());
    } else {
        mAppTranslator.reset();
    }
}

QStringList LanguageManager::availableLanguages()
{
    if (mLanguages.isEmpty())
        loadAvailableLanguages();
    return mLanguages;
}

void LanguageManager::loadAvailableLanguages()
{
    mLanguages.clear();

    QStringList nameFilters;
    nameFilters.append(QLatin1String("*.qm"));

    QDirIterator iterator(mTranslationsDir, nameFilters,
                          QDir::Files | QDir::Readable);

    while (iterator.hasNext()) {
        iterator.next();
        const QString baseName = iterator.fileInfo().completeBaseName();
        mLanguages.append(baseName);
    }
}
