#include "csearch.h"
#include "ui_csearch.h"

#include "cthemoviedbv3.h"

#include "cserie.h"
#include "cmessageanimatedialog.h"

#include <QList>


cSearch::cSearch(const cSerieList& serieList, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cSearch),
	m_lpResultsModel(nullptr),
	m_serieList(serieList)
{
	ui->setupUi(this);
	ui->m_lpSearchButton->setEnabled(false);
	ui->m_lpTabWidget->setCurrentIndex(0);

	ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	ui->m_lpSearch->setFocus();
	ui->m_lpSearchButton->setDefault(true);

	m_lpResultsModel	= new QStandardItemModel(0, 0);
	ui->m_lpResults->setModel(m_lpResultsModel);
}

cSearch::~cSearch()
{
	delete m_lpResultsModel;
	delete ui;
}

void cSearch::on_m_lpSearch_textChanged(const QString& /*arg1*/)
{
	if(ui->m_lpSearch->text().isEmpty())
		ui->m_lpSearchButton->setEnabled(false);
	else
		ui->m_lpSearchButton->setEnabled(true);
}

void cSearch::on_m_lpSearchButton_clicked()
{
	setCursor(Qt::WaitCursor);

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Search");
	lpDialog->setMessage("Searching");
	lpDialog->show();

	cTheMovieDBV3		theMovieDBV3;

	QList<cSerie*>		serieList3	= theMovieDBV3.searchSerie(m_serieList, ui->m_lpSearch->text(), -1, "de-DE");

	m_lpResultsModel->clear();

	for(int z = 0;z < serieList3.count();z++)
	{
		cSerie*	lpSerie	= serieList3.at(z);

		QList<QStandardItem*>	items;

		items.append(new QStandardItem(lpSerie->seriesName()));
		items.append(new QStandardItem(QString::number(lpSerie->firstAired().year())));
		items[0]->setData(QVariant::fromValue(lpSerie));
		items[1]->setData(QVariant::fromValue(lpSerie));

		m_lpResultsModel->appendRow(items);
	}
	ui->m_lpResults->resizeColumnToContents(0);
	ui->m_lpResults->resizeColumnToContents(1);

	m_lpResultsModel->sort(0);

	delete lpDialog;

	setCursor(Qt::ArrowCursor);
}

qint32 cSearch::id()
{
	if(!ui->m_lpResults->selectionModel()->selectedRows().count())
	{
		qint32	iID	= ui->m_lpSearch->text().toInt();
		if(iID)
			return(iID);
		return(-1);
	}

	QStandardItem*	lpItem	= m_lpResultsModel->itemFromIndex(ui->m_lpResults->selectionModel()->selectedRows().at(0));
	cSerie*			lpSerie	= lpItem->data().value<cSerie*>();
	return(lpSerie->seriesID());
}

QString cSearch::placeholderName()
{
	return(ui->m_lpPlaceholderName->text());
}

bool cSearch::placeholder()
{
	return(ui->m_lpTabWidget->currentIndex() == 1);
}

qint32 cSearch::year()
{
	return(ui->m_lpYear->value());
}

void cSearch::on_m_lpResults_clicked(const QModelIndex& index)
{
	setCursor(Qt::WaitCursor);
	QStandardItem*	lpItem	= m_lpResultsModel->itemFromIndex(index);
	cSerie*			lpSerie	= lpItem->data().value<cSerie*>();

	if(lpSerie->cast().isEmpty())
	{
		cTheMovieDBV3	theMovieDB;
		theMovieDB.loadCastSerie(lpSerie);
	}
	ui->m_lpSerieDetails->setSerie(lpSerie);

	setButtonBox();

	setCursor(Qt::ArrowCursor);
}

void cSearch::on_m_lpPlaceholderName_textChanged(const QString& /*arg1*/)
{
	setButtonBox();
}

void cSearch::on_m_lpYear_valueChanged(int /*arg1*/)
{
	setButtonBox();
}

void cSearch::setButtonBox()
{
	if(ui->m_lpTabWidget->currentIndex() == 0)
	{
		if(ui->m_lpResults->selectionModel()->selectedIndexes().count())
			ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
		else
			ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
		return;
	}

	if(ui->m_lpPlaceholderName->text().isEmpty())
	{
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
		return;
	}

	if(ui->m_lpYear->value() == 0)
	{
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
		return;
	}

	ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void cSearch::on_m_lpResults_doubleClicked(const QModelIndex &index)
{
	if(index.isValid())
		accept();
}
