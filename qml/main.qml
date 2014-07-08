import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Dialogs 1.1

ApplicationWindow {
    id: mainWindow

    width: 600
    height: 480

    title: app.applicationName + " author Ilya Petrash" + " v" + app.applicationVersion
    visible: true

    Rectangle {
        color: "#212126"
        anchors.fill: parent
    }

    toolBar: BorderImage {
        border.bottom: 8
        source: "../qml/images/toolbar.png"
        width: parent.width
        height: labelHeader.font.pixelSize + labelHeader.font.pixelSize / 2

        Text {
            id : labelHeader
            font.pixelSize: 40
            Behavior on x { NumberAnimation{ easing.type: Easing.OutCubic} }
            x: 20
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            text: app.applicationName + " v" + app.applicationVersion
        }
    }

    RowLayout {
        anchors.fill: parent

        StackView {
            id: stackView

            Layout.fillWidth: true
            Layout.fillHeight: true

            // Implements back key navigation
            focus: true

            initialItem: ScrollView {
                id : scrollView

                Layout.fillWidth: true
                Layout.fillHeight: true

                width: parent.width
                height: parent.height

                flickableItem.interactive: true

                ListView {
                    spacing: 5 // Расстояние между элементами
                    id : fileView
                    anchors.fill: parent
                    delegate: fileDelegate
                    model: fileListModel
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
                id: fileDelegate
                Item {
                    id : root
                    width: parent.width - 20 // примерная ширина вертикального скрола
                    height: 40

                    property alias nameFile: nameFileItem.text // текущее имя файла
                    property alias pathFile: pathFileItem.text // текущий путь к файлу
                    signal clicked

                    Rectangle {
                        anchors.fill: parent
                        color: "#11ffffff"
                        visible: mouse.pressed
                    }

//                    Row {
                    Column {
                        x: 10 // Отступ слева
                        Text {
                            id: nameFileItem
                            color: "white"
                            font.pixelSize: 20
                            text: name
                            elide : Text.ElideRight;
                            width: root.width - run.width
                        }

                        Text {
                            id: pathFileItem
                            x: 10 // Отступ слева
                            color: "white"
                            font.pixelSize: 12
                            text: path
                            elide : Text.ElideRight;
                            width: root.width - run.width
                        }
                    }

//                    Button {
//                        text: "Run"
//                        width: 30
//                        id : run
//                        style: touchStyle
//                        anchors.right: parent.anchors
//                        anchors.centerIn: parent.anchors
//                    }
//                    }

                    //                    Rectangle {
                    //                        anchors.left: parent.left
                    //                        anchors.right: parent.right
                    //                        anchors.margins: 15
                    //                        height: 1
                    //                        color: "#424246"
                    //                    }

                    //                    Image {
                    //                        anchors.right: parent.right
                    //                        anchors.rightMargin: 20
                    //                        anchors.verticalCenter: parent.verticalCenter
                    //                        source: "image://fileicon/" + idicon
                    //                    }

                    MouseArea {
                        id: mouse
                        anchors.fill: parent
                        onClicked: {
                            root.clicked()
                            fileView.currentIndex = index
                            console.log("About click on: " + root.nameFile)
                        }
                    }
                }
            }
        }

        Item {
            width: 80
            Layout.alignment: Qt.AlignTop

            ColumnLayout {
                anchors.fill: parent

                Button {
                    text: qsTr("Add")
                    id: add
                    style: touchStyle
                    Layout.fillWidth: true
                    onClicked: fileListModel.addfile("<path_to_exe>")
                }

                Button {
                    text: qsTr("Remove")
                    id: remove
                    style: touchStyle
                    Layout.fillWidth: true
                    onClicked: fileListModel.removefile(fileView.currentIndex)
                }

                Button {
                    text: qsTr("Edit")
                    style: touchStyle
                    Layout.fillWidth: true
                    onClicked: { stackView.push(Qt.resolvedUrl("content/edit.qml")) }
                }

                Button {
                    text: qsTr("Run")
                    id: run
                    style: touchStyle
                    implicitWidth: parent.width
                    onClicked: text = app.platformName
                }

                Button {
                    text: qsTr("About")
                    style: touchStyle
                    Layout.fillWidth: true
                    onClicked: { stackView.push(Qt.resolvedUrl("content/about.qml")) }
                }

                Button {
                    text: qsTr("Quit")
                    style: touchStyle
                    Layout.fillWidth: true
                    onClicked: mainWindow.close()
                }
            }

            Component {
                id: touchStyle
                ButtonStyle {
                    panel: Item {
                        implicitHeight: 30
                        implicitWidth: 80
                        BorderImage {
                            anchors.fill: parent
                            antialiasing: true
                            border.bottom: 8
                            border.top: 8
                            border.left: 8
                            border.right: 8
                            anchors.margins: control.pressed ? -4 : 0
                            source: control.pressed ? "../qml/images/button_pressed.png" : "../qml/images/button_default.png"
                            Text {
                                text: control.text
                                anchors.centerIn: parent
                                color: "white"
                                font.pixelSize: 14
                                renderType: Text.NativeRendering
                            }
                        }
                    }
                }
            }
        }
    }
}
