#ifndef EDITFILEITEM_H
#define EDITFILEITEM_H

#include <QDialog>

namespace Ui {
    class EditFileItem;
}

#include "fileitem.h"

class EditFileItem : public QDialog {
    Q_OBJECT

public:
    explicit EditFileItem(QWidget *parent = 0);
    ~EditFileItem();

    void setFileItem(FileItem * fileItem);

private:
    void fillFromFileItem(FileItem *fileItem);

private slots:
    void on_selectPath_clicked();

public slots:
    void accept();

private:
    Ui::EditFileItem *ui;
    FileItem * item;
};

#endif // EDITFILEITEM_H
