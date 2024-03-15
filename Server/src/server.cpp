#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "mserver.hpp"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("wasm"), new WasmImageProvider());
    engine.addImportPath("qrc:/esterVtech.com/imports");

    const QUrl url("qrc:/esterVtech.com/imports/Esterv/StreamServer/qml/server.qml");
    engine.load(url);

    return app.exec();
}
