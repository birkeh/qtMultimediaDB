#ifndef CUPDATETHREAD_H
#define CUPDATETHREAD_H


#include "cmessagedialog.h"

#include "cserie.h"

#include <QThread>
#include <QMutexLocker>
#include <QList>
#include <QStandardItem>
#include <QSqlDatabase>


class cUpdateThread : public QThread
{
	Q_OBJECT

public:
	explicit				cUpdateThread();

	void					setData(cMessageDialog *lpMessageDialog, const cSerieList& serieList, const QSqlDatabase& db);
public slots:
	void					stop();

signals:
	void					updateMessage(const QString& szMessage, const qint32 &iProgress);
	void					updateAppendMessage(const QString& szMessage);

private:
	QMutex					m_mutex;
	bool					m_bStop;
	cSerieList				m_serieList;
	QSqlDatabase			m_db;
	QWidget*				m_lpParent;

	void					run();
};

#endif // CUPDATETHREAD_H
