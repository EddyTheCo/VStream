import QtQuick 2.0
import QtQuick.Controls
import Esterv.StreamServer

ApplicationWindow {
    visible: true
    id:window

    Image
    {
        id:control
        cache : false
        source: "image://wasm/"+VStreamer.source
        anchors.fill: parent

        Button
        {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 20
            text:"start"
            onClicked:
            {
                VStreamer.start();
            }
        }

    }
}

