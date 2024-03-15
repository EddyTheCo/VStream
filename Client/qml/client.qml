import QtQuick 2.0
import QtQuick.Controls
import Esterv.StreamClient

ApplicationWindow {
    visible: true
    id:window

    Image
    {
        id:control
        cache : false
        source: "image://wasm/"+VDecoder.source
        anchors.fill: parent
    }
}

