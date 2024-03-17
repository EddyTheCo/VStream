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
        anchors.fill:parent

        Button
        {
            anchors.right:  parent.right
            anchors.top:  parent.top
            anchors.margins: 20
            text:"close"
            onClicked:
            {
                window.close();
            }
        }

    }
}

