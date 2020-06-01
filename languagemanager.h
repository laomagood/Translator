#pragma once

#include <QStringList>

#include <memory>

class QTranslator;


class LanguageManager
{
public:
    static LanguageManager *instance();

    /**
     * 为程序和Qt安装translators.当语言更改时再次调用
     */
    void installTranslators();

    /**
     * 返回可用语言的国家代码列表
     */
    QStringList availableLanguages();

private:
    LanguageManager();
    ~LanguageManager();

    void loadAvailableLanguages();                  // 从翻译路径提取到mLanguages

    QString mTranslationsDir;                       // 翻译文件路径
    QStringList mLanguages;                         // 语言(en,zh_CN)
    std::unique_ptr<QTranslator> mQtTranslator;     // Qt标准对话框翻译
    std::unique_ptr<QTranslator> mAppTranslator;    // 程序翻译
};

