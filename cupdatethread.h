#ifndef CUPDATETHREAD_H
#define CUPDATETHREAD_H


#include "cmessagedialog.h"

#include "cserie.h"

#include <QThread>
#include <QMutexLocker>
#include <QList>
#include <QStandardItem>
#include <QSqlDatabase>


/*!
 \brief

 \class cUpdateThread cupdatethread.h "cupdatethread.h"
*/
class cUpdateThread : public QThread
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cUpdateThread
	*/
	explicit				cUpdateThread();

	/*!
	 \brief

	 \fn setData
	 \param lpMessageDialog
	 \param serieList
	 \param db
	*/
	void					setData(cMessageDialog *lpMessageDialog, const cSerieList& serieList, const QSqlDatabase& db);
public slots:
	/*!
	 \brief

	 \fn stop
	*/
	void					stop();

signals:
	/*!
	 \brief

	 \fn updateMessage
	 \param szMessage
	 \param iProgress
	*/
	void					updateMessage(const QString& szMessage, const qint32 &iProgress);
	/*!
	 \brief

	 \fn updateAppendMessage
	 \param szMessage
	*/
	void					updateAppendMessage(const QString& szMessage);

private:
	QMutex					m_mutex; /*!< TODO: describe */
	bool					m_bStop; /*!< TODO: describe */
	cSerieList				m_serieList; /*!< TODO: describe */
	QSqlDatabase			m_db; /*!< TODO: describe */
	QWidget*				m_lpParent; /*!< TODO: describe */

	/*!
	 \brief

	 \fn run
	*/
	void					run();
};

#endif // CUPDATETHREAD_H
