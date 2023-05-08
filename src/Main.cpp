#include "Application/Application.h"

int main() {
	Application app;
	app.Run();

	return 0;
}













// ===== TODOS IN FAR FAR FUTURE ======
// == lights ==
// ShadowMaps
// Volumetric lightning (Cones?)
// Bloom
// 
// == Batching ==
// ?Shader/texture/material batching? https://realtimecollisiondetection.net/blog/?p=86
// Instanced static meshes (HISM?)
// Precalculate position straight into Vertex (on CPU)? (Performance++ but only for static/unmovable objects? - Would use BIG VAOs with minimum draw calls and state switches)
// 
// == Performance ==
// For Custom ECS - Either Switch to Unity's archetypes from SparseSets (faster iterations + easier to implement, but worse in Add/removes)
// Or continue with SparseSets - Needs sorting, grouping, custom iterators, Entity recycling, paging (for not wasting memory) 
// Or just use existing library - "entt" (SparseSet based)
// Make components connect/disconnect at runtime (+ prefabs)
// structure padding
//
// == Collisions ==
// AABB
// RayCasting
// Convex collision - QuickHull?
// 
// == Optimization ==
// ?Dirty system?
// Culling (Occlusion, frustum, face)
// Deffered shading
// LOD, mipmapping
// 
// == GUI ==
// Use something better/havier than ImGui? Might be an overkill
// 
// == Other ==
// Threading + manager (Learn more about mutexes)
// Serialization + Custom formats + importing + completely rework AssetLibarries + ContentBrowser? (Keep QOL things to minimum? Eyes on the important stuff...)
// Hierarchy for entitites (Must have, but harder with ECS?)
// Audio/Physics - Use library
// Logging, Configs, RigidBodies, Gizmos, CommandSystem(undo/redo) ....... ?LevelStreaming? 

// ===== Great book of bugs =====
// Camera starts glitching while looking all the way up/down (Scene camera could propably be unlocked/not constrained)
// LSystems act wierd in some cases with threading (threads finish at different times - When writing something async, always think with threading already in mind)
// Crash on level change, while threads are running - Propably needs manager with auto cleanup of threads (For now solved with hardcoded thread synchronization)
// While removing lights the effects still persists in the scene (Do some automatic uniform cleaning?)

// ===== Big book of hacks =====
// == ECS ==
// Custom SparseSet data structure is unfinished (missing sorting, grouping, iterators)
// so the functionality is pretty limited and most stuff is accessed by indirection,
// but it is still faster than OOP approach (not by a lot in such a small app :D)
// Destroying entities is bad - it iterates through all components (owning, but also not owning) and tries to delete it. Create getter
// for all owning components
// 
// Some objects were not converted to components yet (looking at you Camera)
// Some Components have Getters/Setters, some even contain logic - unite the rules, now its a mess
// Split components in multiple files
//
// Rewrite using unsigned ints (uint32_t)
// DeMonolithize structure
// Use Quaternions (Beware the gimbal lock)
// Rename Math folder to Utility 
// Scene is not ticking - it propably should which could even remove some bloat from Application.cpp (Also scene should contain a lot more stuff, 
// as Levels should only be some generic data holders)
// Rework event system (Dispatchers, dispatch queues, registrations, priorities etc...)
//
// Shaders - lights only work with textures now (they can't be empty) - create combinations (only colors, only textures, mix?), create a material system? This is gonna be a headscratcher (Now there is one big shader that does a lot of stuff)
// Also shaders can't be created on the fly (renderer needs to be updated),
// material systems might partially solve this? But each shader needs different renderer (commands - GL_LEQUAL/GL_LESS or uniforms,
// as some shaders only need specific uniforms to be uploaded, or some even share data (should be solved by UBOs))
//
// Number of pointLights is defined statically - find a good way to make it dynamic (than apply it to other lights and various systems)



//that could be enough to make Tetris at least :D 