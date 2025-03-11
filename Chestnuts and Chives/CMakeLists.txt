cmake_minimum_required(VERSION 3.20)
project(ChestnutsAndChives)

# Specify C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Detect platform
if(WIN32)
    # Set paths to your prebuilt SDL3, SDL3_image, and SDL3_net
    set(SDL3_INCLUDE_DIR "C:/Libraries/SDL3-3.2.6/include") 
    set(SDL3_LIBRARY "C:/Libraries/SDL3-3.2.6/lib") 

    set(SDL3_IMAGE_INCLUDE_DIR "C:/Libraries/SDL3_image-3.2.4/include")
    set(SDL3_IMAGE_LIBRARY "C:/Libraries/SDL3_image-3.2.4/lib")

    set(SDL3_NET_INCLUDE_DIR "C:/Libraries/SDL3_net/include")
    set(SDL3_NET_LIBRARY "C:/Libraries/SDL3_net/lib")

elseif(APPLE OR UNIX)
    # Automatically find SDL3, SDL3_image, and SDL3_net on Linux/macOS
    find_package(SDL3 REQUIRED)
    find_package(SDL3_image REQUIRED)
    find_package(SDL3_net REQUIRED)
endif()

# Add source files
file(GLOB SOURCES "Chestnuts and Chives/*.cpp")
add_executable(ChestnutsAndChives ${SOURCES})

# Include SDL3, SDL3_image, and SDL3_net
target_include_directories(ChestnutsAndChives PRIVATE 
    ${SDL3_INCLUDE_DIR} 
    ${SDL3_IMAGE_INCLUDE_DIR}
    ${SDL3_NET_INCLUDE_DIR}
)

# Link SDL3, SDL3_image, and SDL3_net
target_link_libraries(ChestnutsAndChives PRIVATE 
    ${SDL3_LIBRARY} 
    ${SDL3_IMAGE_LIBRARY}
    ${SDL3_NET_LIBRARY}
)
