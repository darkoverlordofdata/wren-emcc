
add_executable ( test_main test_main.c 
                    unity/unity.c 
                    ${SOURCE} )

add_executable ( test_wren test_wren.c 
                    unity/unity.c 
                    ../src/wc/script.c  
                    ../src/wc/method.c 
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
target_link_libraries ( test_wren dl m BlocksRuntime wren corefw glfw GL )

add_test ( main test_main )                      
add_test ( wren test_wren )                      


