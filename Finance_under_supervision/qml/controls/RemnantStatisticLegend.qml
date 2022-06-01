import Felgo 3.0
import QtQuick 2.8

Item {
    id: root
    height: 800
    width:350

    property real totalValue: 1
    property real value: 0
    property var backgroundColor: Theme.colors.tintLightColor
    property var textColor: Theme.secondaryBackgroundColor
    property var fontSize: dp(12)

    AppPaper {
        height: columnLegend.implicitHeight
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter

        background.color: root.backgroundColor

        Column {
            id: columnLegend
            anchors.fill: parent

            AppText {
                width: parent.width
                fontSize: root.fontSize
                color: root.textColor
                text: "Потрачено: " + runStatisticsChart.value
            }

            AppText {
                width: parent.width
                fontSize: root.fontSize
                color: root.textColor
                text: "Заработано: " + runStatisticsChart.totalValue
            }

            AppText {
                width: parent.width
                fontSize: root.fontSize
                color: root.textColor
                text: "Остаток: " + (runStatisticsChart.totalValue + runStatisticsChart.value)
            }
        }
    }
}
