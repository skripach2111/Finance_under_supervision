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
            pieSeries.append(groups[i] + " " + plus[i], Math.abs(plus[i]))
    }

    property var plus:  [2450, 1440, 3035, 1456]
    property var groups:  ["Label_1", "Label_2", "Label_3", "Label_4"]

    ChartView {
        //title: "Total sum:" + pieSeries.sum
        anchors.fill: parent
        antialiasing: true
        legend.alignment: Qt.AlignBottom
        legend.minimumSize: width

        PieSeries {
            id: pieSeries
        }
    }
}
