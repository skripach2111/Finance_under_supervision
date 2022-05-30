import Felgo 3.0
import QtQuick 2.8
import QtCharts 2.3


Item {
    id: root

    property real totalValue: 1
    property real value: 0
    property string activity: "Остаток:"
    property var backgroundColor: Theme.colors.tintLightColor
    property var textColor: Theme.secondaryBackgroundColor

    Column {
        anchors.fill: parent

            ChartView {
                id: chart
                anchors.fill: parent
                legend.alignment: Qt.AlignBottom
                legend.visible: false
                margins {
                    top: 0
                    bottom: 0
                    left: 0
                    right: 0
                }

                antialiasing: true

                backgroundColor: Theme.colors.tintLightColor

                PieSeries {
                    id: pieSeries
                    holeSize: 0.8
                    size: 0.9
                    startAngle: 20
                    endAngle: 380


                    PieSlice {
                        value: root.totalValue - root.value
                        color: Theme.tintColor

                        Behavior on value {
                            NumberAnimation {
                                duration: 1000
                            }
                        }
                    }

                    PieSlice {
                        value: root.value
                        color: Theme.secondaryBackgroundColor
                    }
                }
            }

            Column {
                anchors.centerIn: parent

                AppText {
                    anchors.horizontalCenter: parent.horizontalCenter

                    font.pixelSize: dp(16)
                    font.bold: true
                    color: Theme.backgroundColor
                    text: activity
                }

                AppText {
                    anchors.horizontalCenter: parent.horizontalCenter

                    font.pixelSize: dp(16)
                    font.bold: true
                    color: Theme.backgroundColor
                    text: totalValue
                }
            }
    }
}
