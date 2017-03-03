/**
 * @file	ISampleOperator.h
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */


#ifndef __ISAMPLEOPERATOR_H__
#define __ISAMPLEOPERATOR_H__

#include <fstream>
using namespace std;

/**
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */
class ISampleOperator
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	ISampleOperator(){ }
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~ISampleOperator(){ }

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	ifstream& i_cFileStream	ストリーム.
	 * @return	成功/失敗.
	 */
	virtual double read(ifstream& i_cFileStream) = 0;
	
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

#endif	// __ISAMPLEOPERATOR_H__

