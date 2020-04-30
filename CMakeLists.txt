cmake_minimum_required(VERSION 3.15)
project(ex3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
find_package(Threads)
add_executable(ex3 main.cpp Client.h Client.cpp Lexer.cpp Lexer.h Command.h OpenServerCommand.cpp OpenServerCommand.h
               ConnectCommand.cpp ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h Parse.cpp Parse.h
               PrintCommand.cpp PrintCommand.h SleepCommand.cpp SleepCommand.h
               Server.cpp Server.h Interpreter.cpp Interpreter.h Defines.h Var.h Var.cpp SymbolTable.h SymbolTable.cpp WhileCommand.cpp
               WhileCommand.h IfCommand.cpp IfCommand.h)
target_link_libraries(ex3 ${CMAKE_THREAD_LIBS_INIT})