import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

Rectangle {
    id: root
    implicitWidth: computerPage.gridCellWidth-10
    implicitHeight: computerPage.gridCellHeight-10
    color: lrectangleColor
    radius: 4

    property color lrectangleColor: (status == 0)?"white":(status==1)?"#81C784":(status==2)?"#FFF59D":"#EF9A9A"
    property color drectangleColor: (status == 0)?"#CCCCCC":(status==1)?"#66BB6A":(status==2)?"#FFF176":"#E57373"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Image {
            id: computerIcon
            source: "/image/computer-device-digital-svgrepo-com.svg"
            smooth: true
            Layout.fillHeight: true
            Layout.preferredWidth: height
            clip: true
        }

        Item {
            Text {
                x: -computerIcon.width+computerIcon.width/3
                y: computerIcon.height/4
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
                    text: "CPU: " + model.cpu
                    font.pixelSize: 16
                    font.weight: 40
                }

                Text {
                    text: "RAM: " + model.ram
                    font.pixelSize: 16
                    font.weight: 40
                }


                Text {
                    text: "Position: " + model.position
                    font.pixelSize: 16
                    font.weight: 40
                }


                Text {
                    text: "Status: " + ((model.status==0)?"Idle":(model.status==1)?"Busy":(model.status==2)?"Being registered":"Cracked")
                    font.pixelSize: 16
                    font.weight: 40
                }

                Text {
                    text: "Cost per hour: " + model.cost
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
            root.color = root.drectangleColor
        }

        onExited: {
            root.color = root.lrectangleColor
        }

        onClicked: (mouse) => {
            if (mouse.button === Qt.RightButton)
                contextMenu.popup();
        }

        Menu {
            id: contextMenu
            MenuItem {
                text: "Change"
                enabled: model.status != 1
                onTriggered: {
                    selectedItemIndex = SystemManager.computerModel.getIndexById(id)
                    computerChangeDialog.id = id
                    computerChangeDialog.cpu = cpu
                    computerChangeDialog.ram = ram
                    computerChangeDialog.position = position
                    computerChangeDialog.status = status
                    computerChangeDialog.cost = cost
                    computerChangeDialog.open()
                }
            }
            MenuItem {
                text: "Delete"
                enabled: (model.status == 0 || model.status == 3)
                onTriggered: {
                    SystemManager.computerModel.remove(SystemManager.computerModel.getIndexById(id))
                }
            }
        }
    }
}

