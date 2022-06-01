import QtQuick 2.0

Item {
    id: models

    property ListModel notebook: ListModel {
        ListElement{n: 0; title: "Notebook 1"; description: "one"}
        ListElement{n: 1; title: "Notebook 2"; description: "two"}
        ListElement{n: 2; title: "Notebook 3"; description: "three"}
        ListElement{n: 3; title: "Notebook 4"; description: "four"}
        ListElement{n: 4; title: "Notebook 5"; description: "five"}
        ListElement{n: 5; title: "Notebook 4"; description: "four"}
        ListElement{n: 6; title: "Notebook 4"; description: "four"}
        ListElement{n: 7; title: "Notebook 4"; description: "four"}
        ListElement{n: 8; title: "Notebook 4"; description: "four"}
        ListElement{n: 9; title: "Notebook 4"; description: "four"}
        ListElement{n: 10; title: "Notebook 4"; description: "four"}
        ListElement{n: 11; title: "Notebook 5"; description: "five"}

        function getNewId() {
            return count()
        }
    }

    property ListModel groups: ListModel {
        ListElement {n:0; notebook: 0; title: "Group_1"; description: "One"; icon: "../assets/icon_3.png"; sum: -1000}
        ListElement {n:0; notebook: 0; title: "Group_2"; description: "Two"; icon: "../assets/icon_1.png"; sum: 100}
        ListElement {n:0; notebook: 0; title: "Group_3"; description: "Three"; icon: "../assets/icon_2.png"; sum: -1500}
        ListElement {n:0; notebook: 0; title: "Group_4"; description: "Four"; icon: "../assets/icon_4.png"; sum: 3040}
    }

    property ListModel labels: ListModel {
        ListElement{n: 0; title: "Label_1"; colored: "#000000"}
        ListElement{n: 0; title: "Label_2"; colored: "#000000"}
    }

    property ListModel notes: ListModel {
        ListElement{n: 0; title: "note_1"; sum: -150; date: "21-11-2021"; description: "Descroption\nDescription\nDescription"; group_title: "Group_1"; icon: "../assets/icon_3.png"}
        ListElement{n: 0; title: "note_2"; sum: 465; date: "21-11-2021"; description: "Descroption\nDescription\nDescription"; group_title: "Group_2"; icon: "../assets/icon_1.png"}
        ListElement{n: 0; title: "note_3"; sum: -940; date: "21-11-2021"; description: "Descroption\nDescription\nDescription"; group_title: "Group_3"; icon: "../assets/icon_2.png"}
    }

    property var icons: [
        {icon: "../../assets/icon_1.png", text: "icon_1"},
        {icon: "../../assets/icon_2.png", text: "icon_2"},
        {icon: "../../assets/icon_3.png", text: "icon_3"},
        {icon: "../../assets/icon_4.png", text: "icon_4"}
    ]
}
