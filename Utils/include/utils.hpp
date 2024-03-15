#include<QObject>
#include<QString>
#include <QtQml/qqmlregistration.h>
#include<QImage>
#include <qquickimageprovider.h>

#include <QtCore/QtGlobal>
#if defined(WINDOWS_VSTREAM)
# define VSTREAM_EXPORT Q_DECL_EXPORT
#else
#define VSTREAM_EXPORT Q_DECL_IMPORT
#endif

class VSTREAM_EXPORT WasmImageProvider : public QQuickImageProvider
{
public:
    WasmImageProvider():QQuickImageProvider(QQuickImageProvider::Image)
    {
        restart();
    }
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    static void restart(void);
    static QImage img;
};
