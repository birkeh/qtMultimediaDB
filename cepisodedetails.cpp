#include "cepisodedetails.h"
#include "ui_cepisodedetails.h"

#include "cmovieimage.h"
#include "cmessageanimatedialog.h"

#include <QDebug>
#include <QTreeWidgetItem>


cEpisodeDetails::cEpisodeDetails(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cEpisodeDetails),
	m_lpDetailsActorsModel(0),
	m_lpEpisode(0),
	m_bLoaded(false)
{
	ui->setupUi(this);

	m_lpDetailsActorsModel	= new QStandardItemModel(0, 0);
	ui->m_lpDetailsActors->setModel(m_lpDetailsActorsModel);
}

cEpisodeDetails::~cEpisodeDetails()
{
	delete m_lpDetailsActorsModel;
	delete ui;
}

void cEpisodeDetails::setEpisode(cEpisode* lpEpisode)
{
	m_lpEpisode	= lpEpisode;
	ui->m_lpEpisodeTitle->setText(lpEpisode->name());
	ui->m_lpOverview->setText(lpEpisode->overview());

	for(int x = 0;x < lpEpisode->guestStars().count();x++)
	{
		QStringList				tmp	= lpEpisode->guestStars().at(x).split(",");
		QList<QStandardItem*>	items;

		items <<  new QStandardItem(tmp.at(0));
		if(tmp.count() > 1)
			items << new QStandardItem(tmp.at(1));

		m_lpDetailsActorsModel->appendRow(items);
	}
	ui->m_lpDetailsActors->resizeColumnToContents(0);
	ui->m_lpDetailsActors->resizeColumnToContents(1);
}

void cEpisodeDetails::loadImages()
{
	if(!m_lpEpisode)
		return;

	if(m_bLoaded)
		return;

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Details");
	lpDialog->setMessage("Loading Images");
	lpDialog->show();

	cMovieImage	image;
	QPixmap	pixmap	= image.getImage(m_lpEpisode->stillPath()).scaledToHeight(100);
	ui->m_lpEpisodeThumb->setPixmap(pixmap);

	delete lpDialog;

	m_bLoaded	= true;
}
