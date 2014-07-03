import QtQuick 2.0
import "shared" as Examples

import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.XmlListModel 2.0

ApplicationWindow {
    id: mainWindow
    width: 600
    height: 480

    title: "ListExe author Ilya Petrash"
    visible: true

    RowLayout {
        anchors.fill: parent

        Rectangle {
            border.color: "black"
            Layout.fillWidth: true
            Layout.fillHeight: true

            Component {
                id: contactDelegate
                Item {
                    width: grid.cellWidth; height: grid.cellHeight
                    Column {
                        anchors.fill: parent
                        Image { source: portrait; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { text: name; anchors.horizontalCenter: parent.horizontalCenter }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: parent.GridView.view.currentIndex = index
                    }
                }
            }

            GridView {
                id: grid
                anchors.fill: parent
                cellWidth: 80; cellHeight: 80

                model: contactModel
                delegate: contactDelegate
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                focus: true
            }

            ListModel {
                id: contactModel

                ListElement {
                    name: "Jim Williams"
                    portrait: "pics/portrait.png"
                }
                ListElement {
                    name: "John Brown"
                    portrait: "pics/portrait.png"
                }
                ListElement {
                    name: "Bill Smyth"
                    portrait: "pics/portrait.png"
                }
                ListElement {
                    name: "Sam Wise"
                    portrait: "pics/portrait.png"
                }
            }
        }

        Item {
            width: 70
            Layout.alignment: Qt.AlignTop

            ColumnLayout {
                anchors.fill: parent

                Button {
                    text: qsTr("Add")
                    id: add
                    style: buttonStyle
                    Layout.fillWidth: true
                    onClicked: contactModel.append({name: "Man"});
                }

                Button {
                    text: qsTr("Remove")
                    id: remove
                    style: buttonStyle
                    Layout.fillWidth: true
                    onClicked: contactModel.remove(grid.currentIndex)
                }

                Button {
                    text: qsTr("Edit")
                    id: edit
                    style: buttonStyle
                    Layout.fillWidth: true
                }

                Button {
                    text: qsTr("Run")
                    id: run
                    style: buttonStyle
                    implicitWidth: parent.width
                    onClicked: text = app.platformName
                }

                Button {
                    text: qsTr("About Qt")
                    id: about
                    style: buttonStyle
                    Layout.fillWidth: true
                    onClicked: foo.say()
                }

                Button {
                    text: qsTr("Quit")
                    id: quit
                    style: buttonStyle
                    Layout.fillWidth: true

                    onClicked: mainWindow.close()
                }
            }
        }
    }

    property Component buttonStyle: ButtonStyle {
        background: Rectangle {
            implicitHeight: 22
            implicitWidth: parent.width
            color: control.pressed ? "darkGray" : control.activeFocus ? "#cdd" : "#ccc"
            antialiasing: true
            border.color: "gray"
            radius: height/2
            Rectangle {
                anchors.fill: parent
                anchors.margins: 1
                color: "transparent"
                antialiasing: true
                visible: !control.pressed
                border.color: "#aaffffff"
                radius: height/2
            }
        }
    }
}
