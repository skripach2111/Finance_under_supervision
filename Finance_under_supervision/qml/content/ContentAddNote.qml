import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtGraphicalEffects 1.0
import QtQml.Models 2.12

Item {
    id: root

    height: 800
    width: 300

    property var groupModel
    property var labelModel: ListModel {}
    property var currentGroup

    Component.onCompleted: labelModel.clear()

    signal showLabelSelector()
    signal noteAdd()

    Column {
        anchors.fill: parent

        AppFlickable {
            height: parent.height
            width: parent.width

            contentHeight: clContent.implicitHeight

            Column {
                id: clContent

                anchors.fill: parent

                AppText {
                    width: parent.width

                    text: "Название:"
                }

                AppTextField {
                    id: noteTitle
                    width: parent.width
                }

                AppText {
                    width: parent.width

                    text: "Сумма:"
                }

                AppTextField {
                    id: noteSum
                    width: parent.width
                }

                AppText {
                    width: parent.width

                    text: "Категория:"
                }

                ComboBox {
                    id: comIcon
                    height: dp(150)
                    width: parent.width
                    model: core.groupModel

                    onCurrentIndexChanged: {
//                        content.text = model.get(currentIndex)._title
//                        content.setImage(model.get(currentIndex)._icon)
                        popup.close()
                    }

                    contentItem: AppListItem {
                        id: content

                        property var title: ""
                        property var icon: ""

                        function setImage(img) {
                            contentImage.source = img
                        }

                        anchors.fill: parent

                        text: title

                        leftItem: AppImage {
                            id: contentImage
                            height: parent.height / 4 * 3
                            width: height
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        mouseArea.onClicked: parent.popup.open()
                    }

                    delegate: AppListItem {
                        height: dp(100)

                        text: _title

                        leftItem: AppImage {
                            height: parent.height / 4 * 3
                            width: height
                            source: _icon
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        mouseArea.onClicked: {
                            content.title = _title
                            content.image = _icon
                            content.setImage(_icon)
                            comIcon.currentIndex = index
                            currentGroup = _id
                            console.log(currentGroup)
                        }
                    }
                }

                AppText {
                    width: parent.width

                    text: "Метки:"
                }

                Item {
                    height: gridLabels.contentHeight + dp(5)
                    width: parent.width

                    GridView {
                        id: gridLabels
                        anchors.fill: parent
                        anchors.margins: dp(5)

                        property var cHeight: dp(20)
                        property var cWidth: dp(76)

                        cellHeight: cHeight
                        cellWidth: cWidth

                        model: labelModel

                        delegate: AppPaper {
                            height: dp(16)
                            width: dp(72)

                            background.color: _color//Theme.colors.tintLightColor

                            radius: 10

                            AppText {
                                anchors.centerIn: parent

                                text: _title
                                //color: _color
                            }

                            MouseArea {
                                anchors.fill: parent

                                onClicked: {
                                    labelModel.remove(index)
                                }
                            }
                        }
                    }
                }

                AppButton {
                    width: parent.width

                    text: "Добавить"

                    onClicked: showLabelSelector()
                }

                AppText {
                    width: parent.width

                    text: "Описание:"
                }

                Item {
                    height: contentTextEdit.implicitHeight
                    width: parent.width

                    Column {
                        id: contentTextEdit
                        anchors.fill: parent

                        AppTextEdit {
                            id: noteDesctiption
                            height: contentHeight > dp(150) ? contentHeight : dp(150)
                            width: parent.width

                        }

                        Rectangle {
                            height: dp(1)
                            width: parent.width
                            color: "black"
                        }
                    }
                }
            }
        }

        AppButton {
            id: btSave
            text: "Сохранить"

            minimumHeight: dp(50)

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            verticalMargin: dp(0)
            horizontalMargin: dp(0)
            verticalPadding: dp(0)
            horizontalPadding: dp(0)

            onClicked: {
                var listId = []
                for(var i = 0; i < labelModel.count; i++)
                    listId.push(labelModel.get(i)._id);

                core.addNote(currentGroup, noteTitle.text, noteDesctiption.text, noteSum.text, listId)
                noteAdd()
                app.updateAll()
            }
        }
    }
}
