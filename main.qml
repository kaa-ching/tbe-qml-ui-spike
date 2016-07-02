import QtQuick 2.4
import QtQuick.Controls 1.3
import TBEView 1.0
import "qrc:/content"

Item {
    id: theScene

    property var selection: undefined

    width: 1200
    height: 500

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
                if(selection)
                    selection.destroy()
            }
        }
    }

    ViewObject {
        id: wall1
        source: "qrc:/images/oldbrick.jpg"
        width: 80
        height: 200
        x: 120
        y: 130
    }

    ViewObject {
        id: wall2
        source: "qrc:/images/oldbrick.jpg"
        width: 80
        height: 200
        fillMode: Image.Tile
        horizontalAlignment: Image.AlignLeft
        verticalAlignment: Image.AlignTop
        x: 250
        y: 230
    }

}
