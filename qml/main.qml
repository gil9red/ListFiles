import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: mainWindow

    width: 600
    height: 480

    title: app.applicationName + qsTr(" author Ilya Petrash") + " v" + app.applicationVersion
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
            font.pixelSize: 36
            Behavior on x { NumberAnimation{ easing.type: Easing.OutCubic} }
            x: 20
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            text: app.applicationName
        }
    }

    Item {
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent

            RowLayout {
                anchors.fill: parent

                ScrollView {
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

                        onCurrentIndexChanged: {
                            var hasCurrentIndex = currentIndex !== -1
                            editButton.enabled = hasCurrentIndex
                            runButton.enabled = hasCurrentIndex
                        }
                        onCountChanged: {
                            var isEmpty = count === 0
                            removeButton.enabled = !isEmpty
                        }
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

                        Rectangle {
                            id : rectItem
                            anchors.fill: parent
                            color: "#11ffffff"
                            visible: mouse.pressed
                        }

                        Row {
                            Image {
                                id : icon
                                fillMode: Image.PreserveAspectFit
                                smooth: true
                                source: "image://fileicon/" + idicon
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.leftMargin: 10
                            }
                            Column {
                                Text {
                                    id: nameFileItem
                                    x: 10
                                    color: "white"
                                    font.pixelSize: 20
                                    text: name
                                    elide : Text.ElideRight
                                    width: rectItem.width - x - icon.width
                                }

                                Text {
                                    id: pathFileItem
                                    x: 15
                                    color: "white"
                                    font.pixelSize: 12
                                    text: path
                                    elide : Text.ElideRight
                                    width: rectItem.width - x - icon.width
                                }
                            }
                        }

                        MouseArea {
                            id: mouse
                            anchors.fill: parent
                            onClicked: fileView.currentIndex = index;
                            onDoubleClicked: fileListManager.run(fileView.currentIndex)
                        }
                    }
                }

                Item {
                    id : panelButtons
                    width: 80
                    Layout.alignment: Qt.AlignTop

                    ColumnLayout {
                        anchors.fill: parent

                        Button {
                            text: qsTr("Add")
                            id: addButton
                            style: touchStyle
                            Layout.fillWidth: true
                            onClicked: fileDialogAddedFiles.open()

                            FileDialog {
                                id: fileDialogAddedFiles
                                folder: "."
                                title: qsTr("Choose a file to open")
                                selectMultiple: true
                                nameFilters: [ qsTr("All files (*.*)") ]

                                onAccepted: {
                                    fileListManager.addFileFromUrls(fileUrls)

                                    fileView.currentIndex = fileListManager.countFiles() - 1
                                    fileDialogAddedFiles.close()
                                }

                                onRejected: fileDialogAddedFiles.close()
                            }
                        }

                        Button {
                            text: qsTr("Remove")
                            id: removeButton
                            style: touchStyle
                            Layout.fillWidth: true
                            onClicked: {
                                if (fileView.currentIndex !== -1)
                                    fileListManager.removeFile(fileView.currentIndex);
                            }
                        }

                        Button {
                            text: qsTr("Edit")
                            id: editButton
                            style: touchStyle
                            Layout.fillWidth: true
                            onClicked: {
                                if (fileView.currentIndex !== -1)
                                    fileListManager.edit(fileView.currentIndex);
                            }
                        }

                        Button {
                            text: qsTr("Run")
                            id: runButton
                            style: touchStyle
                            implicitWidth: parent.width
                            onClicked: {
                                if (fileView.currentIndex !== -1)
                                    fileListManager.run(fileView.currentIndex)
                            }
                        }

                        Button {
                            text: qsTr("About")
                            id: aboutButton
                            style: touchStyle
                            Layout.fillWidth: true
                            onClicked: fileListManager.about()
                        }

                        Button {
                            text: qsTr("Quit")
                            id: quitButton
                            style: touchStyle
                            Layout.fillWidth: true
                            onClicked: fileListManager.quit()
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
                                        color: enabled === true ? "white" : "gray"
                                        font.pixelSize: 14
                                        renderType: Text.NativeRendering
                                    }
                                }
                            }
                        }
                    }
                }
            }

            TextField {
                id : search
                placeholderText: qsTr("Search...")
                onTextChanged: fileListManager.searchItems(text)

                Layout.fillWidth: true

                style: TextFieldStyle {
                    background: Rectangle {
                        color: "white"
                        border.color: "transparent"
                        radius: height / 2
                        Rectangle {
                            anchors.fill: parent
                            anchors.margins: 1
                            color: "transparent"
                            antialiasing: true
                            border.color: "transparent"
                            radius: height / 2
                        }
                    }
                }
            }
        }
    }
}
