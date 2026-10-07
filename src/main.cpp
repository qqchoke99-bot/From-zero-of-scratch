#include "core/Runtime.hpp"

#include <pl/Mod.hpp>

class CameraOverhaulMod {
public:
    static CameraOverhaulMod& instance() {
        static CameraOverhaulMod mod;
        return mod;
    }

    bool load(pl::mod::ModContext& context) { return cameraoverhaul::core::Runtime::get().load(context); }
    bool enable(pl::mod::ModContext& context) { return cameraoverhaul::core::Runtime::get().enable(context); }
    bool disable(pl::mod::ModContext& context) { return cameraoverhaul::core::Runtime::get().disable(context); }
    bool unload(pl::mod::ModContext& context) { return cameraoverhaul::core::Runtime::get().unload(context); }
};

PL_REGISTER_MOD(CameraOverhaulMod, CameraOverhaulMod::instance())
