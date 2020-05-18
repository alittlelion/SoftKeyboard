#pragma once
#include <QWidget>

class ContextEdit
{
public:
	ContextEdit() = default;
	~ContextEdit() = default;
	void insert(QString data);
	void backspace();
	void setWidget(QWidget *widget)
	{
		m_widget = widget;
	};
	QWidget* getWidget()
	{
		return m_widget;
	};
protected:
	QWidget *m_widget = nullptr;
};
