cmake_minimum_required(VERSION 3.20)
project(ChestnutsAndChives)

# Specify C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Detect platform
if(WIN32)
    # Set paths to your prebuilt SDL3, SDL3_image, and SDL3_net
    set(SDL3_INCLUDE_DIR "C:/Libraries/SDL3-3.2.6/include")
    set(SDL3_LIBRARY "C:/Libraries/SDL3-3.2.6/lib/x64/SDL3.lib") 

    set(SDL3_IMAGE_INCLUDE_DIR "C:/Libraries/SDL3_image-3.2.4/include")
    set(SDL3_IMAGE_LIBRARY "C:/Libraries/SDL3_image-3.2.4/lib/x64/SDL3_image.lib")

    set(SDL3_NET_INCLUDE_DIR "C:/Libraries/SDL3_net/include")
    set(SDL3_NET_LIBRARY "C:/Libraries/SDL3_net/lib/x64/SDL3_net.lib")

    set(SDL3_TTF_INCLUDE_DIR "C:/Libraries/SDL3_ttf/include")
    set(SDL3_TTF_LIBRARY "C:/Libraries/SDL3_ttf/lib/x64/SDL3_ttf.lib")

elseif(APPLE OR UNIX)
    # Automatically find SDL3, SDL3_image, and SDL3_net on Linux/macOS
    find_package(SDL3 REQUIRED)
    find_package(SDL3_image REQUIRED)
    find_package(SDL3_net REQUIRED)
    find_package(SDL3_ttf REQUIRED)
endif()

# Add source files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/**/*.cpp")
add_executable(ChestnutsAndChives ${SOURCES})

# Include SDL3, SDL3_image, and SDL3_net
# Also includes all code directories to make linking easier
target_include_directories(ChestnutsAndChives PRIVATE 
    ${SDL3_INCLUDE_DIR} 
    ${SDL3_IMAGE_INCLUDE_DIR}
    ${SDL3_NET_INCLUDE_DIR}
    ${SDL3_TTF_INCLUDE_DIR}
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Core/AssetManagement"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Core/GameStates"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Core/GameStates/DefaultStates"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Core/Networking"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Core/Rendering"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Core/UI"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Game/Map"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Game/Networking"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Game/Networking/ServerStates"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Game/Cooking"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Game/Persistence"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Game/GameStates"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Game/GameStates/GameplayStates"
    "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Assets/Libraries"
)

# Link SDL3, SDL3_image, and SDL3_net
target_link_libraries(ChestnutsAndChives PRIVATE 
    ${SDL3_LIBRARY} 
    ${SDL3_IMAGE_LIBRARY}
    ${SDL3_NET_LIBRARY}
    ${SDL3_TTF_LIBRARY}
)

# Define your libraries and assets paths
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}")
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/Chestnuts and Chives/Assets")
set(LIBS_DIR "${ASSETS_DIR}/Libraries")

# Copy SDL3.dll, SDL3_image and SDL3_net.dll and SDL3_ttf to the output folder
add_custom_command(TARGET ChestnutsAndChives POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${LIBS_DIR}/SDL3.dll
    $<TARGET_FILE_DIR:ChestnutsAndChives>)

add_custom_command(TARGET ChestnutsAndChives POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${LIBS_DIR}/SDL3_image.dll
    $<TARGET_FILE_DIR:ChestnutsAndChives>)

add_custom_command(TARGET ChestnutsAndChives POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${LIBS_DIR}/SDL3_net.dll
    $<TARGET_FILE_DIR:ChestnutsAndChives>)

    add_custom_command(TARGET ChestnutsAndChives POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${LIBS_DIR}/SDL3_ttf.dll
    $<TARGET_FILE_DIR:ChestnutsAndChives>)

# Recursively copy Assets folder (including textures, sounds, etc.)
file(COPY ${ASSETS_DIR} DESTINATION ${OUTPUT_DIR})