#include <QApplication>

#include <QFileInfo>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "filelistmodel.h"

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
    app.setOrganizationName("ListFiles");
    app.setApplicationName("ListFiles");
    app.setApplicationVersion("0.0.1");
    app.setApplicationDisplayName("ListFiles");
    app.setOrganizationDomain("gil9red.listfiles.org");    
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());

    QQmlApplicationEngine engine;
    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("app", qApp);

    FileListModel fileListModel;
    rootContext->setContextProperty("fileListModel", &fileListModel);

    // Добавим в модель себя же и все ярлыки и ехе на рабочем столе
    fileListModel.addFile(qApp->applicationFilePath());
    foreach (QFileInfo info, QDir( QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first() ).entryInfoList(QStringList()<<"*.*", QDir::Files | QDir::NoDotAndDotDot)) {
        fileListModel.addFile(info.absoluteFilePath());
    }

//    engine.addImageProvider("fileicon", fileListModel.getNewImageProvider());
    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}
