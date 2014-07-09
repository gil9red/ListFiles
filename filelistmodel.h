#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QAbstractListModel>
#include "fileiconimageprovider.h"

class FileItem;

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

private slots:
    void itemChanged();

private:
    QList<FileItem *> files;
    QHash<QString, FileItem *> hash_IdFile_File;
};

#endif // FILELISTMODEL_H
