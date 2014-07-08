#ifndef FILEICONIMAGEPROVIDER_H
#define FILEICONIMAGEPROVIDER_H

#include <QQuickImageProvider>

class FileListModel;

class FileIconImageProvider : public QQuickImageProvider {
public:
    FileIconImageProvider(FileListModel * model);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
    FileListModel * fileListModel;
};

#endif // FILEICONIMAGEPROVIDER_H
