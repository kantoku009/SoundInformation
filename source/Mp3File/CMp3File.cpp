#include <iostream>		//debug�p.
using namespace std;

#include "CMpegFrame.h"
#include "../CMp3File.h"

bool CMp3File::read(const string i_strFileName)
{
	ifstream a_cFileStream(i_strFileName.c_str(), ios::in|ios::binary);
	CMpegFrame a_cMpegFrame;

	if(!a_cFileStream)
	{	// �t�@�C�����J���Ȃ�����.
		cout << "Can't open file." << endl;
		return false;
	}

	// MPEG Frame�̌��������������, ���[�v����.
	while( true == this->seekMpegFrame(a_cFileStream, a_cMpegFrame) )
	{
		// BWaveForm�ɃT���v���l��ݒ�.

		// debug�p��MPEG Frame Header���o��.
		if(m_bIsDebug) a_cMpegFrame.printHeaderInfo();

		// MPEG Frame Header�N���X��������.
		a_cMpegFrame.init();
	}

	return true;
}

/**
 * 4�o�C�g���t�@�C������ǂݍ���.
 */
void CMp3File::read4byte(ifstream& i_cFileStream, unsigned long& i_ulHeader)
{
	char a_byBuffer = 0;			// �t�@�C������f�[�^��ǂݍ��ނ��߂̃o�b�t�@.

	for(short a_shCnt=3; a_shCnt>=0; a_shCnt--)
	{
		i_cFileStream.read( &a_byBuffer, sizeof(a_byBuffer) );
		i_ulHeader += (unsigned char)a_byBuffer<<(a_shCnt*8);
	}
}

/**
 * MPEG Frame��T��.
 */
bool CMp3File::seekMpegFrame(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame)
{
	bool a_bIsSuccess = true;
	unsigned long a_ulHeader = 0;	// Mpeg Frame�w�b�_.
	char a_byBuffer = 0;			// �t�@�C������f�[�^��ǂݍ��ނ��߂̃o�b�t�@.

	// �ŏ��Ƀt���[���w�b�_(4byte)���t�@�C������ǂݍ���.
	this->read4byte(i_cFileStream, a_ulHeader);

	//////////////////////////////////////////////////////////////////
	// �t���[���w�b�_�[�̌���. 
	// 4096[byte]���ɓ����w�b�_��������Ȃ����, MP3�t�@�C���ł͂Ȃ�.
	//////////////////////////////////////////////////////////////////
	for(short a_shCounter=0; a_shCounter<4096; a_shCounter++)
	{
		a_bIsSuccess = i_cMpegFrame.isHeader(a_ulHeader);
		if(false == a_bIsSuccess)
		{
			// Frame�w�b�_�ł͂Ȃ�������, 1[byte]�����炷.
			i_cFileStream.read( &a_byBuffer, sizeof(a_byBuffer) );
			a_ulHeader = (a_ulHeader<<8) + (unsigned char)a_byBuffer;
			continue;
		}

		// MPEG Frame Header��ݒ�.
		a_bIsSuccess = i_cMpegFrame.setHeader(a_ulHeader);
		if(false == a_bIsSuccess)
		{
			// �s����Frame�w�b�_��������, 3[byte]���߂�, 4[byte]�ǂݒ���.
			i_cFileStream.seekg(-3, ios_base::cur);
			a_ulHeader = 0x00;
			this->read4byte(i_cFileStream, a_ulHeader);
			continue;
		}

		//////////////////////////////////////////////////////////////////
		// �����܂ŗ�����, MPEG Frame�w�b�_ ��������.
		//////////////////////////////////////////////////////////////////
		// �f�o�b�O�p��FilePos���o��.
		if(m_bIsDebug) this->printFilePos((char*)"FilePosStart\t", i_cFileStream);

		// MPEG Frame �{�̂�ǂݍ���.
		a_bIsSuccess = this->seekMpegFrameAfter(i_cFileStream, i_cMpegFrame);
		if(true != a_bIsSuccess)
		{
			return false;
		}
		// �f�o�b�O�p��FilePos���o��.
		if(m_bIsDebug) this->printFilePos((char*)"FilePosEnd\t", i_cFileStream);
		// MPEG Frame �ǂݍ��ݐ���.
		return true;
	}
	// �����ɂ��ǂ蒅������, MP3�t�@�C���ł͂Ȃ��Ɣ��f����.
	return false;
}

/**
 * MPEG Frame �{�̂�ǂݍ���.
 */
