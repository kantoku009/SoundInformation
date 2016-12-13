CC = g++
LIBS = 
LDFLAGS = -Wall -O2

SRCS_TEST_WAVEFORMAT_OPERATOR = ./test_WaveFormatOperator.cpp ../BSoundInformation.cpp ../WaveFormatOperator/CWaveFormatOperatorUtility.cpp ../WaveFormatOperator/CWaveFormatOperator.cpp ../WaveFormatOperator/WriteSample/CFactoryWriteSample.cpp ../WaveFormatOperator/WriteSample/CWriteSample8.cpp ../WaveFormatOperator/WriteSample/CWriteSample16.cpp ../WaveFormatOperator/WriteSample/CWriteSampleOther.cpp ../WaveFormatOperator/ReadSample/CReadSample8.cpp ../WaveFormatOperator/ReadSample/CReadSample16.cpp ../WaveFormatOperator/ReadSample/CReadSampleOther.cpp ../WaveFormatOperator/ReadSample/CFactoryReadSample.cpp

OUTFILE_TEST_WAVEFORMAT_OPERATOR = ./test_WaveFormatOperator

testWaveFormatOperator:
	$(CC) $(LDFLAGS) -o $(OUTFILE_TEST_WAVEFORMAT_OPERATOR) $(LIBS) $(SRCS_TEST_WAVEFORMAT_OPERATOR)

clean:
	rm $(OUTFILE_TEST_WAVEFORMAT_OPERATOR)


