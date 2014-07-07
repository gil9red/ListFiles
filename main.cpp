#include <QApplication>

#include <QFileInfo>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "programlistmodel.h"

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
    app.setOrganizationName("ListExe");
    app.setOrganizationDomain("gil9red.listexe.org");
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());

    QQmlApplicationEngine engine;
    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("app", qApp);

    ProgramListModel programListModel;
    rootContext->setContextProperty("programListModel", &programListModel);

    programListModel.addProgram(qApp->applicationFilePath());
    foreach (QString path, QDir( QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first() ).entryList(QStringList()<<"*.lnk", QDir::Files | QDir::NoDotAndDotDot)) {
        qDebug() << path;
        programListModel.addProgram(path);
    }

    ProgramIconImageProvider * programIconImageProvider = new ProgramIconImageProvider();
    programIconImageProvider->programListModel = &programListModel;
    engine.addImageProvider("programicon", programIconImageProvider);
    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}
