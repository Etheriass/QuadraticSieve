file(GLOB BENCH_SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(BENCH_TARGETS "")  # to keep a list of benchmark executables

foreach(bench_file ${BENCH_SRC})
    get_filename_component(bench_name ${bench_file} NAME_WE)
    add_executable(${bench_name} ${bench_file})
    target_link_libraries(${bench_name} PRIVATE qs_lib benchmark::benchmark)
    list(APPEND BENCH_TARGETS ${bench_name})
endforeach()

# Create a custom target that runs all benchmarks
add_custom_target(run_all_benchmarks
    COMMAND ${CMAKE_COMMAND} -E echo "Running all benchmarks:"
)

foreach(bench_exec ${BENCH_TARGETS})
    add_custom_command(TARGET run_all_benchmarks POST_BUILD
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${bench_exec}
        COMMENT "Running ${bench_exec}"
    )
endforeach()
