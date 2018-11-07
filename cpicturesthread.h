#ifndef CPICTURESTHREAD_H
#define CPICTURESTHREAD_H


#include "cmessagedialog.h"
#include "cserie.h"

#include <QThread>
#include <QMutexLocker>
#include <QList>


/*!
 \brief

 \class cPicturesThread cpicturesthread.h "cpicturesthread.h"
*/
class cPicturesThread : public QThread
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cPicturesThread
	*/
	explicit				cPicturesThread();

	/*!
	 \brief

	 \fn setData
	 \param lpMessageDialog
	 \param list
	*/
	void					setData(cMessageDialog *lpMessageDialog, const QList<cSerie*>& list);
public slots:
	/*!
	 \brief

	 \fn stop
	*/
	void					stop();

signals:
	/*!
	 \brief

	 \fn picturesMessage
	 \param szMessage
	 \param iProgress
	*/
	void					picturesMessage(const QString& szMessage, const qint32 &iProgress);
	/*!
	 \brief

	 \fn picturesAppendMessage
	 \param szMessage
	*/
	void					picturesAppendMessage(const QString& szMessage);

private:
	QMutex					m_mutex; /*!< TODO: describe */
	bool					m_bStop; /*!< TODO: describe */
	QList<cSerie*>			m_items; /*!< TODO: describe */
	QWidget*				m_lpParent; /*!< TODO: describe */

	/*!
	 \brief

	 \fn run
	*/
	void					run();
};

#endif // CPICTURESTHREAD_H
