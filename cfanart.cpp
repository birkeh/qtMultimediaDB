#include "cfanart.h"


cFanart::cFanart(Type type) :
	m_type(type),
	m_iID(-1),
	m_szURL(""),
	m_szLanguage(""),
	m_iLikes(0),
	m_iSeason(-1),
	m_szDisc(""),
	m_szDiscType(""),
	m_bActive(false)
{
}

void cFanart::setType(const Type& type)
{
	m_type	= type;
}

cFanart::Type cFanart::type()
{
	return(m_type);
}

void cFanart::setID(const qint32& iID)
{
	m_iID	= iID;
}

qint32 cFanart::id()
{
	return(m_iID);
}

void cFanart::setURL(const QString& szURL)
{
	m_szURL	= szURL;
}

QString cFanart::url()
{
	return(m_szURL);
}

void cFanart::setLanguage(const QString& szLanguage)
{
	m_szLanguage	= szLanguage;
}

QString cFanart::language()
{
	return(m_szLanguage);
}

void cFanart::setLikes(const qint32& iLikes)
{
	m_iLikes	= iLikes;
}

qint32 cFanart::likes()
{
	return(m_iLikes);
}

void cFanart::setSeason(const qint16& iSeason)
{
	m_iSeason	= iSeason;
}

qint16 cFanart::season()
{
	return(m_iSeason);
}

void cFanart::setDisc(const QString& szDisc)
{
	m_szDisc	= szDisc;
}

QString cFanart::disc()
{
	return(m_szDisc);
}

void cFanart::setDiscType(const QString& szDiscType)
{
	m_szDiscType	= szDiscType;
}

QString cFanart::discType()
{
	return(m_szDiscType);
}

void cFanart::setActive(const bool& bActive)
{
	m_bActive	= bActive;
}

bool cFanart::active()
{
	return(m_bActive);
}

cFanart* cFanartList::add(const cFanart::Type& type)
{
	cFanart*	lpNew	= new cFanart(type);
	append(lpNew);
	return(lpNew);
}

cFanart* cFanartList::search(const cFanart::Type& type, const QString& szLanguage)
{
	for(int x = 0;x < count();x++)
	{
		if(szLanguage.length())
		{
			if(at(x)->type() == type && !at(x)->language().compare(szLanguage, Qt::CaseInsensitive))
				return(at(x));
		}
		else
		{
			if(at(x)->type() == type)
				return(at(x));
		}
	}
	return(0);
}

cFanart* cFanartList::search(const cFanart::Type& type, const bool bActive, const QString& szLanguage)
{
	for(int x = 0;x < count();x++)
	{
		if(szLanguage.length())
		{
			if(at(x)->type() == type &&
					!at(x)->language().compare(szLanguage, Qt::CaseInsensitive) &&
					at(x)->active() == bActive)
				return(at(x));
		}
		else
		{
			if(at(x)->type() == type && at(x)->active() == bActive)
				return(at(x));
		}
	}
	return(0);
}
