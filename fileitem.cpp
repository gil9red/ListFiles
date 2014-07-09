#include "fileitem.h"

#include <QFileInfo>
#include <QFileIconProvider>
#include <QCryptographicHash>
#include <QLabel>
#include "utils.h"

FileItem::FileItem(const QString & pathFile, QObject * parent/* = 0*/)
    : QObject (parent),
      model(0) {
    load(pathFile);
}

void FileItem::load(const QString & pathFile) {
    if (path == pathFile)
        return;

    QFileInfo fileInfo(pathFile);
    path = fileInfo.absoluteFilePath();
    name = fileInfo.fileName();

    QIcon fileIcon = QFileIconProvider().icon(fileInfo);
    if (fileInfo.isSymLink())
        fileIcon = QFileIconProvider().icon(QFileInfo(fileInfo.symLinkTarget()));

    icon = fileIcon.pixmap(32, 32);

    emit aboutChanged();
}

QString FileItem::getPath() {
    return path;
}
QString FileItem::getName() {
    return name;
}
QPixmap FileItem::getIcon() {
    return icon;
}
QString FileItem::getIdFile() {
    return QCryptographicHash::hash(getPath().toUtf8(), QCryptographicHash::Sha1).toHex();
}

FileListModel * FileItem::getModel() {
    return model;
}
