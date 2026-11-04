cmake_minimum_required(VERSION 3.15)
project(PolyglotDemo LANGUAGES C ASM_NASM)
set(CMAKE_ASM_NASM_FLAGS "-f macho64")

# Point to the macOS slice inside the xcframework
set(SDL3_FRAMEWORK "${CMAKE_CURRENT_SOURCE_DIR}/SDL3.xcframework/macos-arm64_x86_64/SDL3.framework")
# 🚀 ADD THIS: Point to the SDL3_mixer framework
set(SDL3_MIXER_FRAMEWORK "${CMAKE_CURRENT_SOURCE_DIR}/SDL3_mixer.xcframework/macos-arm64_x86_64/SDL3_mixer.framework")

set(SDL3_TTF_FRAMEWORK "${CMAKE_CURRENT_SOURCE_DIR}/SDL3_ttf.xcframework/macos-arm64_x86_64/SDL3_ttf.framework")

set(SDL3_Image_FRAMEWORK "${CMAKE_CURRENT_SOURCE_DIR}/SDL3_image.xcframework/macos-arm64_x86_64/SDL3_image.framework")
# Find macOS Built-in OpenGL Framework
find_library(OPENGL_LIBRARY OpenGL REQUIRED)

# 🚀 UPDATE THIS: Include both SDL3 and SDL3_mixer headers
include_directories(
        "${SDL3_FRAMEWORK}/Headers"
        "${SDL3_MIXER_FRAMEWORK}/Headers"

        "${SDL3_TTF_FRAMEWORK}/Headers"
        "${SDL3_Image_FRAMEWORK}/Headers"
)

# 1. Define ELPL Compiler properties
set(ELPL_JAR_PATH "/Users/apple/Projects/ELPL 2/elpl-compiler.jar")
set(ELPL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/TunnelGame.elpl")
set(ELPL_OBJECT "${CMAKE_CURRENT_BINARY_DIR}/TunnelGame.o")

# 2. Tell CMake how to build ELPL using your -c flag
add_custom_command(
        OUTPUT ${ELPL_OBJECT}
        COMMAND java -jar "${ELPL_JAR_PATH}" --native -c "${ELPL_SOURCE}" -o "${CMAKE_CURRENT_BINARY_DIR}"
        DEPENDS "${ELPL_SOURCE}"
        COMMENT "Compiling ELPL to Native Object..."
)

# 3. Build the final app: ELPL + C + Assembly
add_executable(ArcadeDodger
       # coprocessor.asm
        ${ELPL_OBJECT}
        # canvas.c
)

# Force Clang to handle the final linkage & link frameworks
set_target_properties(ArcadeDodger PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(ArcadeDodger PRIVATE
        "${SDL3_FRAMEWORK}"
        "${SDL3_MIXER_FRAMEWORK}"
        "${SDL3_Image_FRAMEWORK}"
        "${SDL3_TTF_FRAMEWORK}"
        "${OPENGL_LIBRARY}"
)