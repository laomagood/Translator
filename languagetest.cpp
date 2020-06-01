#include "languagetest.h"
#include "preferencesdialog.h"
#include "languagemanager.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QEvent>

LanguageTest::LanguageTest(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(500, 200);

    mHelloLabel = new QLabel();
    mPreferenceButton = new QPushButton();

    auto hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(mHelloLabel);
    hBoxLayout->addWidget(mPreferenceButton);
    this->setLayout(hBoxLayout);
    this->layout()->setMargin(30);

    retranslateUi();


    // 打开首选项
    connect(mPreferenceButton, &QPushButton::clicked, this, &LanguageTest::openPreference);
}

void LanguageTest::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange: {
            retranslateUi();
        }
        break;
    default:
        break;
    }
}

void LanguageTest::retranslateUi()
{
    this->setWindowTitle(tr("LanguageTest"));
    this->mHelloLabel->setText(tr("hello"));
    this->mPreferenceButton->setText(tr("preference"));
}

void LanguageTest::openPreference()
{
    if (!mPreferencesDialog) {
        mPreferencesDialog = new PreferencesDialog(this);
        mPreferencesDialog->setAttribute(Qt::WA_DeleteOnClose);     // 关闭时Delete
    }

    mPreferencesDialog->show();
    mPreferencesDialog->activateWindow();
    mPreferencesDialog->raise();
}
