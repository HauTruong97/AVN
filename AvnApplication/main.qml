import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import sortHT 1.0
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    id: window
    visible: true
    color: "#FDFEFE"
    title: "Avn Application1"
    width: 400
    maximumWidth: 400
    maximumHeight: 700
    height: 700

    Item {
        id: implement
        Text {
            id: name
            text: employee.getEmployeesName
            width: 400; height: 200
            font.pointSize: 12
            anchors.centerIn: parent.Center
            anchors.left: parent.left
            anchors.leftMargin: 135
            lineHeight: 50
            wrapMode: Text.WordWrap
        }

        Rectangle {
            width: 400; height: 200
            anchors.left: implement.left
            anchors.leftMargin: 70
            anchors.top: implement.top
            anchors.topMargin: 50
            Component {
                id: contactDelegate
                Item {
                    width: 400; height: 50
                    Row{
                        width: parent.width
                        spacing: 50
                        Image {
                            id: name
                            width: 30
                            height: 30
                            source: icon
                        }
                        TextEdit { text: language
                            width: 30
                        }
                        TextEdit { text: point
                            width: 30
                        }
                        Image {
                            source: point > 5 ? "/data/success.png"
                                              : "/data/fail.png"
                            width: 30
                            height: 30
                        }
                    }
                }
            }

            ListView {
                anchors.fill: parent
                orientation: Qt.Vertical
                model: employee
                delegate: contactDelegate
            }
        }

        Button{
            id: button
            width: 100
            height: 40
            anchors.left: implement.left
            anchors.leftMargin: 140
            anchors.top: implement.top
            anchors.topMargin: 300
            text: "Refresh"
        }
    }


    toolBar: ToolBar {
        TextField {
            id: searchBox
            placeholderText: "Search..."
            inputMethodHints: Qt.ImhNoPredictiveText
            width: parent.width / 5 * 3
            anchors.leftMargin: parent.left
            anchors.centerIn: parent.Center
            anchors.top: parent.top
            anchors.topMargin: 400
        }
    }

    TableView {
        id: tableView
        width: 200
        height: 200
        frameVisible: false
        sortIndicatorVisible: true
        anchors.fill: parent
        Layout.minimumWidth: 400
        Layout.minimumHeight: 240
        Layout.preferredWidth: 600
        Layout.preferredHeight: 400
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 400

        TableViewColumn {
            id: nameColumn
            title: "NAME"
            role: "name"
            movable: false
            resizable: false
            width: 250
        }

        TableViewColumn {
            id: gradeColumn
            title: "AVRAGE"
            role: "avrage"
            movable: false
            resizable: false
            width: 250
        }

        model: SortFilterProxyModel {
            id: proxyModel
            source: employeesModel.count > 0 ? employeesModel : employeesModel
            sortOrder: tableView.sortIndicatorOrder
            sortCaseSensitivity: Qt.CaseInsensitive
            sortRole: employeesModel.count > 0 ? tableView.getColumn(tableView.sortIndicatorColumn).role : ""
            filterString: "*" + searchBox.text + "*"
            filterSyntax: SortFilterProxyModel.Wildcard
            filterCaseSensitivity: Qt.CaseInsensitive
        }

        onClicked: {
            console.log("hihi:" + row)
            employee.requestToControllerChangeName(proxyModel.get(row).name);
        }
    }
}

