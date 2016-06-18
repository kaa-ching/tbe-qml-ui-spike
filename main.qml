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

    Rectangle {
        id: image1
        gradient: Gradient {
            GradientStop {
                position: 0.00;
                color: "#6baaf1";
            }
            GradientStop {
                position: 0.64;
                color: "#ffffff";
            }
            GradientStop {
                position: 0.98;
                color: "#175800";
            }
        }
        anchors.fill: parent

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
