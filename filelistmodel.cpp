#include "filelistmodel.h"

#include <QFileInfo>
#include <QFileIconProvider>
#include <QCryptographicHash>
#include <QDebug>
#include <QLabel>

FileItem::FileItem(const QString & pathFile, QObject * parent/* = 0*/)
    : QObject (parent) {
    load(pathFile);
}

void FileItem::load(const QString & pathFile) {
    QFileInfo fileInfo(pathFile);
    path = fileInfo.absoluteFilePath();
    name = fileInfo.fileName();
//    icon = QFileIconProvider().icon(fileInfo);
//    if (icon.isNull())
//        icon = QFileIconProvider().icon(QFileIconProvider::File);
}

QString FileItem::getPath() {
    return path;
}
QString FileItem::getName() {
    return name;
}
//QIcon FileItem::getIcon() {
//    return icon;
//}
//QString FileItem::getIdIcon() {
//    return QCryptographicHash::hash(getPath().toUtf8(), QCryptographicHash::Sha1).toHex();
//}


FileListModel::FileListModel(QObject *parent)
    : QAbstractListModel(parent) {

}

void FileListModel::addFile(const QString & pathFile) {
    FileItem * file = new FileItem(pathFile, this);
//    hash_Id_Icon[file->getIdIcon()] = file->getIcon().pixmap(32, 32);
//    qDebug() << pathFile << "-> " + file->getIdIcon() << file->getIcon().pixmap(32, 32);

    int length = files.length();

    beginInsertRows(QModelIndex(), length, length);
    files << file;
    endInsertRows();

    //говорим view, что данные изменились
    emit dataChanged(createIndex(0,0), createIndex(length,0));
}
void FileListModel::removeFile(int index) {
//    FileItem * file = files.at(index);
//    hash_Id_Icon.remove(file->getIdIcon());

    beginRemoveRows(QModelIndex(), index, index);
    files.takeAt(index)->deleteLater(); // Удаляем из списка и освобождаем память
    endRemoveRows();

    //говорим view, что данные изменились
    emit dataChanged(createIndex(0,0), createIndex(files.length(),0));
}

int FileListModel::rowCount(const QModelIndex &/*= QModelIndex()*/) const {
    return files.length();
}
QVariant FileListModel::data(const QModelIndex & index, int role /*= Qt::DisplayRole*/) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    FileItem * file = files.at(index.row());

    switch (role) {
        case Qt::EditRole:
        case Qt::ToolTipRole:
        case Path:
            return file->getPath();

        case Qt::DisplayRole:
        case Name:
            return file->getName();

//        case Qt::DecorationRole:
//        case Icon:
//            return file->getIcon();

//        case IdIcon:
//            return file->getIdIcon();

        default:
            return QVariant();
    }

    return QVariant();
}
QHash<int, QByteArray> FileListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Path] = "path";
    roles[Name] = "name";
//    roles[IdIcon] = "idicon";
//    roles[Icon] = "icon";
    return roles;
}

//QPixmap FileListModel::iconFileFromId(const QString & id) {
//    return hash_Id_Icon[id];
//}
