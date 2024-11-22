#include <QApplication>
#include <QQmlApplicationEngine>
#include "systemmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SystemManager* systemManager = new SystemManager(&app);
    qmlRegisterSingletonInstance("Model", 1, 0, "SystemManager", systemManager);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("prototype", "Main");

    return app.exec();
}
