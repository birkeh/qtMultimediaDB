#include "cedit.h"
#include "ui_cedit.h"

#include "cmovieimage.h"
#include "cfanartimage.h"

#include "cseasondetails.h"
#include "cmessageanimatedialog.h"

#include <QRadioButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLineEdit>
#include <QScrollArea>
#include <QDialogButtonBox>
#include <QLabel>
#include <QButtonGroup>

#include <QDebug>
#include <QTime>


cEdit::cEdit(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cEdit),
	m_bLoaded(false),
	m_lpButton1(nullptr),
	m_lpButton2(nullptr),
	m_lpButton3(nullptr),
	m_lpInit(nullptr),
	m_lpProgress(nullptr),
	m_lpDone(nullptr),
	m_lpGroupBox(nullptr),
	m_lpGridLayout(nullptr),
	m_lpGrid(nullptr),
	m_lpLabel(nullptr),
	m_lpLabel1(nullptr),
	m_lpSpacer(nullptr),
	m_lpGroup(nullptr),
	m_lpAllInit(nullptr),
	m_lpAllProgress(nullptr),
	m_lpAllDone(nullptr),
	m_lpVerticalSpacer(nullptr),
	m_lpDetailsActorsModel(nullptr),
	m_lpDetailsGenreModel(nullptr),
	m_lpSerie(nullptr)
{
	ui->setupUi(this);

	QPalette	palette	= ui->m_lpDownloadLinkLabel->palette();
	QColor		col		= palette.color(QPalette::Window);
	QString		color	= QString("background-color: rgb(%1,%2,%3,%4);").arg(col.red()).arg(col.green()).arg(col.blue()).arg(95);
	ui->m_lpScrollArea->setStyleSheet(color);

	m_lpDetailsActorsModel	= new QStandardItemModel(0, 0);
	ui->m_lpDetailsActors->setModel(m_lpDetailsActorsModel);

	m_lpDetailsGenreModel	= new QStandardItemModel(0, 0);
	ui->m_lpDetailsGenre->setModel(m_lpDetailsGenreModel);

	connect(ui->m_lpAllInit, SIGNAL(clicked()), this, SLOT(lpAllInit_clicked()));
	connect(ui->m_lpAllProgress, SIGNAL(clicked()), this, SLOT(lpAllProgress_clicked()));
	connect(ui->m_lpAllDone, SIGNAL(clicked()), this, SLOT(lpAllDone_clicked()));

	ui->m_lpTabWidget->setCurrentIndex(0);
}

cEdit::~cEdit()
{
	if(m_lpSerie)
	{
		int	x;
		QList<cSeason*>	seasonList	= m_lpSerie->seasonList();
		for(x = 0;x < seasonList.count();x++)
		{
			cSeason*	lpSeason	= seasonList.at(x);

			QList<cEpisode*>	episodeList	= lpSeason->episodeList();
			for(int y = 0;y < episodeList.count();y++)
			{
				cEpisode*	lpEpisode	= episodeList.at(y);
				if(lpEpisode)
				{
					lpEpisode->setButton1(0);
					lpEpisode->setButton2(0);
					lpEpisode->setButton3(0);
				}
			}
		}
	}

	delete m_lpDetailsActorsModel;
	delete m_lpDetailsGenreModel;

	delete ui;
}

