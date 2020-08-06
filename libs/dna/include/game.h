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

extern overloadable void* New(DNAGame* this, char* cstr, int width, int height, void* subclass, struct DNAGameVtbl* vptr);

/**
 * DNAGame::HandleEvents
 */
extern overloadable void HandleEvents(DNAGame* const this);

extern overloadable char* ToString(DNAGame* this);

/**
 * DNAGame::Start
 */
extern overloadable void Start(DNAGame* const this);

/**
 * DNAGame::Tick
 */
extern overloadable void Tick(DNAGame* const this);

/**
 * DNAGame::RunLoop
 */
extern overloadable void RunLoop(DNAGame* const this);

/**
 * DNAGame::Run
 */
extern overloadable void Run(DNAGame* const this);

/**
 * DNAGame::Initialize
 */
extern overloadable void Initialize(DNAGame* const this);

/**
 * DNAGame::LoadContent
 */
extern overloadable void LoadContent(DNAGame* const this);

/**
 * DNAGame::Update
 */
extern overloadable void Update(DNAGame* const this);

/**
 * DNAGame::Draw
 */
extern overloadable void Draw(DNAGame* const this);
