import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root
    property alias pagePadding: root.padding
    property alias headerText: headerText.text
    property alias headerDetails: headerDetails.text
    property alias gridModel: mainContent.model
    property alias gridDelegate: mainContent.delegate
    property alias gridCellHeight: mainContent.cellHeight
    property alias gridCellWidth: mainContent.cellWidth
    property alias gridX: mainContent.x
    property alias gridY: mainContent.y
    property alias newMouseArea: newButton.mouseArea
    property alias saveMouseArea: saveButton.mouseArea
    property alias searchBar: searchBar

    ColumnLayout {
        anchors.fill: parent

        Text {
            id: headerText
            font.pixelSize: 32
            font.weight: 40
        }

        Text {
            id: headerDetails
            font.pixelSize: 16
            font.weight: 40
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            color: "white"
            radius: 4
            RowLayout {
                anchors.fill: parent
                TextButton {
                    id: newButton
                    Layout.leftMargin: 8
                    implicitHeight: 40
                    implicitWidth: 40
                    buttonRadius: 4
                    textSize: 32
                    text: "+"
                    mouseArea.onEntered: {
                        newTooltip.visible = true
                    }
                    mouseArea.onExited: {
                        newTooltip.visible = false
                    }
                }

                ImageButton {
                    id: saveButton
                    implicitHeight: 40
                    implicitWidth: 40
                    buttonRadius: 4
                    sourceImage: "/image/save-floppy-svgrepo-com.svg"
                    mouseArea.onEntered: {
                        saveTooltip.visible = true
                    }
                    mouseArea.onExited: {
                        saveTooltip.visible = false
                    }
                }

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                TextField {
                    id: searchBar
                    Layout.rightMargin: 8
                    placeholderText: "Search"
                    background: Rectangle {
                        color: "white"
                        radius: 4
                        border.color: "gray"
                        border.width: 1
                        implicitWidth: 200
                        implicitHeight: searchBar.height
                    }

                    padding: 8
                    font.pixelSize: 16
                    font.weight: 40
                    verticalAlignment: Text.AlignVCenter
                }
            }

            // Tooltip for Text Button
            Rectangle {
                id: newTooltip
                x: newButton.x+newButton.width+8
                y: newButton.y
                color: "lightgray"
                radius: 6
                visible: false
                z: 1 // Tooltip appears above

                Text {
                    text: "Add new"
                    font.pixelSize: 12
                    color: "black"
                    anchors.centerIn: parent
                }

                // Using implicitWidth and implicitHeight
                implicitWidth: 120
                implicitHeight: 40 // Optional padding
            }

            // Tooltip for Image Button
            Rectangle {
                id: saveTooltip
                x: saveButton.x+saveButton.width+8
                y: saveButton.y
                color: "lightgray"
                radius: 6
                visible: false
                z: 1 // Tooltip appears above

                Text {
                    text: "Save changes"
                    font.pixelSize: 12
                    color: "black"
                    anchors.centerIn: parent
                }

                // Using implicitWidth and implicitHeight
                implicitWidth: 120
                implicitHeight: 40
            }
        }

        GridView {
            id: mainContent
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
        }
    }
}
