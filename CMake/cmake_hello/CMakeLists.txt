cmake_minimum_required(VERSION 3.16)
project(our_project VERSION 0.0.1
                    DESCRIPTION "Hello project"
                    LANGUAGES CXX)       
set(FOO "foo" CACHE STRING "Description")
message(STATUS "Value of FOO: ${FOO}")
