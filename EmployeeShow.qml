import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

Rectangle {
    id: root
    implicitWidth: employeePage.gridCellWidth-10
    implicitHeight: employeePage.gridCellHeight-10
    color: "white"
    radius: 4

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Image {
            id: employeeIcon
            source: "/image/employee-id-svgrepo-com.svg"
            smooth: true
            Layout.leftMargin: 12
            Layout.preferredWidth: implicitWidth/13
            Layout.preferredHeight: implicitHeight/13
            clip: true
        }

        Item {
            Text {
                x: -employeeIcon.width+employeeIcon.width/3.5
                y: employeeIcon.height/2.2
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
                    // Layout.columnSpan: 2
                    text: "First name: " + firstName
                    font.pixelSize: 16
                    font.weight: 40
                }

                Text {
                    // Layout.columnSpan: 2
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
                    text: "Position: " + position
                    font.pixelSize: 16
                    font.weight: 40
                }

                Text {
                    text: "Worked days: " + workedDays
                    font.pixelSize: 16
                    font.weight: 40
                }

                Text {
                    text: "Time work: " + timeWork
                    font.pixelSize: 16
                    font.weight: 40
                }

                Text {
                    text: "Base salary: " + baseSalary
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
                    selectedItemIndex = SystemManager.employeeModel.getIndexById(id)
                    employeeChangeDialog.id = id
                    employeeChangeDialog.firstName = firstName
                    employeeChangeDialog.lastName = lastName
                    employeeChangeDialog.age = age
                    employeeChangeDialog.gender = gender
                    employeeChangeDialog.position = position
                    employeeChangeDialog.workedDays = workedDays
                    employeeChangeDialog.timeWork = timeWork
                    employeeChangeDialog.baseSalary = baseSalary
                    employeeChangeDialog.open()
                }
            }
            MenuItem {
                text: "Delete"
                onTriggered: {
                    SystemManager.employeeModel.remove(SystemManager.employeeModel.getIndexById(id))
                }
            }
        }
    }
}
