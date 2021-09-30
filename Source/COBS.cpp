#include "COBS.h"

std::size_t COBS::Encode(const uint8_t *sourceData, std::size_t sourceLength, uint8_t *destinationData, std::size_t destinationLength)
{
	std::size_t strideIndex{ 0 };
	std::size_t strideLength{ 1 };
	std::size_t sourceIndex{ 0 };
	std::size_t destinationIndex{ 1 };

	while(sourceIndex < sourceLength)
	{
		if (sourceData[sourceIndex] == 0x00)
		{
			destinationData[strideIndex] = static_cast<uint8_t>(strideLength);
			strideIndex = destinationIndex;
			destinationIndex++;
			sourceIndex++;
			strideLength = 1;
		}
		else
		{
			if (destinationIndex < destinationLength)
			{
				destinationData[destinationIndex] = sourceData[sourceIndex];
				destinationIndex++;
				sourceIndex++;
				strideLength++;

				if (strideLength == 0xFF)
				{
					destinationData[strideIndex] = static_cast<uint8_t>(strideLength);
					strideIndex = destinationIndex;
					destinationIndex++;
					strideLength = 1;
				}
			}
			else 
			{
				break;
			}
		}
	}
	destinationData[strideIndex] = static_cast<uint8_t>(strideLength);
	if (destinationIndex < destinationLength)
	{
		destinationData[destinationIndex] = 0x00;
		destinationIndex++;
	}
	return destinationIndex;
}

std::size_t COBS::Decode(const uint8_t *sourceData, std::size_t sourceLength, uint8_t *destinationData, std::size_t destinationLength)
{
	std::size_t nextZeroIndex{ sourceData[0] };
	std::size_t nextZeroSize{ sourceData[0] };
	std::size_t destinationIndex{ 0 };

	for (std::size_t i = 1; i < sourceLength; i++)
	{
		if (sourceData[i] == 0x0)
			break;
		if (destinationIndex < destinationLength)
		{
			if (i != nextZeroIndex)
			{
				destinationData[destinationIndex] = sourceData[i];
				destinationIndex++;
			}
			else
			{
				if (nextZeroSize != 0xFF)
				{
					nextZeroIndex += sourceData[i];
					nextZeroSize = sourceData[i];
					destinationData[destinationIndex] = 0x0;
					destinationIndex++;
				}
				else
				{
					nextZeroIndex += sourceData[i];
					nextZeroSize = sourceData[i];
				}
				
			}			
		}
	}

	return destinationIndex;
}