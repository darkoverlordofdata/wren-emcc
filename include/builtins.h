#include "io/io.h"
#include "math/math.h"
#include "script.h"
#include <Block.h>
#include <cfw.h>
#include <stdio.h>
#include <wren.h>

/**
 * native builtin class bindings
 */
const static WrenScript builtIns[] = {
    { "lib/io/path", "Path", io_path_Allocate, io_path_Finalize,
        {
            { "+Absolute", io_path_Absolute },
            { "+Relative", io_path_Relative },
            { "+Simple", io_path_Simple },
            { "+Cwd", io_path_Cwd },
            { "+Type(_)", io_path_Type },
            { "DirName()", io_path_DirName },
            { "RemoveExtension()", io_path_RemoveExtension },
            { "Join(_)", io_path_Join },
            { "AppendChar(_)", io_path_AppendChar },
            { "AppendString(_)", io_path_AppemdString },
            { "Normalize()", io_path_Normalize },
            { "ToString()", io_path_ToString },
        } },
    { "lib/io/stream", "Stream", io_stream_Allocate, io_stream_Finalize,
        {
            { "Write(_)", io_stream_Write },
            { "Read()", io_stream_Read },
            { "Close()", io_stream_Close },
        } },
    { "lib/io/file", "File", io_file_Allocate, io_file_Finalize,
        {} },
    { "lib/math/vec2", "Vec2", math_vec2_allocate, math_vec2_finalize,
        {
            { "x", math_vec2_get_x },
            { "x=(_)", math_vec2_set_x },
            { "y", math_vec2_get_y },
            { "y=(_)", math_vec2_set_y },
            { "norm()", math_vec2_norm },
            { "dot(_)", math_vec2_dot },
            { "clamp(_,_)", math_vec2_clamp },
            { "length()", math_vec2_length },
            { "norm2()", math_vec2_norm2 },
            { "normalize()", math_vec2_normalize },
        } },
    { "lib/math/vec3", "Vec3", math_vec3_allocate, math_vec3_finalize,
        {
            { "x", math_vec3_get_x },
            { "x=(_)", math_vec3_set_x },
            { "y", math_vec3_get_y },
            { "y=(_)", math_vec3_set_y },
            { "z", math_vec3_get_z },
            { "z=(_)", math_vec3_set_z },
            { "norm()", math_vec3_norm },
            { "dot(_)", math_vec3_dot },
            { "clamp(_,_)", math_vec3_clamp },
            { "length()", math_vec3_length },
            { "norm2()", math_vec3_norm2 },
            { "normalize()", math_vec3_normalize },
        } },
    { "lib/math/vec4", "Vec4", math_vec4_allocate, math_vec4_finalize,
        {
            { "x", math_vec4_get_x },
            { "x=(_)", math_vec4_set_x },
            { "y", math_vec4_get_y },
            { "y=(_)", math_vec4_set_y },
            { "z", math_vec4_get_z },
            { "z=(_)", math_vec4_set_z },
            { "w", math_vec4_get_w },
            { "w=(_)", math_vec4_set_w },
            { "norm()", math_vec4_norm },
            { "dot(_)", math_vec4_dot },
            { "length()", math_vec4_length },
            { "norm2()", math_vec4_norm2 },
            { "clamp()", math_vec4_clamp },
        } },
    { "lib/math/mat", "Mat", math_mat_allocate, math_mat_finalize,
        {
            { "identity()", math_mat_identity },
            { "scale(_)", math_mat_scale },
            { "ortho(_,_,_,_,_,_)", math_mat_ortho },
            { "rotate(_,_)", math_mat_rotate },
            { "[_,_]", math_mat_get },
            { "[_,_]=(_)", math_mat_set }
        } },
    // "lib/dna/game", "GameDelegate", dna_game_Allocate, dna_game_Finalize,
    // {
    //     { "DoUpdate()", dna_game_DoUpdate },
    //     { "DoDraw()", dna_game_DoDraw },
    //     { "Tick()", dna_game_Tick },
    //     { "Dispose()", dna_game_Dispose },
    //     { "HandleEvents()", dna_game_HandleEvents },
    //     { "Start()", dna_game_Start },
    //     { "Run()", dna_game_Run },
    //     { "RunLoop()", dna_game_RunLoop },
    // } },
};
