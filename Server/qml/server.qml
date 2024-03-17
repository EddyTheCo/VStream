import QtQuick 2.0
import QtQuick.Controls
import Esterv.StreamServer
import QtMultimedia

ApplicationWindow {
    visible: true
    id:window

    MediaDevices {
        id: mediaDevices
    }
    CaptureSession {
        camera: Camera {
            cameraDevice: mediaDevices.defaultVideoInput
            active:true
        }
        videoOutput: videoOutput
    }
    VideoOutput {
            id: videoOutput
            anchors.fill: parent
        }

}

