#ifndef CMOVIEIMAGE_H
#define CMOVIEIMAGE_H


#include <QPixmap>


class cMovieImage
{
public:
	cMovieImage();
	QPixmap	getImage(const QString& szFileName);
private:
	QPixmap	downloadFile(const QString& szFileName);
};

#endif // CMOVIEIMAGE_H
