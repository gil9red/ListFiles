#ifndef PROGRAMLISTMODEL_H
#define PROGRAMLISTMODEL_H

#include <QAbstractListModel>
#include <QIcon>

class ProgramItem : public QObject {
        Q_OBJECT

    public:
        ProgramItem(const QString & pathExe, QObject * parent = 0);
        void load(const QString & pathExe);
        void setArgs(const QString & argsExe);

        QString getPath();
        QString getName();
        QString getArgs();
        QIcon getIcon();
        QString getIdIcon();

    private:
        QString path;
        QString name;
        QString args;
        QIcon icon;
};

class ProgramListModel : public QAbstractListModel {
        Q_OBJECT

    public:
        enum Roles {
            Path = Qt::UserRole + 1,
            Name,
            Args,
            Icon,
            IdIcon
        };

    public:
        explicit ProgramListModel(QObject *parent = 0);
        QIcon iconProgramFromId(const QString & id);

        virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
        virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
        virtual QHash<int, QByteArray> roleNames() const;

    public slots:
        void addProgram(const QString & pathExe);
        void removeProgram(int index);

    private:
        QList<ProgramItem *> programs;
        QHash<QString, QIcon> hash_Id_Icon;
};


#include <QQuickImageProvider>
class ProgramIconImageProvider : public QQuickImageProvider {
    public:
        ProgramIconImageProvider()
            : QQuickImageProvider(QQmlImageProviderBase::Pixmap) {
        }

        QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
            QIcon icon = programListModel->iconProgramFromId(id);
            QPixmap pixmap = icon.pixmap(requestedSize).scaled(requestedSize, Qt::IgnoreAspectRatio);
            if (size)
                *size = pixmap.size();

            return pixmap;
        }

    public:
        ProgramListModel * programListModel;
};

#endif // PROGRAMLISTMODEL_H
