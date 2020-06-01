#ifndef LANGUAGETEST_H
#define LANGUAGETEST_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPointer>

class PreferencesDialog;

class LanguageTest : public QWidget
{
    Q_OBJECT
public:
    explicit LanguageTest(QWidget *parent = nullptr);

protected:
    void changeEvent(QEvent *e) override;

private slots:
    void retranslateUi();                       // 翻译UI
    void openPreference();                      // 打开首选项

private:
    QLabel              *mHelloLabel;           // 你好
    QPushButton         *mPreferenceButton;     // 首选项按钮
    QPointer<PreferencesDialog>     mPreferencesDialog;    // 首选项对话框
};

#endif // LANGUAGETEST_H
