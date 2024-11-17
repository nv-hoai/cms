import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

Rectangle {
    id: root
    implicitWidth: customerPage.gridCellWidth-10
    implicitHeight: customerPage.gridCellHeight-10
    color: lrectangleColor
    radius: 4

    property color lrectangleColor: (model.status == 0)?"white":(model.status==1)?"#81C784":"#FFF59D"
    property color drectangleColor: (model.status == 0)?"#CCCCCC":(model.status==1)?"#66BB6A":"#FFF176"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Image {
            id: customerIcon
            source: "/image/user-svgrepo-com.svg"
            smooth: true
            Layout.leftMargin: 12
            Layout.preferredWidth: implicitWidth/11
            Layout.preferredHeight: implicitHeight/11
            clip: true
        }

        Item {
            Text {
                x: -customerIcon.width+customerIcon.width/3.5
                y: customerIcon.height/2.5
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
                    text: "First name: " + firstName
                    font.pixelSize: 16
                    font.weight: 40
                }

                Text {
                    text: "Last name: " + lastName
                    font.pixelSize: 16
                    font.weight: 40
                }


                Text {
                    text: "Age: " + age
                    font.pixelSize: 16
                    font.weight: 40
                }


                Text {
                    text: "Gender: " + ((gender)?"Male":"Female")
                    font.pixelSize: 16
                    font.weight: 40
                }

                Text {
                    text: "Status: " + ((!status)?"Not using any service":(status==1)?"Using service":"Registering")
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
                    selectedItemIndex = SystemManager.customerModel.getIndexById(id)
                    customerChangeDialog.id = id
                    customerChangeDialog.firstName = firstName
                    customerChangeDialog.lastName = lastName
                    customerChangeDialog.age = age
                    customerChangeDialog.gender = gender
                    customerChangeDialog.open()
                }
            }
            MenuItem {
                text: "Delete"
                enabled: model.status == 0
                onTriggered: {
                    SystemManager.customerModel.remove(SystemManager.customerModel.getIndexById(id))
                }
            }
        }
    }
}

