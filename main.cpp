#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    MainWindow mainWindow(&engine);
    engine.rootContext()->setContextProperty("cpp_mainWindow", &mainWindow);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
