#ifndef FILEITEM_H
#define FILEITEM_H

#include <QObject>
#include <QIcon>

#include "filelistmodel.h"

class FileItem : public QObject {
    Q_OBJECT

    friend class FileListModel;

public:
    FileItem(const QString & pathFile, QObject * parent = 0);
    void load(const QString & pathFile);

    QString getPath();
    QString getName();
    QPixmap getIcon();
    QString getIdFile();

    FileListModel * getModel();

private:
    QString path;
    QString name;
    QPixmap icon;
    FileListModel * model;

signals:
    void aboutChanged();
};

#endif // FILEITEM_H
