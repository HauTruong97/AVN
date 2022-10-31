import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQml.Models 2.2

DelegateModel {
    property var filter: null
    onFilterChanged: Qt.callLater(update)
    groups: [
        DelegateModelGroup {
            id: allItems
            name: "all"
            includeByDefault: true
            onCountChanged: Qt.callLater(update)
        },
        DelegateModelGroup {
            id: visibleItems
            name: "visible"
        }
    ]
    filterOnGroup: "visible"
    function update() {
        allItems.setGroups(0, allItems.count, [ "all" ] );
        for (var index = 0; index < allItems.count; index++) {
            let visible = !filter || filter(allItems.get(index).model);
            if (!visible) continue;
            allItems.setGroups(index, 1, [ "all", "visible" ]);
        }
    }
    Component.onCompleted: Qt.callLater(update)
}
