import QtQuick 2.8
import QtQuick.Layouts 1.12
import Felgo 3.0
import QtQml.Models 2.12

Page {
    id: root

    height: 800
    width: 300

    signal clickedByNotes()
    signal clickedByGroups()
    signal clickedByLabels()

    AppFlickable {
        height: parent.height
        width:  parent.width

        contentHeight: contentColumn.implicitHeight > height ? contentColumn.implicitHeight : height

        Column {
            id: contentColumn

            height: parent.height
            width:  parent.width

            AppListItem {
                width: parent.width

                text: "по записям"

                mouseArea.onClicked: clickedByNotes()
            }

            AppListItem {
                width: parent.width

                text: "по категориям"

                mouseArea.onClicked: clickedByGroups()
            }

            AppListItem {
                width: parent.width

                text: "по меткам"

                mouseArea.onClicked: clickedByLabels()
            }
        }
    }
}
