#pragma once
#include <QKeyEvent>

class KeyEvent
{
public:
	KeyEvent(Qt::Key key) : m_key(key) {};
	virtual ~KeyEvent() = default;

	virtual void sendEvent(QObject *focus_widget) = 0;
	void setText(const QString &text) 
	{
		m_text = text;
	};
protected:
	Qt::Key m_key;
	QString m_text;
};

class NumberKeyEvent :public KeyEvent
{
public:
	NumberKeyEvent(Qt::Key key) : KeyEvent(key) {};
	~NumberKeyEvent() = default;

	void sendEvent(QObject *focus_widget) override;
};


class LetterKeyEvent :public KeyEvent
{
public:
	LetterKeyEvent(Qt::Key key);
	~LetterKeyEvent() = default;

	void sendEvent(QObject *focus_widget) override;
	void setIsCapital(const bool &flag);
private:
	bool m_isCapital;
};

class SpaceKeyEvent :public KeyEvent
{
public:
	SpaceKeyEvent(Qt::Key key) : KeyEvent(key) {};
	~SpaceKeyEvent() = default;

	void sendEvent(QObject *focus_widget) override;
};

class BackSpaceKeyEvent :public KeyEvent
{
public:
	BackSpaceKeyEvent(Qt::Key key) : KeyEvent(key) {};
	~BackSpaceKeyEvent() = default;

	void sendEvent(QObject *focus_widget) override;
};


class SymbolKeyEvent :public KeyEvent
{
public:
	SymbolKeyEvent(Qt::Key key) : KeyEvent(key) {};
	~SymbolKeyEvent() = default;

	void sendEvent(QObject *focus_widget) override;
};


class ChKeyEvent :public KeyEvent
{
public:
	ChKeyEvent(Qt::Key key) : KeyEvent(key) {};
	~ChKeyEvent() = default;

	void sendEvent(QObject *focus_widget) override;
};

class EnterKeyEvent :public KeyEvent
{
public:
	EnterKeyEvent(Qt::Key key) : KeyEvent(key) {};
	~EnterKeyEvent() = default;

	void sendEvent(QObject *focus_widget) override;
};
