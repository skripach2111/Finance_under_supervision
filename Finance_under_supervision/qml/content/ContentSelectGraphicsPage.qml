import Felgo 3.0
import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQml 2.12

Item {
    height: 800
    width: 300

    signal clickedContinue()

    ColumnLayout {
        anchors.fill: parent

        AppFlickable {
            Layout.fillWidth: true
            Layout.fillHeight: true

            contentHeight: contentColumn.implicitHeight > height ? contentColumn.implicitHeight : height

            Column {
                id: contentColumn

                anchors.fill: parent
                anchors.margins: dp(5)

                AppText {
                    width: parent.width

                    text: "Начальная дата:"
                }

                RowLayout {


                    width: parent.width

                    AppText {
                        property var dateBegin: new Date()

                        height: parent.height

                        text: dateBegin.toLocaleDateString("dd-mm-yyyy")

                        Layout.fillWidth: true
                    }

                    AppButton {
                        height: parent.height

                        text: "Выбрать"
                    }
                }

                AppText {
                    width: parent.width

                    text: "Конечная дата:"
                }

                RowLayout {
                    width: parent.width

                    AppText {
                        id: end
                        property var dateEnd: new Date()

                        height: parent.height

                        text: dateEnd.toLocaleDateString("dd-mm-yyyy")

                        Layout.fillWidth: true
                    }

                    AppButton {
                        height: parent.height

                        text: "Выбрать"

                        onClicked: end.dateEnd =  nativeUtils.displayDatePicker("Pick your favorite date!")
                    }
                }
            }
        }

        AppButton {
            Layout.fillWidth: true

            text: "Продолжить"

            verticalMargin: dp(0)
            horizontalMargin: dp(0)
            verticalPadding: dp(0)
            horizontalPadding: dp(0)

            onClicked: {
                clickedContinue()
            }
        }
    }
}
