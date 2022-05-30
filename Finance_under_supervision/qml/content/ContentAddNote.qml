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

    property var groupModel: ListModel {}
    property var labelModel: ListModel {}

    AppFlickable {
        anchors.fill: parent

        contentHeight: clContent.implicitHeight

        Column {
            id: clContent

            anchors.fill: parent

            AppText {
                width: parent.width

                text: "Название:"
            }

            AppTextField {
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
                model: groupModel

                onCurrentIndexChanged: {
                    content.text = model.get(currentIndex).title
                    content.setImage(model.get(currentIndex).icon)
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

                    text: title

                    leftItem: AppImage {
                        height: parent.height / 4 * 3
                        width: height
                        source: icon
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    mouseArea.onClicked: comIcon.currentIndex = index
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

                        background.color: Theme.colors.tintLightColor

                        radius: 10

                        AppText {
                            anchors.centerIn: parent

                            text: title
                            color: colored
                        }

                        MouseArea {
                            anchors.fill: parent
                        }
                    }
                }
            }

            AppButton {
                width: parent.width

                text: "Добавить"
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
}
