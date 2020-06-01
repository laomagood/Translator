#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include "languagemanager.h"
#include "preferences.h"
#include <QDebug>


PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog),
    mLanguages(LanguageManager::instance()->availableLanguages())
{
    ui->setupUi(this);

    Qt::WindowFlags flags = Qt::Dialog | Qt::WindowCloseButtonHint; // 去掉？
    this->setWindowFlags(flags);
    this->setWindowTitle(tr("PreferencesDialog"));

    // [1] 获取所有语言
    for (const QString &name : qAsConst(mLanguages)) {
        QLocale locale(name);
        QString string = QString(QLatin1String("%1 (%2)"))
                .arg(QLocale::languageToString(locale.language()),
                     QLocale::countryToString(locale.country()));
        ui->languageCombo->addItem(string, name);
    }

    // [2] 系统默认
    ui->languageCombo->model()->sort(0);
    ui->languageCombo->insertItem(0, tr("System default"));

    // 加载首选项
    fromPreferences();

    // 切换语言
    connect(ui->languageCombo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &PreferencesDialog::languageSelected);
    // 关闭
    connect(ui->closeButton, &QPushButton::clicked, [this] {
        this->close();
    });
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange: {
        ui->retranslateUi(this);
    }
        break;
    default:
        break;
    }
}

void PreferencesDialog::fromPreferences()
{
    Preferences *prefs = Preferences::instance();

    // [3] 设置语言
    int languageIndex = ui->languageCombo->findData(prefs->language());
    if (languageIndex == -1)
        languageIndex = 0;
    ui->languageCombo->setCurrentIndex(languageIndex);
}

void PreferencesDialog::languageSelected(int index)
{
    const QString language = ui->languageCombo->itemData(index).toString();
    Preferences *prefs = Preferences::instance();
    prefs->setLanguage(language);
    LanguageManager::instance()->installTranslators();
//    emit languageChanged();
}
