#include "ahriknowwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSvgWidget>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ahriknow_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    AhriknowWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.resize(800, 600);
    w.show();
    // QSvgWidget svgWidget(":/icons/plugin.svg");

    // // 设置QSvgWidget控件的大小
    // svgWidget.resize(100, 100);

    // // 显示QSvgWidget控件
    // svgWidget.show();
    return a.exec();
}
