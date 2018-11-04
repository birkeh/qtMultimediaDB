#include "cdiscover.h"
#include "ui_cdiscover.h"


cDiscover::cDiscover(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cDiscover)
{
	ui->setupUi(this);
}

cDiscover::~cDiscover()
{
	delete ui;
}
