//#include "fileiconimageprovider.h"
//#include <QDebug>
//#include "filelistmodel.h"

//FileIconImageProvider::FileIconImageProvider(FileListModel * model)
//    : QQuickImageProvider(QQmlImageProviderBase::Pixmap),
//      fileListModel(model) {
//}

//QPixmap FileIconImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
//    QPixmap pixmap = fileListModel->iconFileFromId(id).scaled(requestedSize, Qt::IgnoreAspectRatio);
//    if (size)
//        *size = pixmap.size();
//    qDebug() << QString("requestPixmap(%1)").arg(id) << "pixmap=" << pixmap;
//    return pixmap;
//}
