#include "mclient.hpp"

#include <QDebug>
#include<QImage>
#include <QGuiApplication>


VDecoder* VDecoder::m_instance=nullptr;


#if QT_CONFIG(permissions)
#include <QPermission>
#endif



VDecoder* VDecoder::instance()
{
    if (!m_instance) m_instance=new VDecoder();
    return m_instance;
}
VDecoder::VDecoder(QObject *parent):QObject(parent),m_udpSocket(new QUdpSocket(this)),m_format(0),
    m_width(0),m_height(0)
{
    m_udpSocket->bind(45454,QUdpSocket::ShareAddress);
    connect(m_udpSocket, &QUdpSocket::readyRead,
            this, &VDecoder::processPendingDatagrams);

}

void VDecoder::processPendingDatagrams()
{
    QByteArray datagram;
    while (m_udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(m_udpSocket->pendingDatagramSize()));
        m_udpSocket->readDatagram(datagram.data(), datagram.size());
        checkDatagram(datagram);
    }

}
void VDecoder::checkDatagram(QByteArray datagram)
{

    const auto sindex=datagram.indexOf("start");
    if(sindex!=-1)
    {
        if(m_format)
        {
            qDebug()<<"m_cImage:"<<m_cImage.size();
            const auto picture=QImage((const uchar*)m_cImage.constData(),m_width,m_height,(QImage::Format)m_format);
            WasmImageProvider::img=picture;
            setid();
        }


        m_cImage.clear();
        datagram=datagram.sliced(sindex+6);
        auto buffer=QDataStream(&datagram,QIODevice::ReadOnly);
        buffer.setByteOrder(QDataStream::LittleEndian);
        buffer>>m_width>>m_height>>m_format;
        qDebug()<<"recieving:"<<m_width<<" "<<m_height<<" "<<m_format;
    }
    else
    {
        m_cImage.append(datagram);
    }
}


void VDecoder::setid()
{
    static quint8 index=0;
    m_source="qrimage"+QString::number(index);
    emit sourceChanged();
    index++;
}
