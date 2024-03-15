#include "utils.hpp"
#include <QDebug>
#include<QImage>
#include <QQuickImageProvider>
#include <QGuiApplication>




QImage WasmImageProvider::img=QImage();
QImage WasmImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    return img;
}

void WasmImageProvider::restart(void)
{
    WasmImageProvider::img=QImage(QSize(200,150),QImage::Format_RGBA8888);
    WasmImageProvider::img.fill("black");
}

