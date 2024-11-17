import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

Rectangle {
    id: root
    implicitWidth: servicePage.gridCellWidth-10
    implicitHeight: servicePage.gridCellHeight-10
    color: lrectangleColor
    radius: 4

    property color lrectangleColor: (model.status == 0)?"white":"#81C784"
    property color drectangleColor: (model.status == 0)?"#CCCCCC":"#66BB6A"

    GridLayout {
        anchors.fill: parent
        anchors.centerIn: parent
        columns: 2

        Text {
            Layout.leftMargin: 64
            text: "ID: "+id
            font.pixelSize: 16
            font.weight: 40
        }

        Text {
            text: "Service name: " + serviceName
            font.pixelSize: 16
            font.weight: 40
        }

        Text {
            Layout.leftMargin: 64
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                text = Qt.binding(function() {
                    return "Customer's ID: " + customer.id
                })
            }
        }

        Text {
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                text = Qt.binding(function() {
                    return "Customer's name: " + customer.firstName + " " + customer.lastName
                })
            }
        }

        Text {
            visible: (serviceName=="Hire computer")
            Layout.leftMargin: 64
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                if (visible)
                    text = Qt.binding(function() {
                        if (computer)
                            return "Computer's ID: " + computer.id
                        return ""
                    })
            }
        }

        Text {
            visible: (serviceName=="Hire computer")
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                if (visible)
                    text = Qt.binding(function() {
                        return "Time use: " + timeUse
                    })
            }
        }

        Text {
            visible: (serviceName=="Order food")
            Layout.leftMargin: 64
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                if (visible)
                    text = Qt.binding(function() {
                        if (food)
                            return "Food's name: " + food.name
                        return ""
                    })
            }
        }

        Text {
            visible: (serviceName=="Order food")
            font.pixelSize: 16
            font.weight: 40

            Component.onCompleted: {
                if (visible)
                    text = Qt.binding(function() {
                        return "Number ordered: " + numberOrdered
                    })
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
                text: "Confirm"
                enabled: model.status == 0
                onTriggered: {
                    SystemManager.confirmService(id)
                }
            }

            MenuItem {
                text: "Change"
                enabled: model.status == 0
                onTriggered: {
                    selectedItemIndex = SystemManager.serviceModel.getIndexById(id)
                    serviceChangeDialog.id = id
                    serviceChangeDialog.serviceName = serviceName
                    serviceChangeDialog.customerId = customer.id
                    if (serviceName == "Hire computer") {
                        serviceChangeDialog.computerId = computer.id
                        serviceChangeDialog.timeUse = timeUse
                    } else {
                        serviceChangeDialog.foodId = food.id
                        serviceChangeDialog.numberOrdered = numberOrdered
                    }
                    serviceChangeDialog.open()
                }
            }
            MenuItem {
                text: "Delete"
                enabled: model.status == 0
                onTriggered: {
                    SystemManager.removeService(id)
                }
            }
        }
    }
}
