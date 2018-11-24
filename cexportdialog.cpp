#include "cexportdialog.h"
#include "ui_cexportdialog.h"

#include <QSettings>
#include <QDir>
#include <QFileDialog>


cExportDialog::cExportDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cExportDialog)
{
	ui->setupUi(this);

	QSettings			settings;
	QString				szExportSerie	= settings.value("exportSeriePath", QString("%1%2series.xml").arg(QDir::homePath()).arg(QDir::separator())).toString();
	QString				szExportMovie	= settings.value("exportMoviePath", QString("%1%2movies.xml").arg(QDir::homePath()).arg(QDir::separator())).toString();
	bool				bExportSerie	= settings.value("exportSerie", QDir::homePath()).toBool();
	bool				bExportMovie	= settings.value("exportMovie", QDir::homePath()).toBool();

	ui->m_lpExportSeries->setChecked(bExportSerie);
	ui->m_lpExportMovies->setChecked(bExportMovie);
	ui->m_lpSeriesPath->setText(szExportSerie);
	ui->m_lpMoviesPath->setText(szExportMovie);
}

cExportDialog::~cExportDialog()
{
	delete ui;
}

void cExportDialog::on_m_lpSeriesPathSelect_clicked()
{
	QString				szFile	= QFileDialog::getSaveFileName(this, tr("export Serie"), ui->m_lpSeriesPath->text(), tr("XML Files (*.xml)"));

	if(szFile.isEmpty())
			return;

	ui->m_lpSeriesPath->setText(szFile);
}

void cExportDialog::on_m_lpMoviesPathSelect_clicked()
{
	QString				szFile	= QFileDialog::getSaveFileName(this, tr("export Serie"), ui->m_lpMoviesPath->text(), tr("XML Files (*.xml)"));

	if(szFile.isEmpty())
			return;

	ui->m_lpMoviesPath->setText(szFile);
}

void cExportDialog::values(bool& bSeries, QString& szSeriesPath, bool& bMovies, QString& szMoviesPath)
{
	bSeries			= ui->m_lpExportSeries->checkState() == Qt::Checked;
	szSeriesPath	= ui->m_lpSeriesPath->text();
	bMovies			= ui->m_lpExportMovies->checkState() == Qt::Checked;
	szMoviesPath	= ui->m_lpMoviesPath->text();
}
