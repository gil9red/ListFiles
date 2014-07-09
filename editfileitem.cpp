#include "editfileitem.h"
#include "ui_editfileitem.h"
#include <QFileDialog>

EditFileItem::EditFileItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditFileItem) {
    ui->setupUi(this);
}

EditFileItem::~EditFileItem() {
    delete ui;
}

void EditFileItem::setFileItem(FileItem * fileItem) {
    item = fileItem;
    fillFromFileItem(item);
}

void EditFileItem::fillFromFileItem(FileItem * fileItem) {
    ui->path->setText(fileItem->getPath());
    ui->name->setText(fileItem->getName());
    ui->icon->setPixmap(fileItem->getIcon());
}

void EditFileItem::on_selectPath_clicked() {
    const QString & path = QFileDialog::getOpenFileName();
    if (path.isEmpty())
        return;

    FileItem temp(path);
    fillFromFileItem(&temp);
}

void EditFileItem::accept() {
    const QString & newPath = ui->path->text();
    item->load(newPath);

    QDialog::accept();
}
