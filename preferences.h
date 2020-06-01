#pragma once

#include <QObject>
#include <QSettings>


class Preferences : public QObject
{
    Q_OBJECT

public:
    static Preferences *instance();

    QString language() const;
    void setLanguage(const QString &language);

    /**
     * 返回数据本地文件夹路径
     */
    static QString dataLocation();

signals:
    void languageChanged();

private:
    Preferences();
    ~Preferences();

private:
    QSettings *mSettings;

};
