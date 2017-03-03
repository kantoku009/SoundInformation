/**
 * @file	CWaveFileUtility.h
 * @brief	SoundInformationのユーティリティクラス.
 */

#ifndef __CWAVEFILEUTILITY_H__
#define __CWAVEFILEUTILITY_H__


class CWaveFileUtility
{
public:
	CWaveFileUtility();
	~CWaveFileUtility();

	/**
	 * @brief	bit shiftをする.
	 * @param	short i_shBitShift
	 * @return	bit shiftした結果.
	 */
	static long bitShift(short i_shNumShift);
    
	/**
	 * @brief	Big-endianか否かを調べる.
	 * @param	なし.
	 * @return	true:Big-endian / false:Little-endian
	 */
	static bool isBigEndian();
    
	/**
	 * @brief	long型 Little-endian -> Big-endian を変換する.
	 * @param	変換するデータ.
	 * @return	変換した結果.
	 */
	static long swapLong(char* i_pbyData);

	/**
	 * @brief	short型 Little-endian -> Big-endian を変換する.
	 * @param	変換するデータ.
	 * @return	変換した結果.
	 */
	static short swapShort(char* i_pbyData);

	/**
	 * @brief	int型 Little-endian -> Big-endian を変換する.
	 * @param	変換するデータ.
	 * @return	変換した結果.
	 */
	static int swapInt(char* i_pbyData);

	/**
	 * @brief	4ByteDataをlong型に変換する.
	 * @param	char* data
	 * @return	変換した数値.
	 */
	static long convert4ByteDataToLong(char* data);

	/**
	 * @brief	long型を4ByteDataに変換する.
	 * @param	long i_lInteger
	 * @param	char* i_pbyData out引数.
	 * @return	なし.
	 */
	static void convertLongTo4ByteData(long i_lInteger, char* i_pbyData);

	/**
	 * @brief	2ByteDataをshort型に変換する.
	 * @param	char* data
	 * @return	変換した数値.
	 */
	static short convert2ByteDataToShort(char* data);

	/**
	 * @brief	short型を2ByteDataに変換する.
	 * @param	short i_shInteger
	 * @param	char* i_pbyData out引数.
	 * @return	なし.
	 */
	static void convertShortTo2ByteData(short i_shInteger, char* i_pbyData);

};

#endif	//__CWAVEFILEUTILITY_H__
