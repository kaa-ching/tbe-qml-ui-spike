import QtQuick 2.4

Rectangle {
    id: theDecorator
    property int rulersSize: 22 // for Klaas' FullHD 24"
    property int minSize: 50
    property int rotationAngle: 0
    property Item theDecorated: null

    border {
        width: 1
        color: "black"
    }

    color: "#354682B4"
    rotation: rotationAngle

    Binding { target: theDecorated; property: "x"; value: theDecorator.x }
    Binding { target: theDecorated; property: "y"; value: theDecorator.y }
    Binding { target: theDecorated; property: "rotation"; value: rotationAngle }
    Binding { target: theDecorated; property: "width"; value: theDecorator.width }
    Binding { target: theDecorated; property: "height"; value: theDecorator.height }

    MouseArea {     // drag mouse area
        anchors.fill: parent
        drag{
            target: parent
            minimumX: 0
            minimumY: 0
            maximumX: theDecorated.parent.width - parent.width
            maximumY: theDecorated.parent.height - parent.height
            smoothed: true
        }
    }

    Image {
        // TODO/FIXME: I want to redo this to work like PowerPoint: move mouse at will, but always rotate in 15 degree steps
        id: rotateLeft
        width: rulersSize
        height: rulersSize
        anchors.horizontalCenter: parent.left
        anchors.verticalCenter: parent.top
        source: "qrc:/images/ActionRotateLeft.svg"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                rotationAngle -= 15
            }
        }
    }

    Image {
        // TODO/FIXME: I hate the fact that I cannot use a tooltip to highlight the double clicking
        id: deleteItem
        width: rulersSize
        height: rulersSize
        anchors.right: rotateLeft.left
        anchors.rightMargin: rulersSize / 2.0
        anchors.verticalCenter: rotateLeft.verticalCenter
        source: "qrc:/images/ActionDelete.svg"

        MouseArea {
            anchors.fill: parent
            onDoubleClicked: {
                theDecorator.destroy()
                theDecorated.destroy()
            }
        }
    }

    Image {
        id: rotateright
        width: rulersSize
        height: rulersSize
        anchors.horizontalCenter: parent.right
        anchors.verticalCenter: parent.top
        source: "qrc:/images/ActionRotateLeft.svg"
        mirror: true

        MouseArea {
            anchors.fill: parent
            onClicked: {
                rotationAngle += 15
            }
        }
    }

    Image {
        id: left
        width: rulersSize
        height: rulersSize / 1.5
        anchors.horizontalCenter: parent.left
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/images/ActionResizeHorizontally.svg"

        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.XAxis}
            onMouseXChanged: {
                if(drag.active){
                    var myMouseX = mouseX
                    if (theDecorator.width - mouseX < minSize)
                        myMouseX = theDecorator.width - minSize
                    theDecorator.width -= myMouseX
                    theDecorator.x += myMouseX * (0.5 + 0.5 * Math.cos(rotationAngle/180*Math.PI))
                    theDecorator.y += myMouseX * 0.5 * Math.sin(rotationAngle/180*Math.PI)
                }
            }
        }
    }

    Image {
        id: right
        width: rulersSize
        height: rulersSize / 1.5
        anchors.horizontalCenter: parent.right
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/images/ActionResizeHorizontally.svg"

        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.XAxis }
            onMouseXChanged: {
                if(drag.active){
                    var myMouseX = mouseX
                    if (theDecorator.width + mouseX < minSize)
                        myMouseX = minSize - theDecorator.width
                    theDecorator.width += myMouseX
                    theDecorator.x -= myMouseX * (0.5 - 0.5 * Math.cos(rotationAngle/180*Math.PI))
                    theDecorator.y += myMouseX * 0.5 * Math.sin(rotationAngle/180*Math.PI)
                }
            }
        }
    }

    Image {
        id: top
        width: rulersSize / 1.5
        height: rulersSize
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.top
        source: "qrc:/images/ActionResizeVertically.svg"

        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.YAxis }
            onMouseYChanged: {
                if(drag.active){
                    var myMouseY = mouseY
                    if (theDecorator.height - mouseY < minSize)
                        myMouseY = theDecorator.height - minSize
                    theDecorator.height -= myMouseY
                    theDecorator.x -= myMouseY * 0.5 * Math.sin(rotationAngle/180*Math.PI)
                    theDecorator.y += myMouseY * (0.5 + 0.5 * Math.cos(rotationAngle/180*Math.PI))
                }
            }
        }
    }


    Image {
        id: bottom
        width: rulersSize / 1.5
        height: rulersSize
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.bottom
        source: "qrc:/images/ActionResizeVertically.svg"

        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.YAxis }
            onMouseYChanged: {
                if(drag.active){
                    var myMouseY = mouseY
                    if (theDecorator.height + mouseY < minSize)
                        myMouseY = minSize - theDecorator.height
                    theDecorator.height += myMouseY
                    theDecorator.x -= myMouseY * 0.5 * Math.sin(rotationAngle/180*Math.PI)
                    theDecorator.y -= myMouseY * (0.5 - 0.5 * Math.cos(rotationAngle/180*Math.PI))
                }
            }
        }
    }
}
