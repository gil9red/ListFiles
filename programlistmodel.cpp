#include "programlistmodel.h"

#include <QFileInfo>
#include <QFileIconProvider>
#include <QCryptographicHash>
#include <QDebug>

ProgramItem::ProgramItem(const QString & pathExe, QObject * parent/* = 0*/)
    : QObject (parent) {
    load(pathExe);
}

void ProgramItem::load(const QString & pathExe) {
    QFileInfo exeInfo(pathExe);
//    if (exeInfo.isSymLink())
//         exeInfo.setFile(exeInfo.symLinkTarget());

    path = exeInfo.absoluteFilePath();
    name = exeInfo.fileName();
    args = "";
    icon = QFileIconProvider().icon(exeInfo);
}
void ProgramItem::setArgs(const QString & argsExe) {
    args = argsExe;
}

QString ProgramItem::getPath() {
    return path;
}
QString ProgramItem::getName() {
    return name;
}
QString ProgramItem::getArgs() {
    return args;
}
QIcon ProgramItem::getIcon() {
    return icon;
}
QString ProgramItem::getIdIcon() {
    return QCryptographicHash::hash(getPath().toUtf8(), QCryptographicHash::Sha1).toHex();
}


ProgramListModel::ProgramListModel(QObject *parent)
    : QAbstractListModel(parent) {

}

void ProgramListModel::addProgram(const QString & pathExe) {
    ProgramItem * program = new ProgramItem(pathExe, this);
    hash_Id_Icon[program->getIdIcon()] = program->getIcon();

    int length = programs.length();

    beginInsertRows(QModelIndex(), length, length);
    programs << program;
    endInsertRows();


    //говорим view, что данные изменились
    emit dataChanged(createIndex(0,0), createIndex(length,0));
}
void ProgramListModel::removeProgram(int index) {
    ProgramItem * program = programs.at(index);
    hash_Id_Icon.remove(program->getIdIcon());

    beginRemoveRows(QModelIndex(), index, index);
    programs.takeAt(index)->deleteLater(); // Удаляем из списка и освобождаем память
    endRemoveRows();

    //говорим view, что данные изменились
    emit dataChanged(createIndex(0,0), createIndex(programs.length(),0));
}

int ProgramListModel::rowCount(const QModelIndex &/*= QModelIndex()*/) const {
    return programs.length();
}
QVariant ProgramListModel::data(const QModelIndex & index, int role /*= Qt::DisplayRole*/) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    ProgramItem * program = programs.at(index.row());

    switch (role) {
        case Qt::EditRole:
        case Qt::ToolTipRole:
        case Path:
            return program->getPath();

        case Qt::DisplayRole:
        case Name:
            return program->getName();

        case Args:
            return program->getArgs();

        case Qt::DecorationRole:
        case Icon:
            return program->getIcon();

        case IdIcon:
            return program->getIdIcon();

        default:
            return QVariant();
    }

    return QVariant();
}
QHash<int, QByteArray> ProgramListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Path] = "path";
    roles[Name] = "name";
    roles[Args] = "args";
    roles[IdIcon] = "idicon";
    roles[Icon] = "icon";
    return roles;
}

QIcon ProgramListModel::iconProgramFromId(const QString & id) {
    return hash_Id_Icon[id];
}
