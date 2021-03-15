#include "catch.hpp"

#include "CircularBuffer.h"

SCENARIO("Size can be retrieved", "[CircularBuffer]")
{
	GIVEN("A buffer with capacity for 5 elements")
	{
		CocoLib::CircularBuffer<int, 5> buf;

		THEN("The size is reported as 5")
		{
			REQUIRE(5 == buf.Size());
		}
	}
}

SCENARIO("Buffer is empty when created", "[CircularBuffer]")
{
	GIVEN("A buffer is created")
	{
		CocoLib::CircularBuffer<int, 5> buf;

		THEN("The buffer is empty")
		{
			REQUIRE(buf.IsEmpty());
		}
	}
}

SCENARIO("Buffer is full when full", "[CircularBuffer]")
{
	GIVEN("A buffer with space for 3 items")
	{
		CocoLib::CircularBuffer<int, 3> buf;

		WHEN("3 items are added")
		{
			REQUIRE(CocoLib::BufferStatus::OK == buf.Add(1));
			REQUIRE(CocoLib::BufferStatus::OK == buf.Add(2));
			REQUIRE(CocoLib::BufferStatus::OK == buf.Add(3));

			THEN("The buffer is full")
			{
				REQUIRE(buf.IsFull());
			}
		}
	}
}

SCENARIO("Count gives number of elements currently in the buffer", "[CircularBuffer]")
{
	GIVEN("A buffer with space for 3 elements")
	{
		CocoLib::CircularBuffer<int, 3> buf;

		REQUIRE(0 == buf.Count());

		WHEN("Two items are added")
		{
			buf.Add(1);
			buf.Add(2);

			THEN("The count is two")
			{
				REQUIRE(2 == buf.Count());

				WHEN("An item is removed")
				{
					int data;
					buf.Remove(data);

					THEN("The count is one")
					{
						REQUIRE(1 == buf.Count());
					}
				}
			}
		}
	}

}

SCENARIO("Count gives number of elements currently in the buffer after wrap", "[CircularBuffer]")
{
	GIVEN("A full buffer with space for 3 elements")
	{
		CocoLib::CircularBuffer<int, 3> buf;
		REQUIRE(0 == buf.Count());

		buf.Add(1);
		buf.Add(2);
		buf.Add(3);
		REQUIRE(3 == buf.Count());
		REQUIRE(buf.IsFull());

		WHEN("An element is removed")
		{
			int data;
			buf.Remove(data);

			THEN("The count is two")
			{
				REQUIRE(2 == buf.Count());

				WHEN("An item is removed")
				{
					int data;
					buf.Remove(data);

					THEN("The count is one")
					{
						REQUIRE(1 == buf.Count());
					}
				}
			}
		}
	}
}

SCENARIO("Buffers contents are retrieved in order", "[CircularBuffer]")
{
	GIVEN("A buffer with three elements")
	{
		CocoLib::CircularBuffer<int, 3> buf;
		WHEN("Elements are added, and removed")
		{
			int item1 = 1;
			int item2 = 2; 
			int item3 = 3;
			int item4 = 4;
			int item5 = 5;

			buf.Add(item1);
			buf.Add(item2);
			buf.Add(item3);

			int remove1; 
			buf.Remove(remove1);
			int remove2; 
			buf.Remove(remove2);

			buf.Add(item4);
			buf.Add(item5);
			
			int remove3; 
			buf.Remove(remove3);

			int remove4;
			buf.Remove(remove4);

			int remove5;
			buf.Remove(remove5);
			THEN("The items are in the correct order")
			{
				REQUIRE(item1 == remove1);
				REQUIRE(item2 == remove2);
				REQUIRE(item3 == remove3);
				REQUIRE(item4 == remove4);
				REQUIRE(item5 == remove5);
			}
		}
	}
}

SCENARIO("Get status is OK when there is an element to get", "[CircularBuffer]")
{
	GIVEN("A buffer with some data")
	{
		CocoLib::CircularBuffer<int, 5> buf;
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

SCENARIO("Get status is EMPTY when the buffer has no data", "[CircularBuffer]")
{
	GIVEN("A buffer with no data")
	{
		CocoLib::CircularBuffer<int, 5> buf;
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

SCENARIO("Adding to a buffer with space has OK status", "[CircularBuffer]")
{
	GIVEN("A buffer with free space")
	{
		CocoLib::CircularBuffer<int, 5> buf;
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

SCENARIO("Adding to a full buffer gives FULL status", "[CircularBuffer]")
{
	GIVEN("A full buffer")
	{
		CocoLib::CircularBuffer<int, 2> buf;
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

SCENARIO("Removing element from full buffer frees space", "[CircularBuffer]")
{
	GIVEN("A full buffer")
	{
		CocoLib::CircularBuffer<int, 2> buf;
		
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
