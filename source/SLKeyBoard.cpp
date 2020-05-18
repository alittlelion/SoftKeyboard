#include "SLKeyBoard.h"
#include "KeyEvent.h"
#include "SLGooglePinYin.h"

SLKeyBoard::SLKeyBoard()
	: m_isCapital(false)
	, m_isSymbol(false)
	, m_isChinese(false)
	, m_googlepinyin(new SLGooglePinYin)
{
	
}


void SLKeyBoard::ClickCase()
{
	m_isCapital = !m_isCapital;
}

void SLKeyBoard::ClickSymbolChange()
{
	m_isSymbol = !m_isSymbol;
}



void SLKeyBoard::ClickType()
{
	m_isChinese = !m_isChinese;
}

bool SLKeyBoard::GetIsCapital() const
{
	return m_isCapital;
}

bool SLKeyBoard::GetIsChinese() const
{
	return m_isChinese;
}

bool SLKeyBoard::GetIsSymbol() const
{
	return m_isSymbol;
}

QVector<QString> SLKeyBoard::GetSymbols()
{
	//if(GetIsChinese())
	//{
	//	return m_chSymbols;
	//
	//}
	//else
	//{
	//	return m_symbols;
	//}
	return m_symbols;
}

QString SLKeyBoard::GetLetters() const
{
	if(GetIsCapital())
	{
		return m_capitalLetters;
	}
	else
	{
		return m_letters;
	}
}

KeyEvent* SLKeyBoard::ClickNumber(const int& number) 
{
	if (GetIsSymbol())
	{
		return ClickSymbol(number);
	}
	return new NumberKeyEvent(Qt::Key(Qt::Key_0 + number));
}

KeyEvent* SLKeyBoard::ClickLetter(const int& letter)
{
	if(GetIsSymbol())
	{
		return ClickSymbol(10 + letter);
	}
	auto key_event = new LetterKeyEvent(Id2Key(letter));
	key_event->setIsCapital(m_isCapital);
	return key_event;
}


KeyEvent* SLKeyBoard::ClickSymbol(const int& idx)
{
	QString text;
		//添加完一个汉字后,清空当前汉字信息,等待重新输入
	if (idx < GetSymbols().size())
	{
		text = GetSymbols().at(idx);
	}
	auto key_event = new SymbolKeyEvent({});
	key_event->setText(text);
	return key_event;
}

QString SLKeyBoard::ClickChinese(const int& idx)
{
	m_googlepinyin->PushBack(m_letters.at(idx));
	return m_googlepinyin->GetTempStr();
}

QVector<QString> SLKeyBoard::GetCurCandidate()
{
	return m_googlepinyin->GetCurCandidate();
}

KeyEvent* SLKeyBoard::ClickChBackSpace()
{
	if (m_googlepinyin->GetTempStr().isEmpty())
	{
		return new BackSpaceKeyEvent(Qt::Key_Backspace);
	}
	m_googlepinyin->BackSpace();
	return {};
}

QString SLKeyBoard::GetChTempStr() const
{
	return m_googlepinyin->GetTempStr();
}

KeyEvent* SLKeyBoard::ClickInputMethod(const int& idx)
{
	auto res =  m_googlepinyin->Choose(idx);
	if(res.isEmpty())
	{
		return nullptr;
	}
	m_googlepinyin->Cancel();
	auto ret = new ChKeyEvent({});
	ret->setText(res);
	return ret;
}

void SLKeyBoard::PrevPage()
{
	m_googlepinyin->PrevPage();
}

void SLKeyBoard::NextPage()
{
	m_googlepinyin->NextPage();
}

bool SLKeyBoard::CanNext() const
{
	return m_googlepinyin->CanNext();
}

bool SLKeyBoard::CanPrev() const
{
	return m_googlepinyin->CanPrev();
}

void SLKeyBoard::CancelCh()
{
	m_googlepinyin->Cancel();
}




KeyEvent* SLKeyBoard::ClickSpace()
{
	return new SpaceKeyEvent(Qt::Key_Space);
}

KeyEvent* SLKeyBoard::ClickPoint()
{
	auto key_event = new SymbolKeyEvent({});
	key_event->setText(".");
	return key_event;
}

KeyEvent* SLKeyBoard::ClickBackSpace()
{
	return new BackSpaceKeyEvent(Qt::Key_Backspace);
}

Qt::Key SLKeyBoard::Id2Key(const int& letter)
{
	ushort asc = GetLetters().at(letter).unicode();
	if(GetIsCapital())
	{
		asc -= 65;
	}
	else
	{
		asc -= 97;
	}
	return Qt::Key(Qt::Key_A + asc);
}


KeyEvent* SLKeyBoard::ClickEnter()
{
	return new EnterKeyEvent(Qt::Key_Enter);
}