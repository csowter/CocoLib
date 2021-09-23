add_executable(CocoLibTests
		catch.hpp
		CircularBufferTests.cpp
		LockFreeCircularBufferTests.cpp
		SoftTimerTests.cpp
		MockTimer.cpp
		MockTimer.h
		main.cpp
		InterpolatorTests.cpp
		MovingAverageFilterTests.cpp
		FIRFilterTests.cpp
		COBSTests.cpp
		)
		
target_link_libraries(CocoLibTests
	CocoLib
	)

