cmake_minimum_required(VERSION 3.12)
project(LSO_Main_Client C)

set(CMAKE_C_STANDARD 99)

add_executable(LSO_Main_Client main.c substratum_client.c substratum_client.h)