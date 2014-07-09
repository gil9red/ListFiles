#ifndef FILELIST_H
#define FILELIST_H

#include <QObject>
#include "filelistmodel.h"
#include <QSortFilterProxyModel>

class FileListManager : public QObject {
    Q_OBJECT

public:
    explicit FileListManager(QObject *parent = 0);

    FileListModel * getModel();
    QSortFilterProxyModel * getSortFilterProxyModel();
    QQuickImageProvider * getImageProvider();

public slots:
    void read();
    void write();

    int countFiles();
    int countFilterFiles();
    void addFileFromUrls(const QList<QUrl> & urls);
    void removeFile(int index);
    void run(int index);
    void edit(int index);
    void searchItems(const QString & text);

    void about();
    void quit();

private:
    FileListModel model;
    QSortFilterProxyModel filterModel;
};

#endif // FILELIST_H
