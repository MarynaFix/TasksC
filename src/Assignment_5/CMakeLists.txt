cmake_minimum_required(VERSION 4.00)

project(Assignment_5 LANGUAGES C CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME}
    main.cpp
    ./book/book.cpp
    ./customer/customer.cpp
    ./loan/loan.cpp
    ./utils/utils.cpp
    ./library/library.cpp
    ./libraryFactory/libraryFactory.cpp
    ./consoleInterface.cpp
)

