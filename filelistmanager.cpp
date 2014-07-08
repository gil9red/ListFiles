#include "filelistmanager.h"

#include <QDir>
#include <QStandardPaths>
#include <QApplication>
#include <QDesktopServices>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QTextStream>

FileListManager::FileListManager(QObject *parent) :
    QObject(parent) {

    read();
}

FileListModel * FileListManager::getModel() {
    return &model;
}
QQuickImageProvider * FileListManager::getImageProvider() {
    return model.getNewImageProvider();
}

void FileListManager::read() {
    QDomDocument document("Files");
    QFile file("files.xml");
    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream out(&file);
    out.setCodec("utf-8");

    if (!document.setContent(out.readAll())) {
        file.close();
        return;
    }
    file.close();

    // Распарсим xml
    QDomElement root = document.documentElement();
    QDomNode child = root.firstChild();
    while (!child.isNull()) {
        QDomElement fileElement = child.toElement(); // try to convert the node to an element.
        if (!fileElement.isNull())
            model.addFile(fileElement.attribute("Path"));

        child = child.nextSibling();
    }
}
void FileListManager::write() {
    QDomDocument document;
    QDomElement root = document.createElement("Files");
    document.appendChild(root);

    for (int row = 0; row < model.rowCount(); row++) {
        FileItem * fileItem = model.item(row);
        QDomElement fileElement = document.createElement("File");
        fileElement.setAttribute("Path", fileItem->getPath());

        root.appendChild(fileElement);
    }

    QFile file("files.xml");
    if (file.open(QIODevice::WriteOnly)) {
       QTextStream in(&file);
       in.setCodec("utf-8");
       in << document.toString();
    }
}

void FileListManager::run(int index) {
    QUrl url = QUrl::fromLocalFile(model.item(index)->getPath());
    QDesktopServices::openUrl(url);
}
void FileListManager::quit() {
    write();
    qApp->quit();
}
void FileListManager::edit(int index) {
    qDebug() << "FileListManager::edit(int index)" << model.item(index)->getPath();
}
void FileListManager::about() {
    qApp->aboutQt();
}
