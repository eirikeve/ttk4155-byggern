add_executable(test_example_app
    test_example.c
)
 
target_link_libraries(test_example_app
    src
    Unity
)
 
add_test(test_example_test test_example_app)