#include<QObject>
#include<QString>
#include <QtQml/qqmlregistration.h>
#include<QImage>
#include<QBuffer>
#include <QUdpSocket>
#include "utils.hpp"


class VSTREAM_EXPORT VDecoder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ get_source NOTIFY sourceChanged)
    QML_ELEMENT
    QML_SINGLETON

    VDecoder(QObject *parent = nullptr);
public:
    static VDecoder* instance();
    static VDecoder *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
    {
        return instance();
    }

    void processPendingDatagrams();
    void checkDatagram(QByteArray);

    QString get_source(void)const{return m_source;}

signals:
    void sourceChanged();
private:

    void setid();
    QString m_source;
    QUdpSocket *m_udpSocket;
    QByteArray m_cImage;
    quint8 m_format;
    quint16 m_width,m_height;

    static VDecoder* m_instance;
};


