#include "catch.hpp"

#include "COBS.h"

SCENARIO("Short data encoded, and then decoded is the same", "[COBS]")
{
	GIVEN("A data buffer")
	{
		uint8_t data[] = { 0x01,0x02,0x03,0x04,0x00,0x05,0x06,0x07,0x08,0x00,0x00,0x0B };
		WHEN("It's encoded, and then decoded")
		{
			uint8_t encoded[32];
			std::size_t encodedLength = COBS::Encode(data, 12, encoded, 32);

			uint8_t decoded[32];
			std::size_t decodedLength = COBS::Decode(encoded, encodedLength, decoded, 32);

			THEN("The decoded data matches the source data")
			{
				REQUIRE(12 == decodedLength);
				for (std::size_t i = 0; i < 12; i++)
				{
					REQUIRE(decoded[i] == data[i]);
				}
			}
		}
	}
}

SCENARIO("Long data encoded and decoded is the same", "[COBS]")
{
	GIVEN("Source data which is longer that 255 bytes")
	{
		uint8_t data[4096];
		for(std::size_t i = 0; i < 2048; i++)
		{
			data[i] = 0x12;
		}
		for (std::size_t i = 2048; i < 4096; i++)
		{
			data[i] = static_cast<uint8_t>(i);
		}

		WHEN("Data is encoded and decoded")
		{
			uint8_t encoded[5100];
			std::size_t encodedLength = COBS::Encode(data, 4096, encoded, 5100);

			uint8_t decoded[5100];
			std::size_t decodedLength = COBS::Decode(encoded, encodedLength, decoded, 5100);

			THEN("Decoded matches the source data")
			{
				REQUIRE(4096 == decodedLength);
				for (std::size_t i = 0; i < 4096; i++)
				{
					REQUIRE(data[i] == decoded[i]);
				}
			}
		}

	}

}