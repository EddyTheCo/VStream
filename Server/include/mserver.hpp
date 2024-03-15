#include<QObject>
#include<QString>
#include <QtQml/qqmlregistration.h>
#include<QImage>
#include<QBuffer>
#include <QUdpSocket>


#include <QMediaDevices>
#include <QCameraDevice>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoSink>

#include "utils.hpp"


class VSTREAM_EXPORT VStreamer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ get_source NOTIFY sourceChanged)
    QML_ELEMENT
    QML_SINGLETON

    VStreamer(QObject *parent = nullptr);
public:
    static VStreamer* instance();
    static VStreamer *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
    {
        return instance();
    }
    enum State {
        Decoding = 0,
        Ready
    };
    Q_INVOKABLE void start();
    QString get_source(void)const{return m_source;}

signals:
    void sourceChanged();
private:
    State m_state;

    QCamera* m_camera;
    QMediaCaptureSession* m_captureSession;
    QVideoSink* m_videoSink;
    void getCamera(void);

    void setid();
    void decodePicture(QImage picture);
    QString m_source;
    QUdpSocket *m_udpSocket;

    static VStreamer* m_instance;
};


