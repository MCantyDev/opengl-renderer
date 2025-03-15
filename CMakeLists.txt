cmake_minimum_required(VERSION 3.28)

# Create Project
project(OpenGLRenderer VERSION 1.0)

# Set Standards
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set Directories
set(LIBRARIES "${CMAKE_SOURCE_DIR}/Libraries/lib")
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/Project/assets")
set(MODELS_DIR "${CMAKE_SOURCE_DIR}/Project/models")
set(SHADERS_DIR "${CMAKE_SOURCE_DIR}/Project/shaders")

# Include Directories
include_directories("${CMAKE_SOURCE_DIR}/Project/include")
include_directories("${CMAKE_SOURCE_DIR}/Libraries/include")

# Get Libraries
file(GLOB_RECURSE LIBS "${LIBRARIES}/*.lib")

# Get CPP Files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/Project/src/*.cpp")
file(GLOB GLAD_SOURCE "${CMAKE_SOURCE_DIR}/Project/src/glad.c")
file(GLOB IMGUI_SOURCES "${CMAKE_SOURCE_DIR}/Libraries/include/imgui/*.cpp")

# Include Copy Files
file(COPY ${ASSETS_DIR}/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${MODELS_DIR}/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${SHADERS_DIR}/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD_SOURCE} ${IMGUI_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
	${LIBS} opengl32
)