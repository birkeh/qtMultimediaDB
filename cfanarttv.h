#ifndef CFANARTTV_H
#define CFANARTTV_H


#include "cfanart.h"

#include <QString>


class cFanartTV
{
public:
	cFanartTV();

	cFanartList loadFanartSerie(const qint32 &iID);
	cFanartList loadFanartMovie(const QString& szIMDBID);
private:
	QString		m_szAPIKey;

	void		processArray(const QJsonArray& array, cFanartList& fanartList, cFanart::Type type);
};

#endif // CFANARTTV_H
