/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: container

    property alias showEndButton: endRect.visible
    property alias showBackButton: backRect.visible

    color: "#2c3e50"

    signal goBack()
    signal endSession()

    Button {
        id: endRect
        objectName: "endRect"
        text: qsTr("End")
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        onClicked: container.endSession()
        visible: true
    }

    Button {
        id: backRect
        objectName: "backRect"
        text: qsTr("Back")
        anchors.top: endRect.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        onClicked: container.goBack()
        visible: true
    }
}
