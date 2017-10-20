#include "cmovieviewitemdelegate.h"

#include "cmovie.h"

#include <QPainter>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QAbstractItemModel>
#include <QStandardItemModel>


#define STATE_INIT		Qt::gray
#define STATE_PROGRESS	Qt::blue
#define STATE_DONE		Qt::green
#define STATE_UNKNOWN	Qt::black

void cMovieViewItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
	cMovie*	lpMovie	= qvariant_cast<cMovie*>(index.data(Qt::UserRole));
	QBrush	oldBrush;

	QStyleOptionViewItem options = option;
	initStyleOption(&options, index);

	painter->save();

	QTextDocument doc;
	doc.setHtml(options.text);

	options.text = "";
	options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

	// shift text right to make icon visible
	QSize iconSize = options.icon.actualSize(options.rect.size());
	painter->translate(options.rect.left()+iconSize.width(), options.rect.top());
	QRect clip(0, 0, options.rect.width()+iconSize.width(), options.rect.height());

	//doc.drawContents(painter, clip);

	painter->setClipRect(clip);

	if(!lpMovie)
	{
		int	statusInit	= 0;
		int	statusProg	= 0;
		int	statusDone	= 0;

		QStandardItemModel*	lpModel		= (QStandardItemModel*)index.model();
		QStandardItem*		lpParent	= lpModel->itemFromIndex(index);
		if(lpParent)
		{
			int x	= 0;

			QStandardItem*	lpChild	= lpParent->child(x);
			while(lpChild)
			{
				cMovie*	lpMovie1	= qvariant_cast<cMovie*>(lpChild->data(Qt::UserRole));
				if(lpMovie1)
				{
					switch(lpMovie1->state())
					{
					case cMovie::StateInit:
						statusInit++;
						break;
					case cMovie::StateProgress:
						statusProg++;
						break;
					case cMovie::StateDone:
						statusDone++;
						break;
					}
				}
				x++;
				lpChild	= lpParent->child(x);
			}
		}
		if(statusProg)
			painter->setBrush(STATE_PROGRESS);
		else if(statusInit)
			painter->setBrush(STATE_INIT);
		else
			painter->setBrush(STATE_DONE);
	}
	else
	{
		oldBrush	= painter->brush();

		switch(lpMovie->state())
		{
		case cMovie::StateInit:
			painter->setBrush(STATE_INIT);
			break;
		case cMovie::StateProgress:
			painter->setBrush(STATE_PROGRESS);
			break;
		case cMovie::StateDone:
			painter->setBrush(STATE_DONE);
			break;
		default:
			break;
		}
	}
	QRect back	= clip;

	back.setLeft(back.left()+2);
	back.setRight(back.right()-2);
	back.setTop(back.top()+4);
	back.setBottom(back.bottom()-4);

	painter->drawRect(back);
	painter->setBrush(oldBrush);

	QAbstractTextDocumentLayout::PaintContext ctx;
	// set text color to red for selected item
	if (option.state & QStyle::State_Selected)
		ctx.palette.setColor(QPalette::Text, QColor("red"));
	ctx.clip = clip;
	doc.documentLayout()->draw(painter, ctx);

	painter->restore();
}

QSize cMovieViewItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	QStyleOptionViewItem options = option;
	initStyleOption(&options, index);

	QTextDocument doc;
	doc.setHtml(options.text);
	doc.setTextWidth(options.rect.width());
	return QSize(doc.idealWidth(), doc.size().height());
}
