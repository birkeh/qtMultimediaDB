#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cserie.h"
#include "cmovie.h"

#include "cupdatethread.h"
#include "cpicturesthread.h"

#include <QMainWindow>
#include <QList>
#include <QSqlDatabase>

#include <QCloseEvent>

#include <QTime>

#include <QStandardItemModel>
#include <QItemSelection>

#include <QTreeView>

#include <QShortcut>


namespace Ui {
class cMainWindow;
}

class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit cMainWindow(QWidget *parent = 0);
	~cMainWindow();

	void				initDone();
private slots:
	void				on_m_lpSeriesList1_customContextMenuRequested(const QPoint &pos);
	void				on_m_lpSeriesList1_doubleClicked(const QModelIndex &index);
	void				on_m_lpSeriesList1_pressed(const QModelIndex &index);

	void				on_m_lpSeriesList2_customContextMenuRequested(const QPoint &pos);
	void				on_m_lpSeriesList2_doubleClicked(const QModelIndex &index);
	void				on_m_lpSeriesList2_pressed(const QModelIndex &index);

	void				on_m_lpMoviesList_customContextMenuRequested(const QPoint &pos);
	void				on_m_lpMoviesList_doubleClicked(const QModelIndex &index);

	void				onActionAdd();
	void				onActionUpdateAll();
	void				onActionUpdateUnfinished();
	void				onActionUpdate();
	void				onActionDelete();
	void				onActionEdit();
	void				onActionGotoDownload();
	void				onActionCopyDownload();
	void				onActionGotoIMDB();
	void				onActionLoadPictures();

	void				onActionMovieAdd();
	void				onActionMovieUpdateAll();
	void				onActionMovieUpdate();
	void				onActionMovieDelete();
	void				onActionMovieEdit();
	void				onActionMovieGotoIMDB();
	void				onActionMovieLoadPictures();

	void				onActionExport();

	void				onActionAddGlobal();

	void				updateMessage(const QString& szMessage, const qint32 &iProgress);
	void				updateAppendMessage(const QString& szMessage);
	void				updateDone();

	void				picturesMessage(const QString& szMessage, const qint32 &iProgress);
	void				picturesAppendMessage(const QString& szMessage);
	void				picturesDone();

	void				selectionChanged1(const QItemSelection &selected, const QItemSelection &deselected);
	void				selectionChanged2(const QItemSelection &selected, const QItemSelection &deselected);

	void				scrollbarValueChanged1(int value);
	void				scrollbarValueChanged2(int value);

private:
	Ui::cMainWindow*	ui;
	cSerieList			m_serieList;
	cMovieList			m_movieList;
	QSqlDatabase		m_db;

	QString				m_szOldSelected;

	cMessageDialog*		m_lpMessageDialog;
	cUpdateThread*		m_lpUpdateThread;
	cPicturesThread*	m_lpPicturesThread;

	QTime				m_timer;

	QStandardItemModel*	m_lpSeriesListModel;
	QStandardItemModel*	m_lpMoviesListModel;

	bool				m_bProcessing;

	QShortcut*			m_lpShortcut;

	void				initDB();
	void				loadDB();

	void				convertSeries();

	void				loadSeriesDB();
	void				loadMoviesDB();

	void				displaySeries();
	void				displayMovies();

	bool				runEdit(cSerie *lpSerie, QString& szDownload);
	bool				runMovieEdit(cMovie *lpMovie);

	void				showSeriesContextMenu(QTreeView* lpTreeView, const QPoint &pos);
	void				doUpdate(cSerieList& serieList);

	void				showMoviesContextMenu(QTreeView* lpTreeView, const QPoint &pos);

	void				setSeriesStyle(QList<QStandardItem *> lpItems);

protected:
	void				closeEvent(QCloseEvent *event);
};

#endif // CMAINWINDOW_H
