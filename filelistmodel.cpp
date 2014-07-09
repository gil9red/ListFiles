#include "filelistmodel.h"
#include "fileitem.h"

#include "utils.h"

FileListModel::FileListModel(QObject *parent)
    : QAbstractListModel(parent) {

}

void FileListModel::addFile(const QString & pathFile) {
    FileItem * file = new FileItem(pathFile, this);
    file->model = this;
    file->setParent(this);
    QObject::connect(file, SIGNAL(aboutChanged()), SLOT(itemChanged()));

    hash_IdFile_File[file->getIdFile()] = file;

    int length = files.length();

    beginInsertRows(QModelIndex(), length, length);
    files << file;
    endInsertRows();

    //говорим view, что данные изменились
    emit dataChanged(createIndex(length, 0), createIndex(length, 0));
}
void FileListModel::addFileFromUrl(const QUrl & url) {
    if (url.isLocalFile())
        addFile(url.toLocalFile());
}
void FileListModel::removeFile(int index) {
    FileItem * file = files.at(index);
    hash_IdFile_File.remove(file->getIdFile());

    beginRemoveRows(QModelIndex(), index, index);
    files.takeAt(index)->deleteLater(); // Удаляем из списка и освобождаем память
    endRemoveRows();

    //говорим view, что данные изменились
    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
}

void FileListModel::itemChanged() {
    FileItem * item = qobject_cast<FileItem *> (sender());
    if (!item) {
        WARNING("null pointer!");
        return;
    }

    // Проверка Id - вдруг элемент изменился
    const QString & oldId = hash_IdFile_File.key(item);
    const QString & newId = item->getIdFile();
    if (oldId != newId) {
        // обновим хеш
        hash_IdFile_File.remove(oldId); // удалим старую запись
        hash_IdFile_File[newId] = item; // добавим новую
    }

    int index = files.indexOf(item);

    //говорим view, что данные изменились
    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
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

    case Qt::DecorationRole:
    case Icon:
        return file->getIcon();

    case IdIcon:
        return file->getIdFile();

    default:
        return QVariant();
    }

    return QVariant();
}
QHash<int, QByteArray> FileListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Path] = "path";
    roles[Name] = "name";
    roles[IdIcon] = "idicon";
    roles[Icon] = "icon";
    return roles;
}

QPixmap FileListModel::iconFileFromId(const QString & id) {
    FileItem * item = hash_IdFile_File[id];
    if (!item)
        return QPixmap();

    return item->getIcon();
}

FileItem * FileListModel::item(int index) {
    return files.at(index);
}
