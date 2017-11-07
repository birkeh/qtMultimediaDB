#include "cmovieedit.h"
#include "cmovieimage.h"

#include "ui_cmovieedit.h"


cMovieEdit::cMovieEdit(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cMovieEdit),
	m_lpMovie(0)
{
	ui->setupUi(this);
}

cMovieEdit::~cMovieEdit()
{
	delete ui;
}

void cMovieEdit::setMovie(cMovie *lpMovie)
{
	m_lpMovie	= lpMovie;

	if(!lpMovie)
		return;

	ui->m_lpName->setText(lpMovie->movieTitle());
	ui->m_lpFirstAired->setDate(lpMovie->releaseDate());

	switch(lpMovie->state())
	{
	case cMovie::StateInit:
		ui->m_lpInit->setChecked(true);
		break;
	case cMovie::StateProgress:
		ui->m_lpProgress->setChecked(true);
		break;
	case cMovie::StateDone:
		ui->m_lpDone->setChecked(true);
		break;
	default:
		break;
	}

	if(!m_lpMovie->backdropPath().isEmpty())
	{
		cMovieImage	image;
		QPixmap	banner	= image.getImage(m_lpMovie->backdropPath());
		ui->m_lpDetailsBanner->setPixmap(banner);
	}

	ui->m_lpDetailsOverview->setText(m_lpMovie->overview());

	QTreeWidgetItem*	lpItem;
	for(int x = 0;x < m_lpMovie->cast().count();x++)
	{
		QStringList	str	= m_lpMovie->cast().at(x).split(",");
		lpItem	= new QTreeWidgetItem(ui->m_lpDetailsActors);
		lpItem->setText(0, str.at(0));
		lpItem->setText(1, str.at(1));
		ui->m_lpDetailsActors->addTopLevelItem(lpItem);
	}
	ui->m_lpDetailsActors->resizeColumnToContents(0);
	for(int x = 0;x < m_lpMovie->genres().count();x++)
	{
		lpItem	= new QTreeWidgetItem(ui->m_lpDetailsGenre);
		lpItem->setText(0, m_lpMovie->genres().at(x));
		ui->m_lpDetailsGenre->addTopLevelItem(lpItem);
	}
	ui->m_lpDetailsGenre->resizeColumnToContents(0);
}

void cMovieEdit::on_m_lpInit_clicked()
{
	m_lpMovie->setState(cMovie::StateInit);
}

void cMovieEdit::on_m_lpProgress_clicked()
{
	m_lpMovie->setState(cMovie::StateProgress);
}

void cMovieEdit::on_m_lpDone_clicked()
{
	m_lpMovie->setState(cMovie::StateDone);
}
