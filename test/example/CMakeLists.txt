add_executable(test_example_app
    test_example.c
)
 
target_link_libraries(test_example_app
    example
    Unity
)
 
add_test(test_example test_example_app)