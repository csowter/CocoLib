#ifndef cobs_h
#define cobs_h

#include <cstdint>
#include <cstddef>

class COBS
{
public:
	COBS() = delete;
	static std::size_t Encode(const uint8_t *sourceData, std::size_t sourceLength, uint8_t *destinationData, std::size_t destinationLength);
	static std::size_t Decode(const uint8_t *sourceData, std::size_t sourceLength, uint8_t *destinationData, std::size_t destinationLength);
};

#endif
