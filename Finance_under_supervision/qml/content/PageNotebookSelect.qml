import QtQuick 2.0
import Felgo 3.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Item {
    id: root

    property var model: 0

    signal clickedAdd()
    signal clickedOpen(var idNotebook)

    Item {
        width: parent.width / 5 * 4
        height: parent.height / 5 * 4

        anchors.centerIn: parent

        ColumnLayout {
            anchors.fill: parent
            spacing: 0
            anchors.margins: 0

            Rectangle {
                height: parent.height / 10
                Layout.minimumHeight: dp(50)
                Layout.fillWidth: true

                border.width: dp(3)
                color: Theme.colors.tintColor

                AppText {
                    text: "Выберите книжку:"
                    font.bold: true
                    color: Theme.colors.backgroundColor

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    anchors.fill: parent


                }
            }

            ListView {
                id: listNotebook
                clip: true
                model: root.model
                delegate: AppListItem {
                    text: _title

                    mouseArea.onClicked: clickedOpen(_id)
                    mouseArea.onPressAndHold: nativeUtils.displayAlertSheet("Вы действительно хотите удалить дневник?", ["Да", "Нет"], false)

                    Connections {
                            target: nativeUtils
                            onAlertSheetFinished: function (answer) {
                              if(answer == 0)
                                  core.removeNotebook(index+1)
                            }
                          }
                }

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.leftMargin: dp(5)
            }

            Rectangle {
                height: dp(3)

                color: "black"

                Layout.fillWidth: true
                Layout.minimumHeight: dp(3)
            }

            AppButton {
                height: parent.height / 10
                Layout.minimumHeight: dp(50)
                minimumHeight: dp(50)
                Layout.fillWidth: true

                text: "Добавить"

                verticalMargin: dp(0)
                horizontalMargin: dp(0)
                verticalPadding: dp(0)
                horizontalPadding: dp(0)

                onClicked: clickedAdd()

            }
        }

        Rectangle {
            id: mask
            color: "#00000000"
            radius: dp(50)

            border.width: dp(3)

            anchors.fill: parent
        }

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Rectangle {
                height: mask.height
                width: mask.width
                radius: mask.radius
            }
        }
    }
}
