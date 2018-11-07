#include "cmovieedit.h"
#include "cmovieimage.h"

#include "ui_cmovieedit.h"


cMovieEdit::cMovieEdit(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cMovieEdit),
	m_lpMovie(0),
	m_lpActorsModel(0),
	m_lpGenreModel(0)
{
	ui->setupUi(this);

	m_lpActorsModel	= new QStandardItemModel(0, 0);
	ui->m_lpDetailsActors->setModel(m_lpActorsModel);

	m_lpGenreModel	= new QStandardItemModel(0, 0);
	ui->m_lpDetailsGenre->setModel(m_lpGenreModel);
}

cMovieEdit::~cMovieEdit()
{
	delete m_lpActorsModel;
	delete m_lpGenreModel;

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

	for(int x = 0;x < m_lpMovie->cast().count();x++)
	{
		QList<QStandardItem*>	items;
		QStringList				str	= m_lpMovie->cast().at(x).split(",");

		items.append(new QStandardItem(str.at(0)));
		items.append(new QStandardItem(str.at(1)));
		m_lpActorsModel->appendRow(items);
	}
	ui->m_lpDetailsActors->resizeColumnToContents(0);
	for(int x = 0;x < m_lpMovie->genres().count();x++)
		m_lpGenreModel->appendRow(new QStandardItem(m_lpMovie->genres().at(x)));

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
