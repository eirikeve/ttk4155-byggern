add_library(node_1 STATIC
    node_1.c
)
 
target_include_directories(node_1 PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)