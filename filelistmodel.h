#ifndef PROGRAMLISTMODEL_H
#define PROGRAMLISTMODEL_H

#include <QAbstractListModel>
#include <QIcon>

class FileItem : public QObject {
    Q_OBJECT

public:
    FileItem(const QString & pathFile, QObject * parent = 0);
    void load(const QString & pathFile);

    QString getPath();
    QString getName();
    QIcon getIcon();
    QString getIdIcon();

private:
    QString path;
    QString name;
    QIcon icon;
};

#include "fileiconimageprovider.h"

class FileListModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        Path = Qt::UserRole + 1,
        Name,
        Icon,
        IdIcon
    };

public:
    explicit FileListModel(QObject *parent = 0);

    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;

    QPixmap iconFileFromId(const QString & id);

    FileItem * item(int index);

    QQuickImageProvider * getNewImageProvider() {
        return new FileIconImageProvider(this);
    }

public slots:
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

    void addFile(const QString & pathFile);
    void addFileFromUrl(const QUrl & url);
    void removeFile(int index);

private:
    QList<FileItem *> files;
    QHash<QString, FileItem *> hash_IdIcon_File;
};

#endif // PROGRAMLISTMODEL_H
