#include "mserver.hpp"

#include <QDebug>
#include<QImage>
#include <QQuickImageProvider>
#include <QGuiApplication>


VStreamer* VStreamer::m_instance=nullptr;


#if QT_CONFIG(permissions)
#include <QPermission>
#endif

void VStreamer::getCamera(void)
{
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    qDebug()<<"Cameras:"<<cameras.size();
    if(cameras.size())
    {
        QCameraDevice best=cameras.front();
        for (const QCameraDevice &cameraDevice : cameras) {
            qDebug()<<"description:"<<cameraDevice.description()<<" "<<cameraDevice.id();
        }
        m_camera=new QCamera(best,this);
        auto bvF=best.videoFormats().at(0);
        for (const QCameraFormat &format : best.videoFormats())
        {
            qDebug()<<"Cameras.format:"<<format.resolution()<<" "<<format.pixelFormat()<<" "<<format.maxFrameRate();
            if(abs(format.resolution().width()*1.0-format.resolution().height())<abs(bvF.resolution().width()*1.0-bvF.resolution().height()))
            {
                bvF=format;
            }
        }
        m_camera->setCameraFormat(bvF);

    }

}

VStreamer* VStreamer::instance()
{
    if (!m_instance) m_instance=new VStreamer();
    return m_instance;
}
VStreamer::VStreamer(QObject *parent):QObject(parent),m_udpSocket(new QUdpSocket(this)),m_camera(nullptr),
    m_captureSession(new QMediaCaptureSession(this)),m_videoSink(new QVideoSink(this)),
    m_state(Ready)
{

    m_captureSession->setVideoOutput(m_videoSink);
    QObject::connect(m_videoSink,&QVideoSink::videoFrameChanged,this,[=](const QVideoFrame & Vframe)
                     {

                         if(m_camera&&m_camera->isActive()&&Vframe.isValid()){
                             auto picture=Vframe.toImage();
                             WasmImageProvider::img=picture;
                             setid();
                                 decodePicture(picture);
                         }
                     });


}

void VStreamer::start()
{

#if QT_CONFIG(permissions)
    QCameraPermission cPermission;
    switch (qApp->checkPermission(cPermission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(cPermission, this,
                                &VStreamer::start);
        return;
    case Qt::PermissionStatus::Denied:
        return;
    case Qt::PermissionStatus::Granted:
        if(!m_camera)
        {
            getCamera();
            if(m_camera)
            {
                m_captureSession->setCamera(m_camera);

                QObject::connect(m_camera,&QCamera::errorOccurred,[](QCamera::Error error, const QString &errorString)
                                 {
                                     qDebug()<<"Camera Error:"<<errorString;
                                 });
            }

        }
        if(m_camera)
        {
            m_camera->start();
        }

        return;
    }

#endif
}

void VStreamer::decodePicture(QImage picture)
{
    picture.convertTo(QImage::Format_Grayscale8);

    QByteArray datagrams = QByteArray::fromRawData((const char*)picture.constBits(), picture.sizeInBytes());

    
    QByteArray info;
    auto buffer=QDataStream(&info,QIODevice::WriteOnly | QIODevice::Append);
    buffer.setByteOrder(QDataStream::LittleEndian);

    buffer<<"start"<<static_cast<quint16>(picture.width())<<static_cast<quint16>(picture.height());
    buffer<<static_cast<quint8>(picture.format());
    m_udpSocket->writeDatagram(info, QHostAddress::Broadcast, 45454);

    while(datagrams.size())
    {
        QByteArray datagram;
        if(datagrams.size()>4096)
        {
            datagram=datagrams.first(4096);
            datagrams=datagrams.sliced(4096);
        }
        else
        {
            datagram=datagrams;
            datagrams.resize(0);
        }
        m_udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
    }
	

}

void VStreamer::setid()
{
    static quint8 index=0;
    m_source="qrimage"+QString::number(index);
    emit sourceChanged();
    index++;
}

