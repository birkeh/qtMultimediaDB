#include "cmovieedit.h"
#include "cmovieimage.h"

#include "ui_cmovieedit.h"

#include <QSqlQuery>


cMovieEdit::cMovieEdit(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cMovieEdit),
	m_lpMovie(nullptr),
	m_lpActorsModel(nullptr),
	m_lpGenreModel(nullptr)
{
	ui->setupUi(this);

	QSqlQuery	query;

	query.prepare("SELECT resolution FROM resolution ORDER BY sort;");
	if(query.exec())
	{
		while(query.next())
			ui->m_lpResolution->addItem(query.value("resolution").toString());
	}

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
	ui->m_lpLocalPath->setText(lpMovie->localPath());
	ui->m_lpResolution->setCurrentText(lpMovie->resolution());

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

void cMovieEdit::on_buttonBox_accepted()
{
	m_lpMovie->setLocalPath(ui->m_lpLocalPath->text());
	m_lpMovie->setResolution(ui->m_lpResolution->currentText());

	if(ui->m_lpInit->isChecked())
		m_lpMovie->setState(cMovie::StateInit);
	else if(ui->m_lpProgress->isChecked())
		m_lpMovie->setState(cMovie::StateProgress);
	else
		m_lpMovie->setState(cMovie::StateDone);
}
