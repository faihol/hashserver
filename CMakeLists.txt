cmake_minimum_required(VERSION 3.5)
project(hashserver)

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Boost_USE_MULTITHREADED ON)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY -DBOOST_SYSTEM_NO_DEPRECATED)

include_directories(${PROJECT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})

set(${PROJECT_NAME}_SOURCES
	src/hasher.cpp
	src/server.cpp
	src/session.cpp
)
add_library(${PROJECT_NAME}_lib STATIC ${${PROJECT_NAME}_SOURCES})
target_link_libraries(${PROJECT_NAME}_lib ${Boost_LIBRARIES} ${OPENSSL_CRYPTO_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

add_executable(${PROJECT_NAME} src/hashserver.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib ${CMAKE_THREAD_LIBS_INIT})

include(CTest)
if(BUILD_TESTING)
	add_subdirectory(tests)
endif()
