cmake_minimum_required(VERSION 3.5)

project(OtusHomework_10_NetInterpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS system program_options REQUIRED)
find_package( Threads )

include_directories(${Boost_INCLUDE_DIR})


add_executable(OtusHomework_10_NetInterpreter
    Net/Connection.hpp
    Net/Server.hpp

    Async/NetReqHandler/Handler.hpp

    Async/Analize/Analizer.cpp
    Async/Parsing/Parser.hpp
    Async/Parsing/ParserCommand.hpp
    Async/Analize/Analizer.hpp
    Async/Data/Block.hpp
    Async/Listeners/Printer.hpp
    Async/Listeners/FilePrinter.hpp
    Async/CommandProcessor/CommandProcessor.hpp

    Options/Options.hpp

    main.cpp)

target_link_libraries(OtusHomework_10_NetInterpreter ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries(OtusHomework_10_NetInterpreter   ${Boost_LIBRARIES}    )


install(TARGETS OtusHomework_10_NetInterpreter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_FILE_NAME   "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_CONTACT 9mrsmit6@gmail.com)
include(CPack)
