#include <QApplication>

#include <QFileInfo>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "filelistmanager.h"

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

    FileListManager fileListManager;
    rootContext->setContextProperty("fileListManager", &fileListManager);
    rootContext->setContextProperty("fileListModel", fileListManager.getModel());

    engine.addImageProvider("fileicon", fileListManager.getImageProvider());
    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}