void cEdit::setSerie(cSerie* lpSerie)
{
	m_lpSerie	= lpSerie;

	if(!lpSerie)
		return;
	ui->m_lpName->setText(lpSerie->seriesName());
    ui->m_lpFirstAired->setDate(lpSerie->firstAired());
	ui->m_lpCliffhanger->setChecked(lpSerie->cliffhanger());
	ui->m_lpDownloadLink->setText(lpSerie->download());
	ui->m_lpLocalPath->setText(lpSerie->localPath());
	ui->m_lpResolution->setText(lpSerie->resolution());

	QString			szBanner	= lpSerie->fanartBanner();
	{
		if(!szBanner.isEmpty())
		{
			cFanartImage	banner;
			QPixmap			pixmap		= banner.getImage(szBanner);
			if(!pixmap.isNull())
				ui->m_lpBanner->setPixmap(pixmap);
		}
	}

	int	x;
	QList<cSeason*>	seasonList	= lpSerie->seasonList();
	for(x = 0;x < seasonList.count();x++)
	{
		cSeason*	lpSeason	= seasonList.at(x);

		m_lpGroupBox	= new QGroupBox(QString("Season %1").arg(lpSeason->seasonNumber()), ui->m_lpScrollAreaWidget);
		lpSeason->setGroupBox(m_lpGroupBox);
		m_lpGridLayout	= new QGridLayout(m_lpGroupBox);
		lpSeason->setGridLayout(m_lpGridLayout);
		m_lpGrid		= new QGridLayout();
		lpSeason->setGrid(m_lpGrid);

		m_lpLabel1		= new QLabel("Episode");
		lpSeason->setLabel1(m_lpLabel1);
		m_lpAllInit		= new QPushButton("all Init");
		lpSeason->setAllInit(m_lpAllInit);
		m_lpAllProgress	= new QPushButton("all Prog");
		lpSeason->setAllProgress(m_lpAllProgress);
		m_lpAllDone		= new QPushButton("all Done");
		lpSeason->setAllDone(m_lpAllDone);

		connect(m_lpAllInit, SIGNAL(clicked()), this, SLOT(allInit_clicked()));
		connect(m_lpAllProgress, SIGNAL(clicked()), this, SLOT(allProgress_clicked()));
		connect(m_lpAllDone, SIGNAL(clicked()), this, SLOT(allDone_clicked()));

		m_lpGrid->addWidget(m_lpLabel1, 0, 0, 1, 1);
		m_lpGrid->addWidget(m_lpAllInit, 1, 0, 1, 1);
		m_lpGrid->addWidget(m_lpAllProgress, 2, 0, 1, 1);
		m_lpGrid->addWidget(m_lpAllDone, 3, 0, 1, 1);

		bool				bFirst		= true;
		QList<cEpisode*>	episodeList	= lpSeason->episodeList();
		for(int y = 0;y < episodeList.count();y++)
		{
			cEpisode*	lpEpisode	= episodeList.at(y);

			m_lpGroup	= new QButtonGroup(this);
			lpEpisode->setGroup(m_lpGroup);
			m_lpLabel	= new QLabel(QString("%1").arg(lpEpisode->episodeNumber()), m_lpGroupBox);

			lpEpisode->setLabel(m_lpLabel);

			if(bFirst)
			{
				m_lpButton1	= new QRadioButton("init", m_lpGroupBox);
				m_lpButton2	= new QRadioButton("prog", m_lpGroupBox);
				m_lpButton3	= new QRadioButton("done", m_lpGroupBox);
				bFirst = false;
			}
			else
			{
				m_lpButton1	= new QRadioButton(m_lpGroupBox);
				m_lpButton2	= new QRadioButton(m_lpGroupBox);
				m_lpButton3	= new QRadioButton(m_lpGroupBox);
			}
			lpEpisode->setButton1(m_lpButton1);
			lpEpisode->setButton2(m_lpButton2);
			lpEpisode->setButton3(m_lpButton3);

			m_lpLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

			m_lpButton1->setLayoutDirection(Qt::RightToLeft);
			m_lpButton2->setLayoutDirection(Qt::RightToLeft);
			m_lpButton3->setLayoutDirection(Qt::RightToLeft);

			switch(lpEpisode->state())
			{
			case cEpisode::StateInit:
				m_lpButton1->setChecked(true);
				break;
			case cEpisode::StateProgress:
				m_lpButton2->setChecked(true);
				break;
			case cEpisode::StateDone:
				m_lpButton3->setChecked(true);
				break;
			default:
				break;
			}

			m_lpGroup->addButton(m_lpButton1);
			m_lpGroup->addButton(m_lpButton2);
			m_lpGroup->addButton(m_lpButton3);

			m_lpGrid->addWidget(m_lpLabel, 0, y+1, 1, 1);
			m_lpGrid->addWidget(m_lpButton1, 1, y+1, 1, 1);
			m_lpGrid->addWidget(m_lpButton2, 2, y+1, 1, 1);
			m_lpGrid->addWidget(m_lpButton3, 3, y+1, 1, 1);
		}
		m_lpGridLayout->addLayout(m_lpGrid, 0, 0, 1, 1);
		m_lpSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		lpSeason->setSpacer(m_lpSpacer);
		m_lpGridLayout->addItem(m_lpSpacer, 0, 1, 1, 1);
		ui->m_lpGridLayoutScroll->addWidget(m_lpGroupBox, x, 0, 1, 1);
	}

	m_lpVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	ui->m_lpGridLayoutScroll->addItem(m_lpVerticalSpacer, x+1, 0, 1, 1);

	cMovieImage	image;
	//QPixmap	backdrop	= image.getImage(m_lpSerie->backdropPath());
	QPixmap	poster		= image.getImage(m_lpSerie->posterPath());
	ui->m_lpProgressTab->setPixmap(poster);
}

