import QtQuick 2.4
import QtQuick.Controls 1.3
import TBEView 1.0
import "qrc:/content"

Item {
    id: theScene
    objectName: "root"

    width: RCS.renderPixels
    height: (RCS.renderPixels/RCS.aspectRatio)

    property var selection: undefined
    property real theScale: 1.0

    function createViewObject(aName) {
        var QComponentForVO = Qt.createComponent("content/ViewObject.qml");
        var myVO = QComponentForVO.createObject(theScene);
        myVO.objectName = aName;
        return true;
    }

    transform: [
        Scale {
            id: scale
            xScale: theScale
            yScale: theScale
        }
    ]

    Rectangle {
        id: background
        objectName: "background"
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

        x: 0
        y: 0
        width: RCS.renderPixels
        height: (RCS.renderPixels/RCS.aspectRatio)

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if(selection)
                    selection.destroy()
            }
        }
    }

//    ViewObject {
//        id: wall1
//        source: "qrc:/images/oldbrick.jpg"
//        width: 400
//        height: 500
//        x: 1200
//        y: 1300
//    }

    ViewObject {
        id: wall2
        objectName: "wall2"
        source: "qrc:/images/oldbrick.jpg"
        width: 800
        height: 300
        fillMode: Image.Tile
        horizontalAlignment: Image.AlignLeft
        verticalAlignment: Image.AlignTop
        x: 250
        y: 230
    }
}
