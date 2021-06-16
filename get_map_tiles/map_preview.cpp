#include "map_preview.h"
#include "ui_map_preview.h"

map_preview::map_preview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::map_preview)
{
    ui->setupUi(this);
 }

map_preview::~map_preview()
{
    delete ui;
}

void map_preview::loding_map()
{
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    ui->quickWidget->show();
}
