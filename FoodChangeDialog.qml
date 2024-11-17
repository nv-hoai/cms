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
    property string name;
    property int remain;
    property int cost;
    property string imageSource;

    header: Text {
        text: "Food's information"
        font.pixelSize: 12
        font.weight: 40
    }

    onOpened: {
        nameInput.text = name;
        remainInput.text = remain;
        costInput.text = cost;
        imageInput.text = imageSource
    }

    onAccepted: {
        name = nameInput.text
        remain = parseInt(remainInput.text)
        cost = parseInt(costInput.text)
        imageSource = imageInput.text
        updateFoodData(selectedItemIndex, name, remain, cost, imageSource);
    }

    function isSaveAllowed() {
        return !(invalidName.visible || invalidRemain.visible || invalidCost.visible)
    }

    ColumnLayout {
        anchors.fill: parent

        Text {
            text: "ID: "+ root.id
            font.pixelSize: 16
            font.weight: 40
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Name"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: nameInput
                text: root.name
                placeholderText: "Chicken"
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidName
            visible: (nameInput.text == "")
            text: "Name can't be left empty!"
            font.pixelSize: 16
            font.weight: 40
            color: "red"

        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Remain"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: remainInput
                text: root.remain
                inputMask: "9999"
                placeholderText: "XXXX"
                Layout.preferredWidth: root.width/4
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidRemain
            visible: remainInput.text == ""
            text: "Remain can't be left empty!"
            font.pixelSize: 16
            font.weight: 40
            color: "red"
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
                placeholderText: "XX"
                Layout.preferredWidth: root.width/4
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

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Image path"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: imageInput
                text: root.imageSource
                placeholderText: ".../path to the image/..."
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }
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
