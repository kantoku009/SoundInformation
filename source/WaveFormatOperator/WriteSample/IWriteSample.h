/**
 * @file	IWriteSample.h
 * @brief	WAVEファイルのサンプル値を書き込むクラス.
 */

#ifndef __IWRITESAMPLE_H__
#define __IWRITESAMPLE_H__

#include <fstream>
using namespace std;

/**
 * @brief	WAVEファイルのサンプル値を書き込むクラス.
 */
class IWriteSample
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	IWriteSample(){ }
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~IWriteSample(){ }

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	成功/失敗.
	 */
	virtual bool write(double i_dSample, ofstream& i_cFileStream) = 0;

protected:
	/**
	 * @brief	量子化ビット. [bit/sample].
	 */
	short   m_shBitsPerSample;
};

#endif	//__IWRITESAMPLE_H__

