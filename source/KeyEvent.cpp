#include "KeyEvent.h"
#include <qcoreapplication.h>



void NumberKeyEvent::sendEvent(QObject* focus_widget)
{
	QCoreApplication::sendEvent(focus_widget,
		new QKeyEvent(QEvent::KeyPress, m_key, Qt::NoModifier, 
			QString::number(m_key - 48)));
	QCoreApplication::sendEvent(focus_widget, 
		new QKeyEvent(QEvent::KeyRelease, m_key, Qt::NoModifier, 
			QString::number(m_key - 48)));
}

LetterKeyEvent::LetterKeyEvent(Qt::Key key)
	: KeyEvent(key)
	, m_isCapital(false)
{
}

void LetterKeyEvent::sendEvent(QObject* focus_widget)
{
	QString text(m_key - 65 + 97);
	if(m_isCapital)
	{
		text = m_key;
	}
	QCoreApplication::sendEvent(focus_widget, 
		new QKeyEvent(QEvent::KeyPress, m_key, Qt::NoModifier, 
			text));
	QCoreApplication::sendEvent(focus_widget, 
		new QKeyEvent(QEvent::KeyRelease, m_key, Qt::NoModifier,
			text));
}

void LetterKeyEvent::setIsCapital(const bool& flag)
{
	m_isCapital = flag;
}

void SpaceKeyEvent::sendEvent(QObject* focus_widget)
{
	QCoreApplication::sendEvent(focus_widget,
		new QKeyEvent(QEvent::KeyPress, m_key, Qt::NoModifier,
			" "));
	QCoreApplication::sendEvent(focus_widget,
		new QKeyEvent(QEvent::KeyRelease, m_key, Qt::NoModifier,
			" "));
}

void BackSpaceKeyEvent::sendEvent(QObject* focus_widget)
{
	QCoreApplication::sendEvent(focus_widget,
		new QKeyEvent(QEvent::KeyPress, m_key, Qt::NoModifier,
			"\b"));
	QCoreApplication::sendEvent(focus_widget,
		new QKeyEvent(QEvent::KeyRelease, m_key, Qt::NoModifier,
			"\b"));
}

void SymbolKeyEvent::sendEvent(QObject* focus_widget)
{
	QCoreApplication::sendEvent(focus_widget,
		new QKeyEvent(QEvent::KeyPress, NULL, Qt::NoModifier,
			m_text));
	QCoreApplication::sendEvent(focus_widget,
		new QKeyEvent(QEvent::KeyRelease, NULL, Qt::NoModifier,
			m_text));
}

void ChKeyEvent::sendEvent(QObject* focus_widget)
{
	QCoreApplication::sendEvent(focus_widget,
		new QKeyEvent(QEvent::KeyPress, NULL, Qt::NoModifier,
			m_text));
	QCoreApplication::sendEvent(focus_widget,
		new QKeyEvent(QEvent::KeyRelease, NULL, Qt::NoModifier,
			m_text));
}

void EnterKeyEvent::sendEvent(QObject* focus_widget)
{
	QCoreApplication::sendEvent(focus_widget,
		new QKeyEvent(QEvent::KeyPress, m_key, Qt::KeypadModifier,
			"\r"));
	QCoreApplication::sendEvent(focus_widget,
		new QKeyEvent(QEvent::KeyRelease, m_key, Qt::KeypadModifier,
			"\r"));
}
