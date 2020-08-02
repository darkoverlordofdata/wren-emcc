
add_executable ( test_main test_main.c ${SOURCE} )
add_executable ( test_block test_block.c test_block/testclass.c ${SOURCE} )
add_executable ( test_wren test_wren.c 
                    ../src/script.c  
                    ../src/io/File.c
                    ../src/io/Path.c
                    ../src/io/Stream.c
                    ../src/math/Vec2.c
                    ../src/math/Vec3.c
                    ../src/math/Vec4.c
                    ../src/math/Mat.c
                    ../src/wren/path.c 
                    ${SOURCE} )

target_link_libraries ( test_main dl m BlocksRuntime corefw glfw GL )
target_link_libraries ( test_block dl m BlocksRuntime corefw glfw GL )
target_link_libraries ( test_wren dl m BlocksRuntime wren corefw glfw GL )

add_test ( main test_main )                      
add_test ( block test_block )                      
add_test ( wren test_wren )                      


