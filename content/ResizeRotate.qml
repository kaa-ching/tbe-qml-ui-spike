import QtQuick 2.4
import TBEView 1.0

ResizeRotateMoveUndoItem {
    id: theDecorator
    objectName: "theDecorator"
    property int minSize: 50
    property int rotationAngle: 0

    rotation: rotationAngle

    Rectangle {
        border {
            width: 1
            color: "black"
        }
        color: theDecorated.isColliding ? "#80FF5050" : "#8050FF50"
        visible: true
        anchors.fill: parent
    }

    // make sure theDecorated follows our changes (due to Resize or Rotate)
    Binding { target: theDecorated; property: "x"; value: theDecorator.x }
    Binding { target: theDecorated; property: "y"; value: theDecorator.y }
    Binding { target: theDecorated; property: "rotation"; value: rotationAngle }
    Binding { target: theDecorated; property: "width"; value: theDecorator.width }
    Binding { target: theDecorated; property: "height"; value: theDecorator.height }

    // make sure we follow theDecotated position changes (due to dragging)
    Binding { target: theDecorator; property: "x"; value: theDecorated.x }
    Binding { target: theDecorator; property: "y"; value: theDecorated.y }

    Image {
        // TODO/FIXME: I want to redo this to work like PowerPoint: move mouse at will, but always rotate in 15 degree steps
        id: rotateLeft
        width: RCS.handleWidth / theScale
        height: RCS.handleHeight / theScale
        anchors.horizontalCenter: parent.left
        anchors.verticalCenter: parent.top
        source: "qrc:/images/ActionRotateLeft.svg"
        visible: theDecorated.isRotate === true;

        property real origA : 0
        property bool isFirstPress : true

        MouseArea {
            anchors.fill: parent
            onPositionChanged: {
                if (rotateLeft.isFirstPress) {
                    var mpos = mapToItem(null, mouseX, mouseY);
                    var dpos = mapToItem(null, theDecorator.x, theDecorator.y)
                    rotateLeft.origA = rotationAngle - theDecorator.vector2AngleDegrees(dpos.x - mpos.x, dpos.y - mpos.y);
                    rotateLeft.isFirstPress = false;
                }
                else {
                    var mpos = mapToItem(null, mouseX, mouseY);
                    var dpos = mapToItem(null, theDecorator.x, theDecorator.y);
                    var newAngle = rotateLeft.origA + theDecorator.vector2AngleDegrees(dpos.x - mpos.x, dpos.y - mpos.y);
                    rotationAngle = Math.floor(newAngle/15. + 0.5)* 15.;
                }
            }
            onReleased: {
                rotateLeft.isFirstPress = true;
                console.log("released")
            }
        }
    }

    Image {
        // TODO/FIXME: I hate the fact that I cannot use a tooltip to highlight the double clicking
        id: deleteItem
        width: RCS.handleWidth / theScale
        height: RCS.handleHeight / theScale
        anchors.right: rotateLeft.left
        anchors.rightMargin: RCS.handleWidth / 2.0
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
        id: rotateRight
        width: RCS.handleWidth / theScale
        height: RCS.handleHeight / theScale
        anchors.horizontalCenter: parent.right
        anchors.verticalCenter: parent.top
        source: "qrc:/images/ActionRotateLeft.svg"
        mirror: true
        visible: theDecorated.isRotate === true;

        property real origA : 0
        property bool isFirstPress : true

        MouseArea {
            anchors.fill: parent
            onPositionChanged: {
                if (rotateRight.isFirstPress) {
                    var mpos = mapToItem(null, mouseY, mouseX);
                    var dpos = mapToItem(null, theDecorator.y, theDecorator.x)
                    rotateRight.origA = rotationAngle - theDecorator.vector2AngleDegrees(dpos.x - mpos.x, dpos.y - mpos.y);
                    rotateRight.isFirstPress = false;
                }
                else {
                    var mpos = mapToItem(null, mouseX, mouseY);
                    var dpos = mapToItem(null, theDecorator.y, theDecorator.x);
                    var newAngle = rotateRight.origA + theDecorator.vector2AngleDegrees(dpos.x - mpos.x, dpos.y - mpos.y);
                    rotationAngle = Math.ceil(newAngle/15. - 0.5)* 15.;
                }
            }
            onReleased: {
                rotateRight.isFirstPress = true;
                console.log("released")
            }
        }
    }

    Image {
        id: left
        width: RCS.handleWidth / theScale
        height: RCS.handleHeight / 1.5 / theScale
        anchors.horizontalCenter: parent.left
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/images/ActionResizeHorizontally.svg"
        visible: theDecorated.isHResize === true;

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
        width: RCS.handleWidth / theScale
        height: RCS.handleHeight / 1.5 / theScale
        anchors.horizontalCenter: parent.right
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/images/ActionResizeHorizontally.svg"
        visible: theDecorated.isHResize === true;

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
        width: RCS.handleWidth / 1.5 / theScale
        height: RCS.handleHeight / theScale
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.top
        source: "qrc:/images/ActionResizeVertically.svg"
        visible: theDecorated.isVResize === true;

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
        width: RCS.handleWidth / 1.5 / theScale
        height: RCS.handleHeight / theScale
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.bottom
        source: "qrc:/images/ActionResizeVertically.svg"
        visible: theDecorated.isVResize === true;

        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.YAxis }
            onMouseYChanged: {
                if(drag.active) {
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
