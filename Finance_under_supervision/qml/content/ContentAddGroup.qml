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

    property var imageModel: []

    signal clickedSave(string title, string icon, string description)

    AppFlickable {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: btSave.top

        contentHeight: contentColumn.implicitHeight
        bottomMargin: nativeUtils.safeAreaInsets.bottom

        Column {
            id: contentColumn

            anchors.fill: parent

            AppText {
                width: parent.width
                text: "Иконка:"
            }

            ComboBox {
                id: comIcon
                height: dp(150)
                width: parent.width
                model: imageModel
                property var currentIcon: ""

                onCurrentIndexChanged: {
                    content.text = model[currentIndex].text
                    content.setImage(model[currentIndex].icon)
                    popup.close()
                }

                contentItem: AppListItem {
                    id: content

                    property var title: ""
                    property var icon: ""

                    function setImage(img) {
                        contentImage.source = img
                        comIcon.currentIcon = img
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

                    text: modelData.text

                    leftItem: AppImage {
                        height: parent.height / 4 * 3
                        width: height
                        source: modelData.icon
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    mouseArea.onClicked: comIcon.currentIndex = index
                }
            }

            AppText {
                width: parent.width
                text: "Название:"
            }

            AppTextField {
                id: titleField
                width: parent.width
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
                        id: descriptionEdit
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
            console.log(titleField.text)
            console.log(comIcon.currentIcon)
            console.log(descriptionEdit.text)
            clickedSave(titleField.text, comIcon.currentIcon, descriptionEdit.text)
        }
    }
}
