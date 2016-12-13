/**
 * @file	IReadSample.h
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */

#ifndef __IREADSAMPLE_H__
#define __IREADSAMPLE_H__

#include <fstream>
using namespace std;

/**
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */
class IReadSample
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	IReadSample(){ }
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~IReadSample(){ }

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	ifstream& i_cFileStream	ストリーム.
	 * @return	成功/失敗.
	 */
	virtual double read(ifstream& i_cFileStream) = 0;

protected:
	/**
	 * @brief	量子化ビット. [bit/sample].
	 */
	short   m_shBitsPerSample;
};

#endif	//__IREADSAMPLE_H__

