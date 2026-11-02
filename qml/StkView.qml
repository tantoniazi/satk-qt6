/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: container

    property alias showEndButton: panel.showEndButton
    property alias showBackButton: panel.showBackButton

    property alias theme: theme
    property alias stkTheme: stkTheme

    property alias title: title
    property alias icon: icon
    property alias panel: panel

    width: stkTheme.viewWidth
    height: stkTheme.viewHeight

    color: stkTheme.viewBackgroundColor

    signal accepted()
    onAccepted: console.log("StkView Accepted")
    signal rejected()
    onRejected: console.log("StkView Rejected")
    signal textEntered(string text)
    onTextEntered: console.log("StkView Text entered: " + text)
    signal itemSelected(int selection)
    onItemSelected: console.log("StkView Item selected: " + selection)
    signal goBack()
    onGoBack: console.log("StkView Go back")
    signal endSession()
    onEndSession: console.log("StkView End session")

    StkPanel {
        id: panel
        objectName: "panel"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onGoBack: view.goBack()
        onEndSession: view.endSession()
    }

    Text {
        id: title
        objectName: "title"
        text: "SIM Application Toolkit"
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: icon.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        wrapMode: Text.WordWrap
        color: stkTheme.titleFontColor
        font.pixelSize: stkTheme.titleFontPixelSize
    }

    Image {
        id: icon
        objectName: "icon"
        width: 64
        height: 64
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
    }
}
