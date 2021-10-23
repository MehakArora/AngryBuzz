cmake_minimum_required(VERSION 3.1)

project(Lab3)

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")


#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 COMPONENTS audio graphics)

add_executable(Lab3 main.cpp)
target_link_libraries(Lab3 sfml-audio sfml-graphics)


#if(SFML_FOUND)
#    include_directories(${SFML_INCLUDE_DIR})
#    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
#endif()
#cmake_minimum_required(VERSION 3.1)

#project(SFMLTest)

#set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
#find_package(SFML 2.5 COMPONENTS graphics)
#add_executable(SFMLTest main.cpp)
#target_link_libraries(SFMLTest sfml-graphics)