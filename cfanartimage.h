#ifndef CFANARTIMAGE_H
#define CFANARTIMAGE_H


#include <QPixmap>


class cFanartImage
{
public:
	cFanartImage();
	QPixmap	getImage(const QString& szFileName);
private:
	QPixmap	downloadFile(const QString& szFileName);
};

#endif // CFANARTIMAGE_H
