#include "common.h"

#include <QSettings>
#include <QDir>


QString	rootPath()
{
	QSettings	settings;
	QString		szPath	= settings.value("database", QVariant::fromValue(QString("%HOME%"))).toString();

	if(!szPath.compare("%HOME%") || szPath.isEmpty())
	{
		QDir		dir;
		szPath	= QDir::homePath() + QDir::separator() + "qtmovies";
	}

	return(szPath);
}

QStringList	cleanList(const QStringList& list)
{
	QStringList	list1;

	for(int x = 0;x < list.count();x++)
	{
		if(!list.at(x).isEmpty())
			list1.append(list.at(x));
	}
	return(list1);
}
