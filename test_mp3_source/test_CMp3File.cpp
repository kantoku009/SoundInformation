#include "../source/CMp3File.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    CMp3File a_cMp3File;
	char* inFileName = argv[1];
	bool a_bIsSuccess = true;

	// Mp3ファイルを読み込み.
	if(a_bIsSuccess)
	{
		cout << "--- Read file now ---" << endl;
		a_bIsSuccess = a_cMp3File.read(inFileName);
	}
	if(false == a_bIsSuccess)
	{
		cout << "--- error: Read file ---" << endl;
	}

    return 0;
}

