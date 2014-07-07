import QtQuick 2.0
import "shared"
import "content"

import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.XmlListModel 2.0
import QtQuick.Dialogs 1.1

ApplicationWindow {
    id: mainWindow

    width: 600
    height: 480

    title: "ListExe author Ilya Petrash"
    visible: true
    Rectangle {
        color: "#212126"
        anchors.fill: parent
    }

    RowLayout {
        anchors.fill: parent

        //        Rectangle {
        //            border.color: "black"
        //            Layout.fillWidth: true
        //            Layout.fillHeight: true

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            width: parent.width
            height: parent.height

            flickableItem.interactive: true

            ListView {
                id : programView
                anchors.fill: parent
                delegate: programDelegate
                model: programListModel
                highlight: Rectangle { color: "#22ffffff"; }
            }

            style: ScrollViewStyle {
                transientScrollBars: true
                handle: Item {
                    implicitWidth: 14
                    implicitHeight: 26
                    Rectangle {
                        color: "#424246"
                        anchors.fill: parent
                        anchors.topMargin: 6
                        anchors.leftMargin: 4
                        anchors.rightMargin: 4
                        anchors.bottomMargin: 6
                    }
                }
                scrollBarBackground: Item {
                    implicitWidth: 14
                    implicitHeight: 26
                }
            }
        }

        Component {
            id: programDelegate
            Item {
                id : root
                width: parent.width
                height: 88

                property alias text: textitem.text // текущий текст
                signal clicked

                Rectangle {
                    anchors.fill: parent
                    color: "#11ffffff"
                    visible: mouse.pressed
                }

                Text {
                    id: textitem
                    color: "white"
                    font.pixelSize: 32
                    text: name
                    elide : Text.ElideRight;
                    width: root.width
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                }

                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 15
                    height: 1
                    color: "#424246"
                }

                Image {
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    source: "image://programicon/" + idicon
                }

                MouseArea {
                    id: mouse
                    anchors.fill: parent
                    onClicked: {
                        root.clicked()
                        programView.currentIndex = index
                    }
                }
            }
        }

        //            Content.ListPage {
        ////                id: grid
        //                anchors.fill: parent
        ////                cellWidth: 80; cellHeight: 80

        ////                model:
        ////                model: programListModel
        ////                delegate: programDelegate
        ////                delegate: Content.AndroidDelegate
        ////                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        ////                focus: true
        //            }

        //            Component {
        //                id: programDelegate
        //                Item {
        //                    width: grid.cellWidth; height: grid.cellHeight

        //                    Column {
        //                        anchors.fill: parent
        //                        Image {
        //                            horizontalAlignment: Image.AlignHCenter
        //                            source: "image://programicon/" + idicon;
        //                            sourceSize.width: grid.cellWidth / 2
        //                            sourceSize.height: grid.cellHeight / 2
        //                        }
        //                        Text { text: name; elide : Text.ElideRight; width: grid.cellWidth; }
        //                        Text { text: path; elide : Text.ElideRight; width: grid.cellWidth; }
        //                        Text { text: args; elide : Text.ElideRight; width: grid.cellWidth; }
        //                    }
        //                    MouseArea {
        //                        anchors.fill: parent
        //                        onClicked: parent.GridView.view.currentIndex = index
        //                    }
        //                }
        //            }
        //        }

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
//                    onClicked: /*FileDialog {
//                        visible: true
////                        modality: Qt.WindowModal
//                        title: "Choose a file"
//                        selectExisting: true
//                        nameFilters: [ "EXE (*.exe *.lnk)" ]
//                        selectedNameFilter: "EXE (*.exe *.lnk)"
//                        onAccepted: programListModel.addProgram(fileUrl);
//                    }*/
////                               FileDialog {
////                        id: fileDialog
////                        title: "Please choose a file"
////                        onAccepted: {
////                            console.log("You chose: " + fileDialog.fileUrls)
////                            programListModel.addProgram(fileDialog.fileUrls);
//////                            Qt.quit()
////                        }
////                        onRejected: {
////                            console.log("Canceled")
//////                            Qt.quit()
////                        }
////                        Component.onCompleted: visible = true
////                    }
                }

                Button {
                    text: qsTr("Remove")
                    id: remove
                    style: buttonStyle
                    Layout.fillWidth: true
                    onClicked: programListModel.removeProgram(programView.currentIndex)
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
