import QtQuick 2.8
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtQml.Models 2.12
import QtCharts 2.0

Item {
    height: 800
    width: 300

    Component.onCompleted: count()

    function count() {
        for(var i = 0; i < groups.length; i++)
            pieSeries.append(groups[i], Math.abs(plus[i]))
    }

    property var plus:  [3000, 1000, 2035, 456]
    property var groups:  ["Group_1", "Group_2", "Group_3", "Group_4"]

    ChartView {
        title: "Total sum:" + pieSeries.sum
        anchors.fill: parent
        antialiasing: true
        legend.alignment: Qt.AlignBottom

        PieSeries {
            id: pieSeries
        }
    }
}
