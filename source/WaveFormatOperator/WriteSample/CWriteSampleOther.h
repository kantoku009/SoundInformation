/**
 * @file	CWriteSampleOther.h
 * @brief	WAVEファイル書き込むクラス.
 */

#ifndef __CWRITESAMPLEOTHER_H__
#define __CWRITESAMPLEOTHER_H__

#include <fstream>
using namespace std;

#include "IWriteSample.h"

/**
 * @brief	WAVEファイルを扱うクラス.
 * @note	8bit,16bit以外で量子化されたファイルを書き込む.
 */
class CWriteSampleOther : public IWriteSample
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CWriteSampleOther()
	{
		m_shBitsPerSample = 24;
	}
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CWriteSampleOther(){ }

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	成功/失敗.
	 */
	bool write(double i_dSample, ofstream& i_cFileStream);
};

#endif	//__CWRITESAMPLEOTHER_H__

