#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
//class LanguageManager;

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = 0);
    ~PreferencesDialog();

protected:
    void changeEvent(QEvent *e) override;

private:
    void fromPreferences();                 // 从配置文件加载
    void languageSelected(int index);

private:
    Ui::PreferencesDialog *ui;

    QStringList mLanguages;
};

#endif // PREFERENCESDIALOG_H