bool CMp3File::seekMpegFrameAfter(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame)
{
	bool a_bIsSuccess = true;

	// CRC���[�h�̓ǂݍ���.
	a_bIsSuccess = this->readCRC(i_cFileStream, i_cMpegFrame);
	if(true != a_bIsSuccess)
	{
		return false;
	}

	// �T�C�h���̓ǂݍ���.
	a_bIsSuccess = this->readSideInfo(i_cFileStream, i_cMpegFrame);
	if(true != a_bIsSuccess)
	{
		return false;
	}

	// CRC�`�F�b�N.
	bool a_bIsMatchCRC = this->checkCRC(i_cMpegFrame);
	if(a_bIsMatchCRC)
	{
		if(m_bIsDebug) cerr << "CMp3FileError:CRC did not match." << endl;
		return false;
	}

	// �T�|�[�g�t�H�[�}�b�g�̃`�F�b�N.

	// ���C���f�[�^�̓ǂݍ���.
	a_bIsSuccess = this->readMainData(i_cFileStream, i_cMpegFrame);
	if(true != a_bIsSuccess)
	{
		return false;
	}

	return true;
}

/**
 * CRC���[�h��ǂݍ���.
 */
bool CMp3File::readCRC(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame)
{
	// �v���e�N�V�����r�b�g�������Ă��Ȃ�������, �������Ȃ�.
	if(E_PROTECTION_BIT_TRUE != i_cMpegFrame.getProtectionBit())
	{
		i_cMpegFrame.setCRCCheck(0);
		return true;
	}

	// CRC���[�h��ǂݍ���.
	char a_byBuffer2[2] = {0, 0};
	unsigned short a_usCRCCheck = 0;
	i_cFileStream.read(a_byBuffer2, sizeof(a_byBuffer2));

	// CRC���[�h���t���[�����ɐݒ�.
	a_usCRCCheck = (a_byBuffer2[0]<<8) + a_byBuffer2[1];
	i_cMpegFrame.setCRCCheck(a_usCRCCheck);

	return true;
}

/**
 * �T�C�h���̓ǂݍ���.
 */
bool CMp3File::readSideInfo(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame)
{
	unsigned short a_usSideSize = i_cMpegFrame.getSideSize();
	char a_bySide[64];

	// �T�C�h����ǂݍ���.
	i_cFileStream.read(a_bySide, a_usSideSize);

	// �T�C�h����ݒ�.
	i_cMpegFrame.setSideInfo(a_bySide);

	return true;
}

/**
 * ���C���f�[�^�̓ǂݍ���.
 */
bool CMp3File::readMainData(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame)
{
	char a_pFrameData[2048];

	// Main�f�[�^�T�C�Y���擾.
	long a_lSize = i_cMpegFrame.getMainDataSize();
	if(0 > a_lSize)
	{
		if(m_bIsDebug) cerr << "CMp3FileError:do not read Maindata:" << a_lSize << endl;
		return false;
	}

	// Main�f�[�^��ǂݍ���.
	i_cFileStream.read(a_pFrameData, a_lSize);

	return true;
}

/**
 * CRC���`�F�b�N.
 */
bool CMpegFrame::checkCRC(CMpegFrame& i_cMpegFrame)
{
	// TBA. ������.
	return true;
}

/**
 * CRC���v�Z.
 */
unsigned short CMpegFrame::calcCRC( unsigned char* i_pCheckBuf, short i_shBytes )
{
	const unsigned int CRC16_POLYNOMIAL = 0x18005;
	unsigned int crc = 0xffff;

	for( int i=0; i<i_shBytes; i++ )
	{
		unsigned short byte = i_pCheckBuf[i];
		for( int i=0; i<8; i++ )
		{
			crc <<= 1;
			byte <<= 1;
			int nCRCCarry = (crc & 0x10000)!=0;
			int nDataCarry = (byte & 0x100)!=0;
			if( (!nCRCCarry && nDataCarry) || (nCRCCarry && !nDataCarry))
			{
				crc ^= CRC16_POLYNOMIAL;
			}

			crc &= 0xffff;
		}
	}

	return (unsigned short)crc;
}

/**
 * �t�@�C���|�W�V������\��. Debug�p.
 */
void CMp3File::printFilePos(char* i_pMessage, ifstream& i_cFileStream)
{
	ifstream::pos_type a_nPos = i_cFileStream.tellg();
	cout << i_pMessage << a_nPos << endl;
}

