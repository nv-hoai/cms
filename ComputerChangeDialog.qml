import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Model 1.0
import prototype 1.0

Dialog {
    id: root
    width: 300
    height: 300
    anchors.centerIn: parent
    modal: true
    closePolicy: Popup.NoAutoClose

    property int id;
    property string cpu;
    property int ram;
    property int position;
    property int status;
    property int cost;

    header: Text {
        text: "Computer's information"
        font.pixelSize: 12
        font.weight: 40
    }

    onOpened: {
        cpuInput.text = cpu;
        ramInput.currentIndex = ramInput.indexOfValue(root.ram)
        positionInput.value = root.position
        statusInput.currentIndex = statusInput.indexOfValue(root.status)
        costInput.text = cost
    }

    onAccepted: {
        root.cpu = cpuInput.text
        root.ram = ramInput.currentValue
        root.position = positionInput.value
        root.status = statusInput.currentValue
        root.cost = parseInt(costInput.text)
        updateComputerData(selectedItemIndex, root.cpu, root.ram, root.position, root.status, root.cost);
    }

    function isSaveAllowed() {
        return !(invalidCpu.visible || invalidPosition.visible || invalidCost.visible)
    }

    ColumnLayout {
        anchors.fill: parent

        Text {
            text: "ID: "+root.id
            font.pixelSize: 16
            font.weight: 40
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "CPU"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: cpuInput
                text: root.cpu
                placeholderText: "Intel/AMD XXXX"
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidCpu
            text: "Cpu can't be left empty!"
            font.pixelSize: 16
            font.weight: 40
            visible: (cpuInput.text == "")
            color: "red"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "RAM"
                font.pixelSize: 16
                font.weight: 40
            }

            ComboBox {
                id: ramInput
                textRole: "text"
                valueRole: "value"
                editable: true
                model: [
                    { value: 2, text: "2" },
                    { value: 4, text: "4" },
                    { value: 8, text: "8" },
                    { value: 16, text: "16" },
                    { value: 32, text: "32" },
                    { value: 64, text: "64" },
                    { value: 128, text: "128" }
                ]
            }
        }


        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Position"
                font.pixelSize: 16
                font.weight: 40
            }

            SpinBox {
                id: positionInput
                editable: true
                from: 1
                to: 100
            }
        }

        Text {
            id: invalidPosition
            text: "The position has already occupied!"
            font.pixelSize: 16
            font.weight: 40
            visible: ((root.position != positionInput.value)
                      && SystemManager.computerModel.posIsOccupied(positionInput.value))
            color: "red"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Status"
                font.pixelSize: 16
                font.weight: 40
            }

            ComboBox {
                id: statusInput
                textRole: "text"
                valueRole: "value"
                model: [
                    { value: 0, text: "Idle" },
                    { value: 3, text: "Cracked" }
                ]
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Cost"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: costInput
                text: root.cost
                inputMask: "99"
                placeholderText: "20"
                Layout.preferredWidth: statusInput.width
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidCost
            visible: (costInput.text == "")
            text: "Cost can't be left empty!"
            font.pixelSize: 16
            font.weight: 40
            color: "red"
        }
    }

    footer: DialogButtonBox {
        Button {
            text: "Save"
            enabled: root.isSaveAllowed()
            onClicked: root.accept()
            implicitHeight: 32
            implicitWidth: 64
        }
        Button {
            text: "Cancel"
            onClicked: root.reject()
            implicitHeight: 32
            implicitWidth: 64
        }
    }
}
