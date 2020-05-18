#pragma once
#include "googlepinyin/include/pinyinime.h"
#include <qobject.h>
#include <qvector.h>
using namespace std;
class QString;

class GooglePinyin : public QObject
{
	Q_OBJECT

public:
	explicit GooglePinyin(QObject *parent = nullptr);
	~GooglePinyin();

	bool init(int max_spell_len, int max_output_len);
	unsigned search();
	QString choose(unsigned);
	unsigned unchoose();
	QString get_candidate(unsigned);
	QVector<QString> GetAllCandidate();
	QVector<QString> GetCurCandidates();
	QString GetTempStr();
	void BackSpace();
	void PushBack(const QString &c);
	void Cancel();
	void PrevPage();
	void NextPage();
	bool CanNext();
	bool CanPrev();
	
private:
	unsigned del_search(unsigned);
	void reset_search();
	unsigned cur_search_pos();
	QString GetResult();
	void flush_cache();
	bool enable;
	int  spell_len;
	int  output_len;
	size_t size_;
	QString str_;
	size_t fixed_count_;
	uint page_;
	QVector<QString> chs_;
	int page_num_;
};
