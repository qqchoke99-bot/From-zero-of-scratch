#include "GameHooks.hpp"

#include "core/memory/Hooks.hpp"
#include <cameraoverhaul/events/EventBus.hpp>
#include <cameraoverhaul/events/FrameEvent.hpp>
#include <cameraoverhaul/events/LocalPlayerTickEvent.hpp>
#include <cameraoverhaul/memory/Signatures.hpp>
#include <cameraoverhaul/sdk/world/Actor.hpp>

#include <EGL/egl.h>
#include <dlfcn.h>
#include <mutex>

namespace cameraoverhaul::core::gamehooks {
namespace {
using namespace cameraoverhaul::events;
using cameraoverhaul::memory::SignatureId;

using NormalTickFn = void (*)(void*);
using EglSwapBuffersFn = EGLBoolean (*)(EGLDisplay, EGLSurface);

NormalTickFn tickOriginal = nullptr;
EglSwapBuffersFn swapBuffersOriginal = nullptr;

std::mutex installMutex;
bool installed = false;

void tickDetour(void* actor) {
    if (tickOriginal) tickOriginal(actor);
    LocalPlayerTickEvent event{reinterpret_cast<cameraoverhaul::sdk::Player*>(actor)};
    bus().publish(event);
}

EGLBoolean swapBuffersDetour(EGLDisplay display, EGLSurface surface) {
    FrameEvent event{};
    bus().publish(event);
    return swapBuffersOriginal ? swapBuffersOriginal(display, surface) : EGL_FALSE;
}

void hookEgl() {
    void* handle = cameraoverhaul::hooks::openLibrary("libEGL.so");
    if (!handle) return;
    void* symbol = reinterpret_cast<void*>(cameraoverhaul::hooks::symbol(handle, "eglSwapBuffers"));
    if (symbol) {
        cameraoverhaul::hooks::install(symbol, reinterpret_cast<void*>(swapBuffersDetour),
                                       reinterpret_cast<void**>(&swapBuffersOriginal));
    }
    cameraoverhaul::hooks::closeLibrary(handle);
}
}

bool install() {
    std::lock_guard lock(installMutex);
    if (installed) return true;

    const auto tick = cameraoverhaul::memory::resolve(SignatureId::NormalTick);
    if (tick) {
        cameraoverhaul::hooks::install(reinterpret_cast<void*>(tick),
                                       reinterpret_cast<void*>(tickDetour),
                                       reinterpret_cast<void**>(&tickOriginal));
    }

    hookEgl();

    installed = tickOriginal != nullptr;
    return installed;
}

}
