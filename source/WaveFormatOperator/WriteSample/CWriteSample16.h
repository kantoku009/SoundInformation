/**
 * @file	CWriteSample16.h
 * @brief	WAVEファイル書き込むクラス.
 */

#ifndef __CWRITESAMPLE16_H__
#define __CWRITESAMPLE16_H__

#include <fstream>
using namespace std;

#include "IWriteSample.h"

/**
 * @brief	WAVEファイル書き込むクラス.
 * @note	量子化ビットは16ビット.
 */
class CWriteSample16 : public IWriteSample
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CWriteSample16()
	{
		m_shBitsPerSample = 16;
	}
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CWriteSample16(){ }

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	成功/失敗.
	 */
	bool write(double i_dSample, ofstream& i_cFileStream);
};

#endif	//__CWRITESAMPLE16_H__

