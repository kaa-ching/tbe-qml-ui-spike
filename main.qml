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
            }

            Image {
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
                id: deleteItem
                width: rulersSize
                height: rulersSize
                anchors.right: rotateLeft.left
                anchors.verticalCenter: rotateLeft.verticalCenter
                source: "qrc:/images/ActionDelete.svg"

                MouseArea {
                    anchors.fill: parent
                    onDoubleClicked: {
                        selComp.destroy()        // destroy component
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
                            if (selComp.width - mouseX < minSize)
                                myMouseX = selComp.width - minSize
                            selComp.width -= myMouseX
                            selComp.x += myMouseX * (0.5 + 0.5 * Math.cos(rotationAngle/180*Math.PI))
                            selComp.y += myMouseX * 0.5 * Math.sin(rotationAngle/180*Math.PI)
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
                            selComp.width = selComp.width + mouseX
                            if(selComp.width < minSize)
                                selComp.width = minSize
                        }
                    }
                }
            }

            Image {
                id: top
                width: rulersSize
                height: rulersSize / 1.5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.top
                source: "qrc:/images/ActionResizeHorizontally.svg"
                rotation: 90

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


            Image {
                id: bottom
                width: rulersSize
                height: rulersSize / 1.5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.bottom
                source: "qrc:/images/ActionResizeHorizontally.svg"
                rotation: 90

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
