/**
 * @file	CWriteSample8.h
 * @brief	WAVEファイルにサンプル値を書き込むクラス.
 */

#ifndef __CWRITESAMPLE8_H__
#define __CWRITESAMPLE8_H__

#include <fstream>
using namespace std;

#include "IWriteSample.h"

/**
 * @brief	WAVEファイルにサンプル値を書き込むクラス.
 * @note	量子化ビットは8ビット.
 */
class CWriteSample8 : public IWriteSample
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CWriteSample8()
	{
		m_shBitsPerSample = 8;
	}
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CWriteSample8(){ }

	/**
	 * @brief	WAVEファイルにサンプル値を書き込むクラス.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	成功/失敗.
	 */
	bool write(double i_dSample, ofstream& i_cFileStream);
};

#endif	//__CWRITESAMPLE8_H__

