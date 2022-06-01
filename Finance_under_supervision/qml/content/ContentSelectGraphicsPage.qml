import Felgo 3.0
import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQml 2.12

Item {
    height: 800
    width: 300

    signal clickedContinue(var beginDate, var endDate)

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

                DatePicker {
                    id: startDate
                    width: parent.width

                    datePickerMode: dateMode


                }

                AppText {
                    width: parent.width

                    text: "Конечная дата:"
                }

                DatePicker {
                    id: endDate
                    width: parent.width

                    datePickerMode: dateMode
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
                clickedContinue(startDate.selectedDate, endDate.selectedDate)
            }
        }
    }
}
