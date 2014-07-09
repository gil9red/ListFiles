#ifndef UTILS_H
#define UTILS_H

#include <QDebug>

#define OUT_MESSAGE "\"%s\": in file \"%s\", func \"%s\", line %i"
#define WARNING( msg )  qWarning( OUT_MESSAGE,  qPrintable( msg ), __FILE__, __FUNCTION__, __LINE__ );
#define CRITICAL( msg ) qCritical( OUT_MESSAGE, qPrintable( msg ), __FILE__, __FUNCTION__, __LINE__ );
#define FATAL( msg )    qFatal( OUT_MESSAGE,    qPrintable( msg ), __FILE__, __FUNCTION__, __LINE__ );

#endif // UTILS_H
