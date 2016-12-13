/**
 * @file	CReadSampleOther.h
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */

#ifndef __CREADSAMPLEOTHER_H__
#define __CREADSAMPLEOTHER_H__

#include <fstream>
using namespace std;

#include "IReadSample.h"

/**
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */
class CReadSampleOther : public IReadSample
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CReadSampleOther()
	{
		m_shBitsPerSample = 24;
	}
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CReadSampleOther(){ }

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	正規化されたサンプル値.
	 */
	double read(ifstream& i_cFileStream);
};

#endif	//__CREADSAMPLEOTHER_H__

