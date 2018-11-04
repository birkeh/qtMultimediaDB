#ifndef CDISCOVER_H
#define CDISCOVER_H


#include <QDialog>


namespace Ui {
class cDiscover;
}

class cDiscover : public QDialog
{
	Q_OBJECT

public:
	explicit cDiscover(QWidget *parent = 0);
	~cDiscover();

private:
	Ui::cDiscover*	ui;
};

#endif // CDISCOVER_H
