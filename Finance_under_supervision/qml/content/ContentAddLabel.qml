import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.0
import Felgo 3.0

Item {
    id: root

    height: 800
    width: 300

    signal clickedSave(string title, string color)

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
                text: "Название"
            }

            AppTextField {
                id: titleLabel
                width: parent.width
            }

            AppText {
                width: parent.width
                text: "Цвет"
            }

            Row {
                width: parent.width
                height: dp(55)

                Rectangle {
                    id: colorView

                    height: dp(50)
                    width: height

                    border.width: dp(1)
                }

                AppButton {
                    text: "Выбрать"

                    anchors.left: colorView.right
                    anchors.right: parent.right

                    anchors.verticalCenter: colorView.verticalCenter

                    onClicked: colorDialog.open()
                }
            }
            AppText {
                id: colorText
                width: parent.width
                text: colorView.color
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
            console.log(colorView.color)
            clickedSave(titleLabel.text, colorView.color)
        }
    }

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        onAccepted: {
            colorView.color = colorDialog.color
            close()
        }
        onRejected: {
            console.log("Canceled")
            close()
        }
    }
}
