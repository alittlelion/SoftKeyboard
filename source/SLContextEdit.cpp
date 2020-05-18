#include "SLContextEdit.h"
#include <QKeyEvent>
#include <QCoreApplication>
#include <qdebug.h>

void ContextEdit::insert(QString data)
{
	QCoreApplication::sendEvent(m_widget, new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier, data));
	QCoreApplication::sendEvent(m_widget, new QKeyEvent(QEvent::KeyRelease, 0, Qt::NoModifier, data));
}

void ContextEdit::backspace()
{
	QCoreApplication::sendEvent(m_widget, new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier, "\b"));
	QCoreApplication::sendEvent(m_widget, new QKeyEvent(QEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier, "\b"));
}
