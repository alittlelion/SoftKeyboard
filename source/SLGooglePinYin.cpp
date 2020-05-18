#include "SLGooglePinYin.h"


#include <QLoggingCategory>
Q_LOGGING_CATEGORY(LogSLGooglePinYinr, "U201.LogSLGooglePinYin")
SLGooglePinYin::SLGooglePinYin()
	:m_google(new GooglePinyin)
{
	bool ret = m_google->init(64, 64);
	if(!ret)
	{
		qDebug(LogSLGooglePinYinr) << "GooglePinyin init fail";
	}
}

SLGooglePinYin::~SLGooglePinYin()
{
	if(m_google)
	{
		delete m_google;
		m_google = nullptr;
	}
}

QVector<QString> SLGooglePinYin::GetAllCandidate() const
{
	return m_google->GetAllCandidate();
}

QVector<QString> SLGooglePinYin::GetCurCandidate() const
{
	return m_google->GetCurCandidates();
}

QString SLGooglePinYin::Choose(const unsigned& id) const
{
	return m_google->choose(id);
}

void SLGooglePinYin::BackSpace() const
{
	m_google->BackSpace();
}

QString SLGooglePinYin::GetTempStr() const
{
	return m_google->GetTempStr();
}

void SLGooglePinYin::PushBack(const QString& c)
{
	m_google->PushBack(c);
	m_google->search();
}

void SLGooglePinYin::Cancel() 
{
	m_google->Cancel();
}

void SLGooglePinYin::PrevPage()
{
	m_google->PrevPage();
}

void SLGooglePinYin::NextPage()
{
	m_google->NextPage();
}

bool SLGooglePinYin::CanNext()
{
	return m_google->CanNext();
}

bool SLGooglePinYin::CanPrev()
{
	return m_google->CanPrev();
}