void cEdit::lpAllInit_clicked()
{
	m_lpSerie->allInit();
}

void cEdit::lpAllProgress_clicked()
{
	m_lpSerie->allProgress();
}

void cEdit::lpAllDone_clicked()
{
	m_lpSerie->allDone();
}

void cEdit::allInit_clicked()
{
	QPushButton*	lpButton	= (QPushButton*)sender();
	m_lpSerie->seasonInit(lpButton);
}

void cEdit::allProgress_clicked()
{
	QPushButton*	lpButton	= (QPushButton*)sender();
	m_lpSerie->seasonProgress(lpButton);
}

void cEdit::allDone_clicked()
{
	QPushButton*	lpButton	= (QPushButton*)sender();
	m_lpSerie->seasonDone(lpButton);
}

QString cEdit::download()
{
	return(ui->m_lpDownloadLink->text());
}

QString cEdit::localPath()
{
	return(ui->m_lpLocalPath->text());
}

QString cEdit::resolution()
{
	return(ui->m_lpResolution->text());
}

void cEdit::on_m_lpTabWidget_tabBarClicked(int index)
{
	if(index == 1)
	{
		if(!m_bLoaded)
		{
			cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
			lpDialog->setTitle("Edit");
			lpDialog->setMessage("Loading");
			lpDialog->show();

			cMovieImage	image;
			QPixmap	poster		= image.getImage(m_lpSerie->posterPath());
			ui->m_lpDetailsImage->setPixmap(poster.scaledToHeight(200));

			ui->m_lpDetailsOverview->setText(m_lpSerie->overview());
			ui->m_lpDetailsSeasonTab->clear();

			for(int x = 0;x < m_lpSerie->cast().count();x++)
			{
				QList<QStandardItem*>	items;
				QStringList	tmp			= m_lpSerie->cast().at(x).split(",");

				items.append(new QStandardItem(tmp.at(0)));
				if(tmp.count() > 1)
					items.append(new QStandardItem(tmp.at(1)));

				m_lpDetailsActorsModel->appendRow(items);
			}
			ui->m_lpDetailsActors->resizeColumnToContents(0);
			ui->m_lpDetailsActors->resizeColumnToContents(1);

			for(int x = 0;x < m_lpSerie->genre().count();x++)
				m_lpDetailsGenreModel->appendRow(new QStandardItem(m_lpSerie->genre().at(x)));
			for(int x = 0;x < m_lpSerie->seasonList().count();x++)
			{
				cSeason*		lpSeason		= m_lpSerie->seasonList().at(x);
				cSeasonDetails*	lpSeasonDetails	= new cSeasonDetails(ui->m_lpDetailsSeasonTab);
				ui->m_lpDetailsSeasonTab->addTab(lpSeasonDetails, QString("Season %1").arg(lpSeason->seasonNumber()));
				lpSeasonDetails->setSeason(lpSeason);
			}

			delete lpDialog;

			m_bLoaded = true;
		}
	}
}

void cEdit::on_m_lpCliffhanger_clicked()
{
	m_lpSerie->setCliffhanger(ui->m_lpCliffhanger->checkState() == Qt::Checked);
}

void cEdit::on_m_lpFirstAired_dateChanged(const QDate &date)
{
    m_lpSerie->setFirstAired(date);
}
