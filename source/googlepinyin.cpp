#include "googlepinyin.h"
#include <string.h>
#include <qfile.h>
#include <qcoreapplication.h>
#include <qdebug.h>
using namespace ime_pinyin;

// fix cand_len
static size_t fix_cand_len(size_t cand, int output_len)
{
#define MAX_SINGLE 40   // single hz MAX is 40
	size_t i;
	size_t decode_len;
	size_t single = 0;
	size_t multi = 0;
	char16 *cand_buf = new char16[output_len];

	 im_get_sps_str(&decode_len);
	if (decode_len == 1) { // only one spell char
		if (cand > 20) {
			cand = 20; // max is 10.
		}
		delete cand_buf;
		return  cand;
	}

	for (i = 0; i < cand; i++) {
		im_get_candidate(i, cand_buf, output_len);
		if (strlen((char *)cand_buf) > 2) {
			multi++;
		}
		else {
			single++;
			if (single > MAX_SINGLE) {
				break;
			}
		}
	}

	cand = multi + single;
	delete cand_buf;
	return  cand;
}

// constructor
GooglePinyin::GooglePinyin(QObject *parent) :
	QObject(parent), enable(false)
	, size_(0)
	, fixed_count_(0)
	, page_(0)
	, page_num_(5)
{
}

// input panel destructor
GooglePinyin::~GooglePinyin()
{
	im_close_decoder();
}

// init dict database
bool GooglePinyin::init(int max_spell_len, int max_output_len)
{
	bool  ret;
	QString dict1 = qApp->applicationDirPath() + "/dict_pinyin.dat";
	QString dict2 = qApp->applicationDirPath() + "/dict_pinyin_user.dat";
	QFile file(dict1);
	if(!file.exists())
	{
		QFile::copy(":/Resources/dict_pinyin.dat", dict1);
		file.setPermissions(QFile::WriteUser | QFile::ReadUser);
	}
	QFile file2(dict2);
	if (!file2.exists())
	{
		QFile::copy(":/Resources/dict_pinyin_user.dat", dict2);
		file2.setPermissions(QFile::WriteUser | QFile::ReadUser);
	}
	ret = im_open_decoder(dict1.toLocal8Bit().data(),
							dict2.toLocal8Bit().data());

	enable = ret;
	if (ret == false) {
		return ret;
	}

	im_set_max_lens(max_spell_len /* input pinyin max len */,
		max_output_len /* max output Chinese character string len */);

	reset_search();

	spell_len = max_spell_len;
	output_len = max_output_len;

	return  ret;
}

// flush dict cache
void GooglePinyin::flush_cache()
{
	im_flush_cache();
}

// add a char to search
unsigned GooglePinyin::search()
{
	if (!enable)
	{
		return 0;
	}
	QByteArray bytearray(str_.toUtf8());
	char  *pinyin = bytearray.data();
	//const char  *pinyin = str_.toUtf8().data();
	size_t cand = im_search(pinyin, bytearray.size());
	if(cand == 0)
	{
		Cancel();
		return {};
	}
	
	const uint16 *pos;
	int size = im_get_spl_start_pos(pos);

	page_ = 0;
	cand = fix_cand_len(cand, output_len);
	size_ = (unsigned)cand;
	//str_ = spell.toStdString();
	return  (unsigned)cand;
}

// delete a char to search
unsigned GooglePinyin::del_search(unsigned pos)
{
	if (!enable)
	{
		return 0;
	}
	size_t cand = im_delsearch(pos, false, false);
	cand = fix_cand_len(cand, output_len);

	return  (unsigned)cand;
}

// reset search string
void GooglePinyin::reset_search()
{
	if (!enable)
	{
		return;
	}
	im_reset_search();
	size_ = 0;;
	page_ = 0;
}

// get current search position
unsigned GooglePinyin::cur_search_pos()
{
	const uint16 *start_pos;
	size_t  pos_len;
	size_t  fixed_len = im_get_fixed_len();

	pos_len = im_get_spl_start_pos(start_pos);
	if (fixed_len <= pos_len) {
		return  (start_pos[fixed_len]);
	}

	return  0;
}

// get a candidate
QString GooglePinyin::get_candidate(unsigned index)
{
	char16 *cand_buf = new char16[output_len];
	QString cand_str;

	char16 *cand = im_get_candidate(index, cand_buf, output_len);
	if (cand) 
	{
		cand_str = QString::fromUtf16(cand); // 'GooglePinyin' output is utf16 string.
		if (index == 0) 
		{
			cand_str.remove(0, im_get_fixed_len());
		}
	}
	delete cand_buf;
	return cand_str;
}

// choose a candidate
QString GooglePinyin::choose(unsigned index)
{
	size_t left;

	for(const auto s : get_candidate(page_ * page_num_ + index))
	{
		chs_.push_back(s);
	}
	left = im_choose(page_ * page_num_ + index);
	
	left = fix_cand_len(left, output_len);
	size_ = left;
	fixed_count_++;
	page_ = 0;
	if(left <= 1)
	{
		//clean;
		auto res = GetResult();
		Cancel();
		return res;
	}
	else
	{
		return {};
	}
}

// unchoose a candidate
unsigned GooglePinyin::unchoose()
{
	size_t cand = im_cancel_last_choice();
	fixed_count_--;
	cand = fix_cand_len(cand, output_len);
	size_ = cand;
	chs_.pop_back();
	return  (unsigned)cand;
}

QVector<QString> GooglePinyin::GetAllCandidate()
{
	QVector<QString> list;
	for (unsigned i = 0; i < size_; i++)
	{
		list.push_back(get_candidate(i));
	}
	return list;
}

QVector<QString> GooglePinyin::GetCurCandidates()
{
	QVector<QString> list;
	for (unsigned i = page_ * page_num_; i < size_ && i < (page_ + 1) * page_num_; i++)
	{
		list.push_back(get_candidate(i));
	}
	return list;
}

QString GooglePinyin::GetTempStr()
{
	const uint16 *pos;
	size_t size = im_get_spl_start_pos(pos);
	QString tmp = str_;
	size_t j = chs_.size();
	int last_idx = 0;
	for (int i = size - 1; i >= 0; i--)
	{
		auto p = pos[i];
		tmp.insert(p, "'");
		if(i < chs_.size())
		{
			tmp.replace(p + 1, last_idx - p + 1 , chs_.at(i));
		}
		last_idx = p;
		j++;
	}
	return tmp.right(tmp.size() - 1);
}

void GooglePinyin::BackSpace()
{
	if (fixed_count_ != 0)
	{
		unchoose();
	}
	else
	{
		del_search(str_.size() - 1);
		str_ = str_.left(str_.size() - 1);
		if (str_.isEmpty())
		{
			Cancel();
		}
	}
	page_ = 0;
}

void GooglePinyin::PushBack(const QString &c)
{
	str_.append(c);
}

QString GooglePinyin::GetResult()
{
	QString res;
	for(const auto &s : chs_)
	{
		res.push_back(s);
	}
	return res;
}

void GooglePinyin::Cancel()
{
	chs_.clear();
	size_ = 0;
	str_.clear();
	fixed_count_ = 0;
	reset_search();
}

void GooglePinyin::PrevPage()
{
	if(CanPrev())
	{
		page_--;
	}
}

void GooglePinyin::NextPage()
{
	if(CanNext())
	{
		page_++;
	}
}

bool GooglePinyin::CanNext()
{
	if((page_ + 1) * page_num_ < size_)
	{
		return true;
	}
	return false;
}

bool GooglePinyin::CanPrev()
{
	if(page_ == 0)
	{
		return false;
	}
	return true;
}
