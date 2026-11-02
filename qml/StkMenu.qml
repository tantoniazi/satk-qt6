/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.ListView 1.0

Rectangle {
    id: view
    objectName: "view"

    width: stkTheme.viewWidth
    height: stkTheme.viewHeight

    color: stkTheme.viewBackgroundColor

    signal itemSelected(int selection)
    signal goBack()
    signal endSession()

    ListView {
        id: menuView
        objectName: "menuView"
        model: menuModel
        delegate: menuDelegate
        highlight: Rectangle {
            color: "#4a90e2"
            width: menuView.width
        }
        highlightFollowsCurrentItem: true
        anchors.top: icon.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        clip: true

        onItemSelected: {
            currentIndex = selection
            view.itemSelected(selection)
        }
    }

    Component {
        id: menuDelegate
        Row {
            spacing: 10
            Image {
                width: 32
                height: 32
                anchors.verticalCenter: parent.verticalCenter
                source: icon
                MouseArea {
                    anchors.fill: parent
                    onClicked: menuView.itemSelected(index)
                }
            }
            Text {
                height: 48
                verticalAlignment: Text.AlignVCenter
                color: "#333333"
                font.pixelSize: 18
                text: title
                MouseArea {
                    width: menuView.width
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    onClicked: menuView.itemSelected(index)
                }
            }
        }
    }

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
        color: "#333333"
        font.pixelSize: 20
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
