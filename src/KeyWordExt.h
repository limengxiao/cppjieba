/************************************
 * file enc : ASCII
 * author   : wuyanyi09@gmail.com
************************************/
#ifndef CPPJIEBA_KEYWORDEXT_H
#define CPPJIEBA_KEYWORDEXT_H

#include "Segment.h"

namespace CppJieba
{

	struct WordInfo
	{
		string word;
		size_t wLen;
		double weight;
		double idf;
		WordInfo()
		{
			word = "";
			wLen = 0;
			weight = 0.0;
			idf = 0.0;
		}
		string getInfoStr() const
		{
			return string_format("{word:%s,wLen:%d weight:%lf, idf:%lf}", word.c_str(), wLen, weight, idf);
		}
	};

	inline string joinWordInfos(const vector<WordInfo>& vec)
	{
		vector<string> tmp;
		for(uint i = 0; i < vec.size(); i++)
		{
			tmp.push_back(vec[i].getInfoStr());
		}
		return joinStr(tmp, ",");
	}

	class KeyWordExt
	{
		private:
			Segment _segment;
			vector<string> _priorSubWords;
			set<string> _stopWords;
		public:
			KeyWordExt();
			~KeyWordExt();
			bool init();

			bool loadSegDict(const string& filePath);

			//load stopwords
			bool loadStopWords(const string& filePath);

			//load prior words' prefix
			bool loadPriorSubWords(const string& filePath);

			bool dispose();

		public:
			bool extract(const string& title, vector<string>& keywords, uint topN);
		private:
			static bool _wordInfoCompare(const WordInfo& a, const WordInfo& b);
		private:
			bool _extractTopN(const vector<string>& words, vector<string>& keywords, uint topN);
		private:
			//sort by word len - idf
			bool _sortWLIDF(vector<WordInfo>& wordInfos);
		private:
			bool _filter(vector<string>& strs);
			bool _filterDuplicate(vector<string>& strs);
			bool _filterSingleWord(vector<string>& strs);
			bool _filterSubstr(vector<string>& strs);
			bool _filterStopWords(vector<string>& strs);
		private:
			bool _prioritizeSubWords(vector<WordInfo>& wordInfos);
			bool _isContainSubWords(const string& word);

	};

}

#endif