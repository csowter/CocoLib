#include "catch.hpp"

#include "LockFreeCircularBuffer.h"

SCENARIO("LF Buffer is empty when created", "[LockFreeCircularBuffer]")
{
	GIVEN("A buffer is created")
	{
		CocoLib::LockFreeCircularBuffer<int, 5> buf;

		THEN("The buffer is empty")
		{
			REQUIRE(buf.IsEmpty());
		}
	}
}

SCENARIO("LF Buffer is full when full", "[LockFreeCircularBuffer]")
{
	GIVEN("A buffer with space for 3 items")
	{
		CocoLib::LockFreeCircularBuffer<int, 4> buf;

		WHEN("3 items are added")
		{
			buf.Add(1);
			buf.Add(2);
			buf.Add(3);

			THEN("The buffer is full")
			{
				REQUIRE(buf.IsFull());
			}
		}
	}
}

SCENARIO("LF Buffers contents are retrieved in order", "[LockFreeCircularBuffer]")
{
	GIVEN("A buffer with three elements")
	{
		CocoLib::LockFreeCircularBuffer<int, 4> buf;
		WHEN("Elements are added, and removed")
		{
			int item1 = 1;
			int item2 = 2; 
			int item3 = 3;

			buf.Add(item1);
			buf.Add(item2);
			buf.Add(item3);

			int remove1; 
			buf.Remove(remove1);
			int remove2; 
			buf.Remove(remove2);
			int remove3; 
			buf.Remove(remove3);

			THEN("The items are in the correct order")
			{
				REQUIRE(item1 == remove1);
				REQUIRE(item2 == remove2);
				REQUIRE(item3 == remove3);
			}
		}
	}
}

SCENARIO("LF Get status is OK when there is an element to get", "[LockFreeCircularBuffer]")
{
	GIVEN("A buffer with some data")
	{
		CocoLib::LockFreeCircularBuffer<int, 5> buf;
		buf.Add(1);

		WHEN("Data is fetched")
		{
			int data;
			CocoLib::BufferStatus status = buf.Remove(data);

			THEN("Status is OK")
			{
				REQUIRE(status == CocoLib::BufferStatus::OK);
			}
		}
	}
}

SCENARIO("LF Get status is EMPTY when the buffer has no data", "[LockFreeCircularBuffer]")
{
	GIVEN("A buffer with no data")
	{
		CocoLib::LockFreeCircularBuffer<int, 5> buf;
		WHEN("Data is fetched")
		{
			int data;
			CocoLib::BufferStatus status = buf.Remove(data);

			THEN("The status is EMPTY")
			{
				REQUIRE(status == CocoLib::BufferStatus::Empty);
			}
		}
	}
}

SCENARIO("LF Adding to a buffer with space has OK status", "[LockFreeCircularBuffer]")
{
	GIVEN("A buffer with free space")
	{
		CocoLib::LockFreeCircularBuffer<int, 5> buf;
		WHEN("Data is added")
		{
			CocoLib::BufferStatus status = buf.Add(3);
			THEN("Status is OK")
			{
				REQUIRE(status == CocoLib::BufferStatus::OK);
			}
		}
	}
}

SCENARIO("LF Adding to a full buffer gives FULL status", "[LockFreeCircularBuffer]")
{
	GIVEN("A full buffer")
	{
		CocoLib::LockFreeCircularBuffer<int, 3> buf;
		buf.Add(1);
		buf.Add(2);

		WHEN("Another element is added")
		{
			CocoLib::BufferStatus status = buf.Add(3);

			THEN("Status is FULL")
			{
				REQUIRE(status == CocoLib::BufferStatus::Full);
			}
		}
	}
}

SCENARIO("LF Removing element from full buffer frees space", "[LockFreeCircularBuffer]")
{
	GIVEN("A full buffer")
	{
		CocoLib::LockFreeCircularBuffer<int, 3> buf;
		
		buf.Add(1);
		buf.Add(2);

		REQUIRE(buf.IsFull());

		WHEN("An element is removed")
		{
			int data;
			buf.Remove(data);

			THEN("The buffer has space")
			{
				REQUIRE(!(buf.IsFull()));
				AND_THEN("An element can be added")
				{
					CocoLib::BufferStatus status = buf.Add(3);
					REQUIRE(status == CocoLib::BufferStatus::OK);
				}
			}
		}
	}
}
