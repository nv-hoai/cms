import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

Rectangle {
    id: root
    implicitWidth: foodPage.gridCellWidth-10
    implicitHeight: foodPage.gridCellHeight-10
    color: "white"
    radius: 4

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Image {
            id: foodImage
            source: imageSource
            smooth: true
            Layout.leftMargin: 12
            Layout.preferredWidth: implicitWidth/13
            Layout.preferredHeight: implicitHeight/13
            clip: true
        }

        Item {
            Text {
                x: -foodImage.width+foodImage.width/3.5
                y: foodImage.height/3.4
                text: "ID: "+id
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            GridLayout {
                anchors.centerIn: parent
                columns: 2

                Text {
                    Layout.columnSpan: 2
                    text: "Name: " + name
                    font.pixelSize: 16
                    font.weight: 40
                }

                Text {
                    text: "Remain: " + remain
                    font.pixelSize: 16
                    font.weight: 40
                }


                Text {
                    text: "Cost: " + cost
                    font.pixelSize: 16
                    font.weight: 40
                }
            }
        }
    }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onEntered: {
            root.color = "#CCCCCC"
        }

        onExited: {
            root.color = "white"
        }

        onClicked: (mouse) => {
            if (mouse.button === Qt.RightButton)
                contextMenu.popup();
        }

        Menu {
            id: contextMenu
            MenuItem {
                text: "Change"
                onTriggered: {
                    selectedItemIndex = SystemManager.foodModel.getIndexById(id)
                    foodChangeDialog.id = id
                    foodChangeDialog.name = name
                    foodChangeDialog.remain = remain
                    foodChangeDialog.cost = cost
                    foodChangeDialog.imageSource = imageSource
                    foodChangeDialog.open()
                }
            }
            MenuItem {
                text: "Delete"
                onTriggered: {
                    SystemManager.foodModel.remove(SystemManager.foodModel.getIndexById(id))
                }
            }
        }
    }
}
