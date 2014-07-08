#include "fileiconimageprovider.h"
#include <QDebug>
#include "filelistmodel.h"

FileIconImageProvider::FileIconImageProvider(FileListModel * model)
    : QQuickImageProvider(QQmlImageProviderBase::Pixmap),
      fileListModel(model) {
}

QPixmap FileIconImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
    QPixmap pixmap = fileListModel->iconFileFromId(id);
    if (size)
        *size = pixmap.size();
    return pixmap;
}
