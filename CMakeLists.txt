cmake_minimum_required(VERSION 3.10)

project(xmos-test C ASM)
set(CMAKE_C_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.*")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_options(${PROJECT_NAME} PRIVATE -target=XCORE-AI-EXPLORER)

set(OUTPUT_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.xe)
execute_process(COMMAND which xrun OUTPUT_VARIABLE XRUN_PATH)
string(STRIP ${XRUN_PATH} XRUN_PATH)

add_custom_target(run 
        COMMAND "${XRUN_PATH}" "${OUTPUT_FILE}"
        DEPENDS ${PROJECT_NAME}
        COMMENT "Running ${PROJECT_NAME}.xe using xrun"
)
