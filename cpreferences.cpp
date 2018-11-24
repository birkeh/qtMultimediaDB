#include "cpreferences.h"
#include "ui_cpreferences.h"

#include <QSettings>
#include <QDir>
#include <QFileDialog>


cPreferences::cPreferences(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cPreferences)
{
	ui->setupUi(this);

	QSettings	settings;

	ui->m_lpExportSeries->setChecked(settings.value("exportSerie", QDir::homePath()).toBool());
	ui->m_lpExportMovies->setChecked(settings.value("exportMovie", QDir::homePath()).toBool());
	ui->m_lpSeriesPath->setText(settings.value("exportSeriePath", QString("%1%2series.xml").arg(QDir::homePath()).arg(QDir::separator())).toString());
	ui->m_lpMoviesPath->setText(settings.value("exportMoviePath", QString("%1%2movies.xml").arg(QDir::homePath()).arg(QDir::separator())).toString());

	ui->m_lpDiscoverResultsSerie->setValue(settings.value("serieDiscover/results", 100).toInt());
	ui->m_lpSearchResultsSerie->setValue(settings.value("serieSearch/results", 100).toInt());
	ui->m_lpDiscoverResultsMovie->setValue(settings.value("movieDiscover/results", 100).toInt());
	ui->m_lpSearchResultsMovie->setValue(settings.value("movieSearch/results", 100).toInt());

	ui->m_lpDisplaySeason0->setChecked(settings.value("displaySeason0", true).toBool());

	m_bDisplaySeason0	= settings.value("displaySeason0", true).toBool();
}

cPreferences::~cPreferences()
{
	QSettings			settings;

	settings.setValue("exportSeriePath", ui->m_lpSeriesPath->text());
	settings.setValue("exportMoviePath", ui->m_lpMoviesPath->text());
	settings.setValue("exportSerie", ui->m_lpExportSeries->isChecked());
	settings.setValue("exportMovie", ui->m_lpExportMovies->isChecked());

	settings.setValue("serieDiscover/results", ui->m_lpDiscoverResultsSerie->value());
	settings.setValue("serieSearch/results", ui->m_lpSearchResultsSerie->value());
	settings.setValue("movieDiscover/results", ui->m_lpDiscoverResultsMovie->value());
	settings.setValue("movieSearch/results", ui->m_lpSearchResultsMovie->value());

	settings.setValue("displaySeason0", ui->m_lpDisplaySeason0->isChecked());

	delete ui;
}

bool cPreferences::displaySeason0Changed()
{
	return(m_bDisplaySeason0 != ui->m_lpDisplaySeason0->isChecked());
}

void cPreferences::on_m_lpSeriesPathSelect_clicked()
{
	QString				szFile	= QFileDialog::getSaveFileName(this, tr("export Serie"), ui->m_lpSeriesPath->text(), tr("XML Files (*.xml)"));

	if(szFile.isEmpty())
			return;

	ui->m_lpSeriesPath->setText(szFile);
}

void cPreferences::on_m_lpMoviesPathSelect_clicked()
{
	QString				szFile	= QFileDialog::getSaveFileName(this, tr("export Serie"), ui->m_lpMoviesPath->text(), tr("XML Files (*.xml)"));

	if(szFile.isEmpty())
			return;

	ui->m_lpMoviesPath->setText(szFile);
}
