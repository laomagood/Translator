#include <QApplication>
#include <QDebug>
#include "languagemanager.h"
#include "languagetest.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LanguageManager::instance()->installTranslators();
    LanguageTest w;
    w.show();

    return a.exec();
}
