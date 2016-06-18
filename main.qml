import QtQuick 2.4
import QtQuick.Controls 1.3
import "qrc:/content"

ApplicationWindow {
    id: theScene

    property var selection: undefined

    title: qsTr("Test Resize/Rotate")
    width: 640
    height: 480
    visible: true

    Image {
        id: image1
        anchors.fill: parent
        source: "http://cdn.cutestpaw.com/wp-content/uploads/2013/01/l-Kitty-attack.jpg"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("parent clicked")
                if(selection)
                    selection.destroy()
            }
        }
    }

    ViewObject {
        id: floor1
        source: "qrc:/images/used_wood_bar.png"
        width: 200
        height: 80
        x: 120
        y: 130
    }

    ViewObject {
        id: floor2
        source: "qrc:/images/used_wood_bar.png"
        width: 200
        height: 80
        fillMode: Image.Tile
        horizontalAlignment: Image.AlignLeft
        verticalAlignment: Image.AlignTop
        x: 250
        y: 230
    }

}
