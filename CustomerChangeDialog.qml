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
    property string firstName;
    property string lastName;
    property int age;
    property bool gender;

    header: Text {
        text: "Customer's information"
        font.pixelSize: 12
        font.weight: 40
    }

    onOpened: {
        firstNameInput.text = firstName;
        lastNameInput.text = lastName;
        ageInput.value = age;
        genderInput.currentIndex = genderInput.indexOfValue(gender);
    }

    onAccepted: {
        firstName = firstNameInput.text.substring(0, 30);
        lastName = lastNameInput.text.substring(0, 30);
        age = ageInput.value;
        gender = genderInput.currentValue;
        updateCustomerData(selectedItemIndex, firstName, lastName, age, gender);
    }

    function isSaveAllowed() {
        return !(invalidFirstName.visible || invalidLastName.visible)
    }

    ColumnLayout {
        anchors.fill: parent

        Text {
            text: "Id: "+ root.id
            font.pixelSize: 16
            font.weight: 40
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "First name"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: firstNameInput
                text: root.firstName
                placeholderText: "Hoai"
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidFirstName
            text: "First name can't be left empty!"
            font.pixelSize: 16
            font.weight: 40
            visible: (firstNameInput.text == "")
            color: "red"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Last name"
                font.pixelSize: 16
                font.weight: 40
            }

            TextField {
                id: lastNameInput
                text: root.lastName
                placeholderText: "Nguyen Van"
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: 16
                font.weight: 40
            }
        }

        Text {
            id: invalidLastName
            text: "Last name can't be left empty!"
            font.pixelSize: 16
            font.weight: 40
            visible: (lastNameInput.text == "")
            color: "red"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Age"
                font.pixelSize: 16
                font.weight: 40
            }

            SpinBox {
                id: ageInput
                editable: true
                from: 18
                to: 60
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 24

            Text {
                text: "Gender"
                font.pixelSize: 16
                font.weight: 40
            }

            ComboBox {
                id: genderInput
                textRole: "text"
                valueRole: "value"
                model: [
                    { value: 0, text: "Female" },
                    { value: 1, text: "Male" }
                ]
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
