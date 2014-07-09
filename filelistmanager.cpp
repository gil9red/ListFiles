#include "filelistmanager.h"

#include <QDir>
#include <QStandardPaths>
#include <QApplication>
#include <QDesktopServices>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QTextStream>
#include <QMessageBox>
#include "editfileitem.h"
#include "fileitem.h"

FileListManager::FileListManager(QObject *parent) :
    QObject(parent) {
    filterModel.setSourceModel(&model);
    filterModel.setDynamicSortFilter(true);
}

FileListModel * FileListManager::getModel() {
    return &model;
}
QSortFilterProxyModel * FileListManager::getSortFilterProxyModel() {
    return &filterModel;
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

int FileListManager::countFiles() {
    return model.rowCount();
}
int FileListManager::countFilterFiles() {
    return filterModel.rowCount();
}
void FileListManager::addFileFromUrls(const QList<QUrl> & urls) {
    foreach (QUrl url, urls)
        model.addFileFromUrl(url);

    write(); // Сохраняем список файлов
}
void FileListManager::removeFile(int index) {
    QModelIndex proxyIndex = filterModel.index(index, 0);
    QModelIndex modelIndex = filterModel.mapToSource(proxyIndex); // конвертируем индекс прокси модели в индекс нашей модель
    int row = modelIndex.row();

    model.removeFile(row);
    write(); // Сохраняем список файлов
}
void FileListManager::run(int index) {
    QModelIndex proxyIndex = filterModel.index(index, 0);
    QModelIndex modelIndex = filterModel.mapToSource(proxyIndex); // конвертируем индекс прокси модели в индекс нашей модель
    int row = modelIndex.row();

    QUrl url = QUrl::fromLocalFile(model.item(row)->getPath());
    QDesktopServices::openUrl(url);
}
void FileListManager::quit() {
    write();
    qApp->quit();
}
void FileListManager::edit(int index) {
    QModelIndex proxyIndex = filterModel.index(index, 0);
    QModelIndex modelIndex = filterModel.mapToSource(proxyIndex); // конвертируем индекс прокси модели в индекс нашей модель
    int row = modelIndex.row();
    FileItem * file = model.item(row);

    EditFileItem edit;
    edit.setFileItem(file);
    edit.exec();
}
void FileListManager::searchItems(const QString & text) {
    filterModel.setFilterFixedString(text);
}
void FileListManager::about() {
    const QString & text = qApp->applicationName() + " v" + qApp->applicationVersion()
            + QObject::trUtf8("\nAuthor Ilya Petrash")
            + QObject::trUtf8("\nContains links files");
    QMessageBox::about(0, QObject::trUtf8("About"), text);
}
