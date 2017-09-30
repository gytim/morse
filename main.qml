import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

import QtQuick.Dialogs 1.0

Window {
    visible: true

    width: 640
    height: 480

    color: "lightgrey"

    title: qsTr("MorseTranslate")

    //Загрузка файла
    FileDialog {
        id: loadFileDialog

        title: "Please choose a file"

        folder: shortcuts.home

        onAccepted: {
            var str = loadFileDialog.fileUrl.toString();
            str = str.replace("file://", "");

            cpp_mainWindow.loadFile(str)

            loadFileDialog.close();
        }
        onRejected: {
            loadFileDialog.close();
        }
    }

    //Сохранение файла
    FileDialog {
        id: saveFileDialog

        title: "Please choose a file"

        folder: shortcuts.home
        selectFolder: true

        onAccepted: {
            var str = saveFileDialog.fileUrl.toString();
            str = str.replace("file://", "");

            cpp_mainWindow.saveFile(str, textTarget.text);

            saveFileDialog.close();
        }
        onRejected: {
            saveFileDialog.close();
        }
    }

 //Кнопки
    Button {
        id: buttonOpen

        width: 120
        height: 40

        anchors.top : parent.top
        anchors.left : parent.left
        anchors.leftMargin : 10
        anchors.topMargin : 10

        text: qsTr("Open")

        onClicked: {
            loadFileDialog.open();
        }
    }

    Button {
        id: buttonSave

        width: 120
        height: 40

        anchors.top : parent.top
        anchors.right : parent.right
        anchors.topMargin : 10
        anchors.rightMargin : 10

        text: qsTr("Save")

        onClicked: {
            saveFileDialog.open();
        }
    }

    Button {
        id: buttonTranslate

        width: 120
        height: 40

        anchors.horizontalCenter:  parent.horizontalCenter

        anchors.top : parent.top
        anchors.topMargin : 10

        text: qsTr("Translate")

        onClicked: {
            cpp_mainWindow.translateText(textSource.text)
        }
    }

 //Тело
    Rectangle   {
        id: textSourceArea

        width: parent.width / 2 - 20

        anchors.top: buttonOpen.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        anchors.margins: 10

        color: "white"

        border.width: 1

        TextEdit {
            id: textSource
            objectName: "textSource"

            anchors.fill: parent

            anchors.margins: 15

            font.pixelSize: 15

            wrapMode: Text.Wrap

            text: qsTr("")
        }
    }

    Rectangle   {
        id: textTextTarget

        width: parent.width / 2 - 20

        anchors.top: buttonOpen.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.margins: 10

        color: "white"

        border.width: 1

        TextEdit {
            id: textTarget
            objectName: "textTarget"

            anchors.fill: parent

            anchors.margins: 15

            font.pixelSize: 15

            wrapMode: Text.Wrap

            text: qsTr("")
        }
    }
}
