#ifndef FILELIST_H
#define FILELIST_H

#include <QObject>
#include "filelistmodel.h"

class FileListManager : public QObject {
    Q_OBJECT

public:
    explicit FileListManager(QObject *parent = 0);

    FileListModel * getModel();
    QQuickImageProvider * getImageProvider();

    void read();
    void write();

public slots:
    void run(int index);
    void edit(int index);

    void about();
    void quit();

private:
    FileListModel model;
};

#endif // FILELIST_H
