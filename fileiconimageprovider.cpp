#include "fileiconimageprovider.h"
#include <QDebug>
#include "filelistmodel.h"

FileIconImageProvider::FileIconImageProvider(FileListModel * model)
    : QQuickImageProvider(QQmlImageProviderBase::Pixmap),
      fileListModel(model) {
}

QPixmap FileIconImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
    Q_UNUSED(requestedSize)

    QPixmap pixmap = fileListModel->iconFileFromId(id);
    if (size)
        *size = pixmap.isNull() ? QSize(32, 32) : pixmap.size();
    return pixmap;
}
