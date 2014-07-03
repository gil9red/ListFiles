#ifndef FOO_H
#define FOO_H

#include <QApplication>

class Foo : public QObject
{
    Q_OBJECT

public:
    Foo();

public slots:
    void say();
};

#endif // FOO_H
