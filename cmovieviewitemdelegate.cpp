#include "cmovieviewitemdelegate.h"

#include "cmovie.h"

#include <QPainter>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>


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
	painter->drawRect(clip);

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
