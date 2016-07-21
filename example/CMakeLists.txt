
if (NOT CMAKE_COMPILER_IS_MSVC)

    add_executable(example example.cpp)

    # The example defines lots of unused variables to demonstrate things,
    # so turn off warnings for these
    if (CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(example PRIVATE "-Wno-unused-but-set-variable")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(example PRIVATE "-Wno-unused-variable")
    endif()

endif()