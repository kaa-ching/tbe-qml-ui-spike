import QtQuick 2.4
import QtQuick.Controls 1.3

ApplicationWindow {
    title: qsTr("Test Resize/Rotate")
    width: 640
    height: 480
    visible: true
    property var selection: undefined

    Image {
        id: image1
        anchors.fill: parent
        source: "http://cdn.cutestpaw.com/wp-content/uploads/2013/01/l-Kitty-attack.jpg"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if(!selection)
                    selection = selectionComponent.createObject(parent, {"x": parent.width / 4, "y": parent.height / 4, "width": parent.width / 2, "height": parent.width / 2})
            }
        }
    }

    Component {
        id: selectionComponent

        Rectangle {
            id: selComp
            border {
                width: 1
                color: "black"
            }
            color: "#354682B4"

            property int rulersSize: 18
            property int minSize: 50
            property int rotationAngle: 0

            rotation: rotationAngle

            MouseArea {     // drag mouse area
                anchors.fill: parent
                drag{
                    target: parent
                    minimumX: 0
                    minimumY: 0
                    maximumX: parent.parent.width - parent.width
                    maximumY: parent.parent.height - parent.height
                    smoothed: true
                }

                onDoubleClicked: {
                    parent.destroy()        // destroy component
                }
            }

            Rectangle {
                id: rotateleft
                width: rulersSize
                height: rulersSize
                radius: rulersSize / 2
                color: "black"
                anchors.right: parent.left
                anchors.bottom: parent.top

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        rotationAngle -= 15
                    }
                }
            }

            Rectangle {
                id: rotateright
                width: rulersSize
                height: rulersSize
                radius: rulersSize / 2
                color: "black"
                anchors.left: parent.right
                anchors.bottom: parent.top

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        rotationAngle += 15
                    }
                }
            }

            Rectangle {
                id: left
                width: rulersSize
                height: rulersSize
                color: "green"
                anchors.right: parent.left
                anchors.verticalCenter: parent.verticalCenter

                MouseArea {
                    anchors.fill: parent
                    drag{ target: parent; axis: Drag.XAxis}
                    onMouseXChanged: {
                        if(drag.active){
                            var myMouseX = mouseX
                            if (selComp.width - mouseX < minSize)
                                myMouseX = selComp.width - minSize
                            selComp.width -= myMouseX
                            selComp.x += myMouseX * (0.5 + 0.5 * Math.cos(rotationAngle/180*Math.PI))
                            selComp.y += myMouseX * 0.5 * Math.sin(rotationAngle/180*Math.PI)
                        }
                    }
                }
            }

            Rectangle {
                id: right
                width: rulersSize
                height: rulersSize
                color: "black"
                anchors.left: parent.right
                anchors.verticalCenter: parent.verticalCenter

                MouseArea {
                    anchors.fill: parent
                    drag{ target: parent; axis: Drag.XAxis }
                    onMouseXChanged: {
                        if(drag.active){
                            selComp.width = selComp.width + mouseX
                            if(selComp.width < minSize)
                                selComp.width = minSize
                        }
                    }
                }
            }

            Rectangle {
                id: top
                width: rulersSize
                height: rulersSize
                color: "black"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.top

                MouseArea {
                    anchors.fill: parent
                    drag{ target: parent; axis: Drag.YAxis }
                    onMouseYChanged: {
                        if(drag.active){
                            var myMouseY = mouseY
                            if (selComp.height - mouseY < minSize)
                                myMouseY = selComp.height - minSize
                            selComp.height -= myMouseY
                            selComp.y += myMouseY
                        }
                    }
                }
            }


            Rectangle {
                width: rulersSize
                height: rulersSize
                color: "black"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.bottom

                MouseArea {
                    anchors.fill: parent
                    drag{ target: parent; axis: Drag.YAxis }
                    onMouseYChanged: {
                        if(drag.active){
                            selComp.height = selComp.height + mouseY
                            if(selComp.height < minSize)
                                selComp.height = minSize
                        }
                    }
                }
            }
        }
    }
}
