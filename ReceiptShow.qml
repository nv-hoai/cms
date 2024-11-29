import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

Rectangle {
    id: root
    implicitWidth: receiptPage.gridCellWidth-10
    implicitHeight: receiptPage.gridCellHeight-10
    color: lrectangleColor
    radius: 4

    property color lrectangleColor: (model.status == 0)?"white":"#81C784"
    property color drectangleColor: (model.status == 0)?"#CCCCCC":"#66BB6A"
    property int receiptIndex: model.index

    function formatTimeFromSeconds(seconds) {
        var hours = Math.floor(seconds / 3600);
        var minutes = Math.floor((seconds % 3600) / 60);
        var secs = seconds % 60;

        var hoursStr = hours < 10 ? "0" + hours : "" + hours;
        var minutesStr = minutes < 10 ? "0" + minutes : "" + minutes;
        var secondsStr = secs < 10 ? "0" + secs : "" + secs;

        return hoursStr + ":" + minutesStr + ":" + secondsStr;
    }

    GridLayout {
        anchors.fill: parent
        anchors.centerIn: parent
        columns: 2

        Text {
            Layout.columnSpan: 2
            Layout.leftMargin: 32
            text: "ID: "+id
            font.pixelSize: 16
            font.weight: 40
        }

        Text {
            Layout.leftMargin: 32
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
            Layout.columnSpan: (paidTimeShow.visible)?1:2
            Layout.leftMargin: 32
            text: "Created time: " + createdTime
            font.pixelSize: 16
            font.weight: 40
        }

        Text {
            id: paidTimeShow
            visible: model.status == 1
            text: "Paid time: " + paidTime
            font.pixelSize: 16
            font.weight: 40
        }

        Repeater {
            id: rp
            model: receiptPage.gridModel.serviceNumber(receiptIndex)

            ColumnLayout {
                property var service: receiptPage.gridModel.getService(receiptIndex, index)
                Layout.leftMargin: (index%2)?0:32
                Layout.columnSpan: (index == rp.count-1 && index%2 == 0)?2:1

                Component.onCompleted: {
                    if (service.serviceName == "Hire computer")
                        service = receiptPage.gridModel.toHireComputer(service);
                    else
                        service = receiptPage.gridModel.toOrderFood(service);
                }

                Text {
                    text: "Service's ID: " + service.id
                    font.pixelSize: 16
                    font.weight: 40
                }

                Text {
                    text: "Service name: " + service.serviceName
                    font.pixelSize: 16
                    font.weight: 40
                }

                Text {
                    visible: service.serviceName == "Hire computer"
                    font.pixelSize: 16
                    font.weight: 40
                    Component.onCompleted: {
                        if (visible) {
                            text = Qt.binding(function() {
                                return "Computer's ID: " + service.computer.id
                            })
                        }
                    }
                }

                Text {
                    visible: service.serviceName == "Hire computer"
                    font.pixelSize: 16
                    font.weight: 40
                    Component.onCompleted: {
                        if (visible) {
                            text = "Time used: " + root.formatTimeFromSeconds(service.timeUsed);
                        }
                    }
                }

                Text {
                    visible: service.serviceName == "Order food"
                    font.pixelSize: 16
                    font.weight: 40
                    Component.onCompleted: {
                        if (visible) {
                            text = Qt.binding( function () {
                                return "Food's name: " + service.food.name
                            })
                        }
                    }
                }

                Text {
                    visible: service.serviceName == "Order food"
                    font.pixelSize: 16
                    font.weight: 40
                    Component.onCompleted: {
                        if (visible) {
                            text = Qt.binding( function () {
                                return "Number Ordered: " + service.numberOrdered
                            })
                        }
                    }
                }

                Text {
                    text: "Charge: " + service.totalCost
                    font.pixelSize: 16
                    font.weight: 40
                }
            }
        }

        Text {
            Layout.leftMargin: 32
            text: "Total charge: " + totalCharge
            font.pixelSize: 16
            font.weight: 40
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
                text: "Pay"
                enabled: model.status == 0
                opacity: enabled ? 1.0 : 0.5
                onTriggered: {
                    model.status = 1
                    model.paidTime = 1
                    SystemManager.payReceipt(index);
                }
            }
            MenuItem {
                text: "Delete"
                onTriggered: {
                    SystemManager.receiptModel.remove(index)
                }
            }
        }
    }
}
