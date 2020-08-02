#pragma once
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <corefw/corefw.h>

typedef struct DNAGame DNAGame;
struct DNAGameVtbl;
extern const CFWClass* DNAGameClass;

extern DNAGame* DNAGame_instance;

typedef void (*DNAGameProc)(void* self);
struct DNAGameVtbl {
    void (*Initialize)(void* self);
    void (*LoadContent)(void* self);
    void (*Update)(void* self);
    void (*Draw)(void* self);
};

// extern void* DNAGame_ctor(DNAGame* this, char* cstr, int width, int height, void* subclass, struct DNAGameVtbl* vptr);

extern method void* New(DNAGame* this, char* cstr, int width, int height, void* subclass, struct DNAGameVtbl* vptr);

/**
 * DNAGame::HandleEvents
 */
extern method void HandleEvents(DNAGame* const this);

extern method char* ToString(DNAGame* this);

/**
 * DNAGame::Start
 */
extern method void Start(DNAGame* const this);

/**
 * DNAGame::Tick
 */
extern method void Tick(DNAGame* const this);

/**
 * DNAGame::RunLoop
 */
extern method void RunLoop(DNAGame* const this);

/**
 * DNAGame::Run
 */
extern method void Run(DNAGame* const this);

/**
 * DNAGame::Initialize
 */
extern method void Initialize(DNAGame* const this);

/**
 * DNAGame::LoadContent
 */
extern method void LoadContent(DNAGame* const this);

/**
 * DNAGame::Update
 */
extern method void Update(DNAGame* const this);

/**
 * DNAGame::Draw
 */
extern method void Draw(DNAGame* const this);
