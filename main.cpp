#include <QApplication>

#include <QFileInfo>

//#include <QQmlEngine>
//#include <QQmlFileSelector>
//#include <QQuickView>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "foo.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
    app.setOrganizationName("ListExe");
    app.setOrganizationDomain("gil9red.listexe.org");
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());

    QQmlApplicationEngine engine;    
    QQmlContext * rootContext = engine.rootContext();

    Foo foo;
    rootContext->setContextProperty("foo", &foo);
    rootContext->setContextProperty("app", qApp);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

//    QQuickView view;
//    if (qgetenv("QT_QUICK_CORE_PROFILE").toInt())
//    {
//        QSurfaceFormat f = view.format();
//        f.setProfile(QSurfaceFormat::CoreProfile);
//        f.setVersion(4, 4);
//        view.setFormat(f);
//    }
//    view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));

//    new QQmlFileSelector(view.engine(), &view);

//    view.setSource(QUrl("qrc:/qml/main.qml"));
//    view.setResizeMode(QQuickView::SizeRootObjectToView);
//    view.show();

    return app.exec();
}
