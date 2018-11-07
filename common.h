#ifndef COMMON_H
#define COMMON_H


#include <QString>


/*!
 \brief

 \fn rootPath
 \return QString
*/
QString	rootPath();
/*!
 \brief

 \fn cleanList
 \param list
 \return QStringList
*/
QStringList	cleanList(const QStringList& list);


#endif // COMMON_H
