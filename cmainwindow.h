#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cserie.h"
#include "cmovie.h"

//#include "cupdatethread.h"
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

/*!
 \brief

 \class cMainWindow cmainwindow.h "cmainwindow.h"
*/
class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cMainWindow
	 \param parent
	*/
	explicit cMainWindow(QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cMainWindow
	*/
	~cMainWindow();

	/*!
	 \brief

	 \fn initDone
	*/
	void				initDone();
private slots:
	/*!
	 \brief

	 \fn on_m_lpSeriesList1_customContextMenuRequested
	 \param pos
	*/
	void				on_m_lpSeriesList1_customContextMenuRequested(const QPoint &pos);
	/*!
	 \brief

	 \fn on_m_lpSeriesList1_doubleClicked
	 \param index
	*/
	void				on_m_lpSeriesList1_doubleClicked(const QModelIndex &index);
	/*!
	 \brief

	 \fn on_m_lpSeriesList1_pressed
	 \param index
	*/
	void				on_m_lpSeriesList1_pressed(const QModelIndex &index);

	/*!
	 \brief

	 \fn on_m_lpSeriesList2_customContextMenuRequested
	 \param pos
	*/
	void				on_m_lpSeriesList2_customContextMenuRequested(const QPoint &pos);
	/*!
	 \brief

	 \fn on_m_lpSeriesList2_doubleClicked
	 \param index
	*/
	void				on_m_lpSeriesList2_doubleClicked(const QModelIndex &index);
	/*!
	 \brief

	 \fn on_m_lpSeriesList2_pressed
	 \param index
	*/
	void				on_m_lpSeriesList2_pressed(const QModelIndex &index);

	/*!
	 \brief

	 \fn on_m_lpMoviesList_customContextMenuRequested
	 \param pos
	*/
	void				on_m_lpMoviesList_customContextMenuRequested(const QPoint &pos);
	/*!
	 \brief

	 \fn on_m_lpMoviesList_doubleClicked
	 \param index
	*/
	void				on_m_lpMoviesList_doubleClicked(const QModelIndex &index);

	/*!
	 \brief

	 \fn onActionAdd
	*/
	void				onActionAdd();
	/*!
	 \brief

	 \fn onActionUpdateAll
	*/
	void				onActionUpdateAll();
	/*!
	 \brief

	 \fn onActionUpdateUnfinished
	*/
	void				onActionUpdateUnfinished();
	/*!
	 \brief

	 \fn onActionUpdate
	*/
	void				onActionUpdate();
	/*!
	 \brief

	 \fn onActionDelete
	*/
	void				onActionDelete();
	/*!
	 \brief

	 \fn onActionEdit
	*/
	void				onActionEdit();
	/*!
	 \brief

	 \fn onActionGotoDownload
	*/
	void				onActionGotoDownload();
	/*!
	 \brief

	 \fn onActionCopyDownload
	*/
	void				onActionCopyDownload();
	/*!
	 \brief

	 \fn onActionGotoIMDB
	*/
	void				onActionGotoIMDB();
	/*!
	 \brief

	 \fn onActionLoadPictures
	*/
	void				onActionLoadPictures();
	/*!
	 \brief

	 \fn onActionFind
	*/
	void				onActionFind();
	/*!
	 \brief

	 \fn onActionFindAgain
	*/
	void				onActionFindAgain();
	/*!
	 \brief

	 \fn onActionDiscover
	*/
	void				onActionDiscover();

	/*!
	 \brief

	 \fn onActionGotoAllDownload
	*/
	void				onActionGotoAllDownload();
	/*!
	 \brief

	 \fn onActionGotoAllDownloadOpen
	*/
	void				onActionGotoAllDownloadOpen();

	/*!
	 \brief

	 \fn onActionMovieAdd
	*/
	void				onActionMovieAdd();
	/*!
	 \brief

	 \fn onActionMovieUpdateAll
	*/
	void				onActionMovieUpdateAll();
	/*!
	 \brief

	 \fn onActionMovieUpdate
	*/
	void				onActionMovieUpdate();
	/*!
	 \brief

	 \fn onActionMovieDelete
	*/
	void				onActionMovieDelete();
	/*!
	 \brief

	 \fn onActionMovieEdit
	*/
	void				onActionMovieEdit();
	/*!
	 \brief

	 \fn onActionMovieGotoIMDB
	*/
	void				onActionMovieGotoIMDB();
	/*!
	 \brief

	 \fn onActionMovieLoadPictures
	*/
	void				onActionMovieLoadPictures();
	/*!
	 \brief

	 \fn onActionMovieFind
	*/
	void				onActionMovieFind();
	/*!
	 \brief

	 \fn onActionMovieFindAgain
	*/
	void				onActionMovieFindAgain();
	/*!
	 \brief

	 \fn onActionMovieDiscover
	*/
	void				onActionMovieDiscover();
	/*!
	 \brief

	 \fn onActionExport
	*/
	void				onActionExport();
	/*!
	 \brief

	 \fn onActionPreferences
	*/
	void				onActionPreferences();

	/*!
	 \brief

	 \fn onActionAddGlobal
	*/
	void				onActionAddGlobal();
	/*!
	 \brief

	 \fn onActionFindGlobal
	*/
	void				onActionFindGlobal();
	/*!
	 \brief

	 \fn onActionFindAgainGlobal
	*/
	void				onActionFindAgainGlobal();

	/*!
	 \brief

	 \fn updateMessage
	 \param szMessage
	 \param iProgress
	*/
	void				updateMessage(const QString& szMessage, const qint32 &iProgress);
	/*!
	 \brief

	 \fn updateAppendMessage
	 \param szMessage
	*/
	void				updateAppendMessage(const QString& szMessage);
	/*!
	 \brief

	 \fn updateDone
	*/
	void				updateDone();

	/*!
	 \brief

	 \fn picturesMessage
	 \param szMessage
	 \param iProgress
	*/
	void				picturesMessage(const QString& szMessage, const qint32 &iProgress);
	/*!
	 \brief

	 \fn picturesAppendMessage
	 \param szMessage
	*/
	void				picturesAppendMessage(const QString& szMessage);
	/*!
	 \brief

	 \fn picturesDone
	*/
	void				picturesDone();

	/*!
	 \brief

	 \fn selectionChanged1
	 \param selected
	 \param deselected
	*/
	void				selectionChanged1(const QItemSelection &selected, const QItemSelection &deselected);
	/*!
	 \brief

	 \fn selectionChanged2
	 \param selected
	 \param deselected
	*/
	void				selectionChanged2(const QItemSelection &selected, const QItemSelection &deselected);

	/*!
	 \brief

	 \fn scrollbarValueChanged1
	 \param value
	*/
	void				scrollbarValueChanged1(int value);
	/*!
	 \brief

	 \fn scrollbarValueChanged2
	 \param value
	*/
	void				scrollbarValueChanged2(int value);

	/*!
	 \brief

	 \fn on_m_lpSeriesFilterInitialized_clicked
	*/
	void				on_m_lpSeriesFilterInitialized_clicked();
	/*!
	 \brief

	 \fn on_m_lpSeriesFilterProgress_clicked
	*/
	void				on_m_lpSeriesFilterProgress_clicked();
	/*!
	 \brief

	 \fn on_m_lpSeriesFilterDone_clicked
	*/
	void				on_m_lpSeriesFilterDone_clicked();
	/*!
	 \brief

	 \fn on_m_lpSeriesFilterWithLink_clicked
	*/
	void				on_m_lpSeriesFilterWithLink_clicked();
	/*!
	 \brief

	 \fn on_m_lpSeriesFilterCliffhanger_clicked
	*/
	void				on_m_lpSeriesFilterCliffhanger_clicked();
	/*!
	 \brief

	 \fn on_m_lpSeriesFilterNotFinished_clicked
	*/
	void				on_m_lpSeriesFilterNotFinished_clicked();
	/*!
	 \brief

	 \fn on_m_lpMoviesFilterInitialized_clicked
	*/
	void				on_m_lpMoviesFilterInitialized_clicked();
	/*!
	 \brief

	 \fn on_m_lpMoviesFilterProgress_clicked
	*/
	void				on_m_lpMoviesFilterProgress_clicked();
	/*!
	 \brief

	 \fn on_m_lpMoviesFilterDone_clicked
	*/
	void				on_m_lpMoviesFilterDone_clicked();

	/*!
	 \brief

	 \fn on_m_lpSeriesFilter_clicked
	*/
	void				on_m_lpSeriesFilter_clicked();
	/*!
	 \brief

	 \fn on_m_lpMoviesFilter_clicked
	*/
	void				on_m_lpMoviesFilter_clicked();

	/*!
	 \brief

	 \fn onActionExit
	*/
	void				onActionExit();

private:
	Ui::cMainWindow*	ui; /*!< TODO: describe */
	cSerieList			m_serieList; /*!< TODO: describe */
	cMovieList			m_movieList; /*!< TODO: describe */
	QSqlDatabase		m_db; /*!< TODO: describe */

	QString				m_szOldSelected; /*!< TODO: describe */

	cMessageDialog*		m_lpMessageDialog; /*!< TODO: describe */
	cPicturesThread*	m_lpPicturesThread; /*!< TODO: describe */

	QStandardItemModel*	m_lpSeriesListModel; /*!< TODO: describe */
	QStandardItemModel*	m_lpMoviesListModel; /*!< TODO: describe */

	bool				m_bProcessing; /*!< TODO: describe */

	QShortcut*			m_lpShortcutAdd; /*!< TODO: describe */
	QShortcut*			m_lpShortcutFind; /*!< TODO: describe */
	QShortcut*			m_lpShortcutFindAgain; /*!< TODO: describe */

	QString				m_szFind; /*!< TODO: describe */
	QString				m_szFindMovie; /*!< TODO: describe */

	QMenu*				m_lpFileMenu; /*!< TODO: describe */
	QAction*			m_lpFileExportAction; /*!< TODO: describe */
	QAction*			m_lpFilePreferencesAction; /*!< TODO: describe */
	QAction*			m_lpFileExitAction; /*!< TODO: describe */

	/*!
	 \brief

	 \fn initDB
	*/
	void				initDB();
	/*!
	 \brief

	 \fn loadDB
	*/
	void				loadDB();

	/*!
	 \brief

	 \fn loadSeriesDB
	*/
	void				loadSeriesDB();
	/*!
	 \brief

	 \fn loadMoviesDB
	*/
	void				loadMoviesDB();

	/*!
	 \brief

	 \fn displaySeries
	*/
	void				displaySeries();
	/*!
	 \brief

	 \fn displayMovies
	*/
	void				displayMovies();

	/*!
	 \brief

	 \fn runEdit
	 \param lpSerie
	 \param szDownload
	 \return bool
	*/
	bool				runEdit(cSerie *lpSerie, QString& szDownload);
	/*!
	 \brief

	 \fn runMovieEdit
	 \param lpMovie
	 \return bool
	*/
	bool				runMovieEdit(cMovie *lpMovie);

	/*!
	 \brief

	 \fn showSeriesContextMenu
	 \param lpTreeView
	 \param pos
	*/
	void				showSeriesContextMenu(QTreeView* lpTreeView, const QPoint &pos);
	/*!
	 \brief

	 \fn doUpdate
	 \param serieList
	*/
	void				doUpdate(cSerieList& serieList);

	/*!
	 \brief

	 \fn showMoviesContextMenu
	 \param lpTreeView
	 \param pos
	*/
	void				showMoviesContextMenu(QTreeView* lpTreeView, const QPoint &pos);

	/*!
	 \brief

	 \fn setSeriesStyle
	 \param lpItems
	*/
	void				setSeriesStyle(QList<QStandardItem *> lpItems);
	/*!
	 \brief

	 \fn setMovieStyle
	 \param lpItem
	*/
	void				setMovieStyle(QStandardItem* lpItem);

	/*!
	 \brief

	 \fn applySeriesFilter
	*/
	void				applySeriesFilter();
	/*!
	 \brief

	 \fn applyMoviesFilter
	*/
	void				applyMoviesFilter();
	/*!
	 \brief

	 \fn applyMoviesFilter
	 \param i
	 \param lpMovie
	 \return bool
	*/
	bool				applyMoviesFilter(qint32 i, cMovie* lpMovie);
	/*!
	 \brief

	 \fn applyMoviesFilter
	 \param lpParent
	*/
	void				applyMoviesFilter(QStandardItem* lpParent);

	/*!
	 \brief

	 \fn checkState
	 \param state
	 \param bDesiredState
	 \return bool
	*/
	bool				checkState(const Qt::CheckState &state, bool bDesiredState);

	/*!
	 \brief

	 \fn find
	*/
	void				find();
	/*!
	 \brief

	 \fn findMovie
	*/
	void				findMovie();
protected:
	/*!
	 \brief

	 \fn closeEvent
	 \param event
	*/
	void				closeEvent(QCloseEvent *event);
};

#endif // CMAINWINDOW_H
