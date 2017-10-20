#include "cmovieviewitemdelegate.h"

#include "cmovie.h"

#include <QPainter>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QAbstractItemModel>
#include <QStandardItemModel>


#define STATE_INIT		Qt::lightGray
#define STATE_PROGRESS	Qt::blue
#define STATE_DONE		Qt::green
#define STATE_UNKNOWN	Qt::black

void cMovieViewItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
	cMovie*	lpMovie	= qvariant_cast<cMovie*>(index.data(Qt::UserRole));
	QBrush	oldBrush;
	cMovie::State state;
	QPen	oldPen;

	QStyleOptionViewItem options = option;
	initStyleOption(&options, index);

	painter->save();

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
			state	= cMovie::StateProgress;
		else if(statusInit)
			state	= cMovie::StateInit;
		else
			state	= cMovie::StateDone;
	}
	else
		state	= lpMovie->state();

	QTextDocument doc;

	if(option.state & QStyle::State_Selected)
		doc.setHtml(QString("<font color='red'>%1</font>").arg(options.text));
	else
	{
		switch(state)
		{
		case cMovie::StateInit:
			doc.setHtml(QString("<font color='black'>%1</font>").arg(options.text));
			break;
		case cMovie::StateProgress:
			doc.setHtml(QString("<font color='white'>%1</font>").arg(options.text));
			break;
		case cMovie::StateDone:
			doc.setHtml(QString("<font color='black'>%1</font>").arg(options.text));
			break;
		default:
			break;
		}
	}

	options.text = "";
	options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

	// shift text right to make icon visible
	QSize iconSize = options.icon.actualSize(options.rect.size());
	painter->translate(options.rect.left()+iconSize.width(), options.rect.top());
	QRect clip(0, 0, options.rect.width()+iconSize.width(), options.rect.height());

	painter->setClipRect(clip);

	oldBrush	= painter->brush();
	oldPen		= painter->pen();

	switch(state)
	{
	case cMovie::StateInit:
		painter->setBrush(STATE_INIT);
		if(!(option.state & QStyle::State_Selected))
			painter->setPen(STATE_INIT);
		break;
	case cMovie::StateProgress:
		painter->setBrush(STATE_PROGRESS);
		if(!(option.state & QStyle::State_Selected))
			painter->setPen(STATE_PROGRESS);
		break;
	case cMovie::StateDone:
		painter->setBrush(STATE_DONE);
		if(!(option.state & QStyle::State_Selected))
			painter->setPen(STATE_DONE);
		break;
	default:
		break;
	}

	QRect	back	= clip;
	back.setLeft(back.left()+1);
	back.setRight(back.right()-1);
	back.setTop(back.top()+1);
	back.setBottom(back.bottom()-1);

	painter->drawRect(back);
	painter->setBrush(oldBrush);
	painter->setPen(oldPen);

	QAbstractTextDocumentLayout::PaintContext ctx;

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
