import Felgo 3.0
import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQml 2.12
import "content"
import "controls"
import "logic"

import com.custom 1.0

App {

    // You get free licenseKeys from https://felgo.com/licenseKey
    // With a licenseKey you can:
    //  * Publish your games & apps for the app stores
    //  * Remove the Felgo Splash Screen or set a custom one (available with the Pro Licenses)
    //  * Add plugins to monetize, analyze & improve your apps (available with the Pro Licenses)
    //licenseKey: "<generate one from https://felgo.com/licenseKey>"
    Models {
        id: models
    }

    Core {
        id: core


    }

    property ListModel tmpGroup: ListModel {
        onCountChanged: {
            if(notebookUpdate)
            {
                core.addGroup(tmpGroup.get(0)._title, tmpGroup.get(0)._description, tmpGroup.get(0)._icon, core.currentNotebook)
                tmpGroup.clear();
            }
        }
    }
    property ListModel tmpLabel: ListModel {
    onCountChanged: {
        if(notebookUpdate)
        {
            core.addLabel(tmpLabel.get(0)._title, tmpLabel.get(0)._color, core.currentNotebook)
            tmpLabel.clear()
        }
    }
    }

    property bool notebookUpdate: false

    NavigationStack {
        id: startNavStack

        Page {
            id: startPage
            title: qsTr("Добро пожаловать!")

            PageNotebookSelect {
                id: notebookSelect
                model: core.notebookModel

                anchors.fill: parent

                onClickedAdd: startNavStack.push(addNotebook)
                onClickedOpen: {
                    core.currentNotebook = idNotebook
                    core.getTotalPlus(core.currentNotebook)
                    core.getTotalMinus(core.currentNotebook)
                    core.selectNoteByCurrentNotebook();
                    startNavStack.visible = false
                    mainNavStack.visible = true
                }
            }
        }

        Component {
            id: addNotebook

            Page {
                title: qsTr("Создание книжки")

                ContentAddNotebook {
                    anchors.fill: parent

                    groupModel: tmpGroup
                    labelsModel: tmpLabel

                    onClickedSave: {
                        core.addNotebook(title)

                        for(var i = 0; i < tmpGroup.count; i++)
                        {
                            core.addGroup(tmpGroup.get(i)._title, tmpGroup.get(i)._description, tmpGroup.get(i)._icon, core.getLastNotebook())
                        }

                        for(var i = 0; i < tmpLabel.count; i++)
                        {
                            core.addLabel(tmpLabel.get(i)._title, tmpLabel.get(i)._color, core.getLastNotebook())
                        }

                        tmpGroup.clear();
                        tmpLabel.clear();

                        startNavStack.pop()
                    }

                    onClickedAddGroup: {
                        notebookUpdate = false
                        startNavStack.push(addGroup)
                    }
                    onClickedAddLabel: {
                        notebookUpdate = false
                        startNavStack.push(addLabels)
                    }

                    onRemoveGroup: tmpGroup.remove(ind, 1)
                    onRemoveLabel: tmpLabel.remove(ind, 1)
                }
            }
        }

        Component {
            id: addGroup

            Page {
                title: qsTr("Добавление группы")

                ContentAddGroup {
                    anchors.fill: parent

                    imageModel: models.icons

                    onClickedSave: {
                        console.log(icon);
                        tmpGroup.append({_title: title, _icon: icon, _description: description})
                        startNavStack.pop()
                        navStackNotebook.pop()
                    }
                }
            }
        }

        Component {
            id: addLabels

            Page {
                title: qsTr("Добавление метки")

                ContentAddLabel {
                    anchors.fill: parent

                    onClickedSave: {
                        tmpLabel.append({_title: title, _color: color})
                        startNavStack.pop()
                        navStackNotebook.pop()
                    }
                }
            }
        }
    }


    Navigation {
        id: mainNavStack
        visible: false

        headerView: AppPaper {
            height: parent.height / 2

            background.color: Theme.colors.tintColor

            AppText {
                text: "Notebook"
                color: Theme.colors.backgroundColor
                fontSize: dp(22)
                font.bold: true

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.margins: dp(10)
            }
        }

        footerView: AppListItem {
            anchors.bottom: parent.bottom

            text: "Выход"

            mouseArea.onClicked: {
                startNavStack.visible = true
                mainNavStack.visible = false
            }
        }

        NavigationItem {
            title: "Главная"

            NavigationStack {
                id: navStackMainPage

                Page {
                    id: mainaNavePage
                    title: "Главная"

                    function setChart()
                        {
                        mainPage.setChart()
                    }

                    ContentMainPage {
                        id: mainPage
                        anchors.fill: parent

                        groups: core.groupModel
                        labels: core.labelModel
                        notes: core.noteModel

                        onClickedNotes: {
                            core.currentNote = idNote
                            navStackMainPage.push(infoNote)
                        }
                        onClickedGroup: {
                            core.currentGroup = idGroup
                            navStackMainPage.push(listNotes)
                        }



                    }

                    AppButton {
                        height: dp(75)
                        width: dp(75)

                        minimumWidth: dp(75)

                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        //anchors.margins: dp(5)

                        radius: dp(30)

                        AppImage {
                            anchors.fill: parent
                            anchors.margins: dp(25)

                            source: "../assets/plus_white.png"
                        }

                        onClicked: navStackMainPage.push(addNote)
                    }

                }

                Component {
                    id: addNote

                    Page {
                        title: "Создание записи"

                        ContentAddNote {
                            anchors.fill: parent

                            groupModel: core.groupModel
                            labelModel: core.labelModel
                        }
                    }
                }

                Component {
                    id: infoNote

                    Page {
                        title: "Запись"

                        ContentInfoNote {
                            anchors.fill: parent

                            notes: core.noteModel
                            labels: core.labelModel
                        }
                    }
                }

                Component {
                    id: listNotes

                    Page {
                        title: "Записи"

                        rightBarItem: TextButtonBarItem {
                            text: "Инфо"
                            color: Theme.colors.backgroundColor

                            onClicked: navStackNotebook.push(changeNotebook)
                          }

                        PageListNotes {
                            anchors.fill: parent

                            notes: core.noteModel
                            labels: core.labelModel

                            onClickedNote: {
                                core.currentNote = idNote
                                navStackMainPage.push(infoNote)
                            }
                        }
                    }
                }
            }
        }

        NavigationItem {
            title: "Графики"

            NavigationStack {
                id: navStackGraphics

                property var selectGraphick: id

                Page {
                    title: "Графики"

                    ContentGraphicPage {
                        anchors.fill: parent

                        onClickedByNotes: {
                            navStackGraphics.selectGraphick = graphickNotes
                            navStackGraphics.push(selectDateInterval)
                        }
                        onClickedByGroups: {
                            navStackGraphics.selectGraphick = graphickGroup
                            navStackGraphics.push(selectDateInterval)
                        }
                        onClickedByLabels: {
                            navStackGraphics.selectGraphick = graphickLabel
                            navStackGraphics.push(selectDateInterval)
                        }
                    }
                }

                Component {
                    id: selectDateInterval

                    Page {
                        title: "Период"

                        ContentSelectGraphicsPage {
                            anchors.fill: parent

                            onClickedContinue: {
                                core.beginDate = beginDate
                                core.endDate = endDate
                                navStackGraphics.push(navStackGraphics.selectGraphick)

                                console.log(core.getListTotalPlusByDate())
                                console.log(core.getListTotalMinusByDate())
                            }
                        }
                    }
                }

                Component {
                    id: graphickNotes

                    Page {
                        title: "График трат по дням"

                        ContentGraphicsNotesPage {
                            id: grContent
                            anchors.fill: parent

                            daysNumbers: core.convertListDate()
                            plus: core.getListTotalPlusByDate()
                            minus: core.getListTotalMinusByDate()
                        }
                    }
                }

                Component {
                    id: graphickGroup

                    Page {
                        title: "График по категориям"

                        ContentGraphicGroupPage {
                            anchors.fill: parent

                            groups: core.getListGroupTitles(core.currentNotebook);
                            plus: core.getListPlusByGroup(core.currentNotebook, core.beginDate, core.endDate)
                        }
                    }
                }

                Component {
                    id: graphickLabel

                    Page {
                        title: "График по меткам"

                        ContentGraphicLabelPage {
                            anchors.fill: parent

                            groups: core.getListLabelTitles(core.currentNotebook)
                            plus: core.getListPlusByLabel(core.currentNotebook, core.beginDate, core.endDate)
                        }
                    }
                }
            }
        }

        NavigationItem {
            title: "Дневник"

            NavigationStack {
                id: navStackNotebook

                Page {
                    title: "Дневник"

                    rightBarItem: TextButtonBarItem {
                        text: "Изменить"
                        color: Theme.colors.backgroundColor

                        onClicked: navStackNotebook.push(changeNotebook)
                      }

                    ContentViewNotebook {
                        anchors.fill: parent

                        groupModel: core.groupModel
                        labelsModel: core.labelModel
                        notebooksModel: core.notebookModel
                    }
                }

                Component {
                    id: changeNotebook

                    Page {
                        title: "Редактирование книжки"

                        ContentAddNotebook {
                            anchors.fill: parent

                            property ListModel removeListGroup: ListModel {}
                            property ListModel removeListLabel: ListModel {}

                            notebookTitle: core.getNotebookTitleById(core.currentNotebook)

                            groupModel: core.groupModel
                            labelsModel: core.labelModel

                            onRemoveGroup: removeListGroup.append({_index: ind})
                            onRemoveLabel: removeListLabel.append({_index: ind})

                            onClickedAddGroup: {
                                notebookUpdate = true
                                navStackNotebook.push(addGroup)
                            }
                            onClickedAddLabel: {
                                notebookUpdate = true
                                navStackNotebook.push(addLabels)
                            }
                            onSetGroup: navStackNotebook.push(addGroup)
                            onSetLabel: navStackNotebook.push(addLabels)

                            onClickedSave: {
                                for(var i = 0; i < removeListGroup.count; i++)
                                    core.removeGroup(removeListGroup.get(i)._index)

                                for(var i = 0; i < removeListLabel.count; i++)
                                    core.removeLabel(removeListLabel.get(i)._index)

                                navStackNotebook.pop()
                            }
                        }
                    }
                }
            }
        }
    }
}



