/**
 * @file	CWaveFormatOperator.h
 * @brief	WAVEファイルを操作するクラス.
 */

#ifndef __CWAVE_FORMAT_OPERATOR_H__
#define __CWAVE_FORMAT_OPERATOR_H__

#include <fstream>
using namespace std;

#ifndef __BSOUND_INFORMATION_H__
#include "BSoundInformation.h"
#endif

/**
 * @brief	WAVEファイルを扱うクラス.
 */
class CWaveFormatOperator : public BSoundInformation
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CWaveFormatOperator(
						long  sampleRate=44100,
						short bitsPerSample=16,
						short numChannels=2,
						long  numSamples=44100)
			:BSoundInformation(
							sampleRate, 
							bitsPerSample, 
							numChannels, 
							numSamples)
	{
	}
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CWaveFormatOperator(){ }

	/**
	 * @brief	WAVEファイルから読みこみ.
	 * @param	const string i_strFilename
	 * @return	成功/失敗.
	 */
	bool read(const string i_strFileName);

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	成功/失敗.
	 */
	bool write(const string i_strFileName);

};

#endif	//__CWAVE_FORMAT_OPERATOR_H__

