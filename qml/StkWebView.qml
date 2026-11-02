/*
 * satk - SIM application toolkit
 * Copyright © 2011, Intel Corporation.
 * Ported to Qt 6 - MeeGo rebuild project
 */

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtWebEngine 1.0

Rectangle {
    id: container
    color: "#2c3e50"
    width: 400
    height: 300

    property string url: ""

    WebEngineView {
        id: webView
        anchors.fill: parent
        url: container.url
    }
}
