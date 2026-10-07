#include "ModMenu.hpp"

#include "config/ConfigManager.hpp"
#include "module/CameraOverhaulModule.hpp"

#include <pl/ModMenu.hpp>
#include <cstdlib>
#include <string>

namespace {

void onToggle(std::string_view, bool enabled) {
    CameraOverhaulModule::get().setEnabled(enabled);
    cameraoverhaul::config::ConfigManager::get().save();
}

void onConfigChanged(std::string_view, std::string_view key, std::string_view value) {
    auto& mod = CameraOverhaulModule::get();

    nlohmann::json j;
    mod.saveConfig(j);

    const std::string safeKey(key);
    const std::string safeValue(value);

    if (!safeValue.empty()) {
        try {
            if (j.contains(safeKey)) {
                if (j[safeKey].is_boolean()) {
                    if (safeValue == "true") j[safeKey] = true;
                    else if (safeValue == "false") j[safeKey] = false;
                } else if (j[safeKey].is_number_float()) {
                    char* end = nullptr;
                    const float parsed = std::strtof(safeValue.c_str(), &end);
                    if (end != safeValue.c_str()) j[safeKey] = parsed;
                } else if (j[safeKey].is_number_integer()) {
                    char* end = nullptr;
                    const long parsed = std::strtol(safeValue.c_str(), &end, 10);
                    if (end != safeValue.c_str()) j[safeKey] = static_cast<int>(parsed);
                } else {
                    j[safeKey] = safeValue;
                }
            }
        } catch (...) {
            return;
        }
    }

    mod.loadConfig(j);
    cameraoverhaul::config::ConfigManager::get().save();
}

std::string f(float value) {
    return std::to_string(value);
}

} // namespace

void registerWithLauncher() {
    auto& mod = CameraOverhaulModule::get();

    pl::modmenu::ModuleBuilder builder{std::string(CameraOverhaulModule::moduleId),
                                       std::string(CameraOverhaulModule::name)};

    builder.description("Step head-bob + cinematic pitch/roll/sway (1.26.50+)")
           .defaultEnabled(mod.enabled())
           .hideInHudEditor(true)
           .onToggle(onToggle)
           .onConfigChanged(onConfigChanged);

    using pl::modmenu::ConfigType;

    // Same config() shape as original CameraOverhaul only:
    //   Toggle:  (id, label, Toggle, default)
    //   Slider:  (id, label, SliderFloat, default, min, max, dependsOn)

    builder.config("enablePitch", "Pitch", ConfigType::Toggle,
                   mod.m_enablePitch ? "true" : "false");
    builder.config("forwardPitchIntensity", "Forward Pitch Intensity", ConfigType::SliderFloat,
                   f(mod.m_forwardPitchIntensity), "0.0", "3.0", "enablePitch");
    builder.config("forwardPitchSmoothing", "Forward Pitch Smoothing", ConfigType::SliderFloat,
                   f(mod.m_forwardPitchSmoothing), "0.1", "5.0", "enablePitch");
    builder.config("verticalPitchIntensity", "Vertical Pitch Intensity", ConfigType::SliderFloat,
                   f(mod.m_verticalPitchIntensity), "0.0", "3.0", "enablePitch");
    builder.config("verticalPitchSmoothing", "Vertical Pitch Smoothing", ConfigType::SliderFloat,
                   f(mod.m_verticalPitchSmoothing), "0.1", "5.0", "enablePitch");

    builder.config("enableRoll", "Roll", ConfigType::Toggle,
                   mod.m_enableRoll ? "true" : "false");
    builder.config("turningRollIntensity", "Turning Roll Intensity", ConfigType::SliderFloat,
                   f(mod.m_turningRollIntensity), "0.0", "3.0", "enableRoll");
    builder.config("turningRollAccumulation", "Turning Roll Accumulation", ConfigType::SliderFloat,
                   f(mod.m_turningRollAccumulation), "0.0", "3.0", "enableRoll");
    builder.config("turningRollSmoothing", "Turning Roll Smoothing", ConfigType::SliderFloat,
                   f(mod.m_turningRollSmoothing), "0.1", "5.0", "enableRoll");
    builder.config("strafingRollIntensity", "Strafing Roll Intensity", ConfigType::SliderFloat,
                   f(mod.m_strafingRollIntensity), "0.0", "3.0", "enableRoll");

    builder.config("enableSway", "Idle Sway", ConfigType::Toggle,
                   mod.m_enableSway ? "true" : "false");
    builder.config("swayIntensity", "Sway Intensity", ConfigType::SliderFloat,
                   f(mod.m_swayIntensity), "0.0", "3.0", "enableSway");
    builder.config("swayFrequency", "Sway Frequency", ConfigType::SliderFloat,
                   f(mod.m_swayFrequency), "0.1", "5.0", "enableSway");
    builder.config("swayFadeInDelay", "Sway Fade In Delay", ConfigType::SliderFloat,
                   f(mod.m_swayFadeInDelay), "0.0", "15.0", "enableSway");
    builder.config("swayFadeInLength", "Sway Fade In Length", ConfigType::SliderFloat,
                   f(mod.m_swayFadeInLength), "0.1", "15.0", "enableSway");
    builder.config("swayFadeOutLength", "Sway Fade Out Length", ConfigType::SliderFloat,
                   f(mod.m_swayFadeOutLength), "0.1", "15.0", "enableSway");

    builder.config("transitionSmoothing", "Overall Smoothness", ConfigType::SliderFloat,
                   f(mod.m_transitionSmoothing), "0.2", "4.0");

    // Head bob
    // Radio API (from pl/ModMenu.hpp):
    //   config(key, name, type, defaultValue, minValue, maxValue, dependsOn)
    // For Radio, option list goes in minValue as comma-separated values.
    builder.config("enableHeadBob", "Head Bob", ConfigType::Toggle,
                   mod.m_enableHeadBob ? "true" : "false");
    builder.config("headBobMode", "Head Bob Mode", ConfigType::Radio,
                   mod.m_headBobMode.empty() ? "bodycam" : mod.m_headBobMode,
                   "default,bodycam,comfort,custom",
                   "",
                   "enableHeadBob");
    builder.config("headBobStrength", "Head Bob Strength", ConfigType::SliderFloat,
                   f(mod.m_headBobStrength), "0.0", "3.0", "enableHeadBob");
    builder.config("headBobStepRate", "Step Rate", ConfigType::SliderFloat,
                   f(mod.m_headBobStepRate), "0.25", "2.5", "enableHeadBob");
    builder.config("headBobSmoothHz", "Head Bob Smooth Hz", ConfigType::SliderFloat,
                   f(mod.m_headBobSmoothHz), "0.25", "6.0", "enableHeadBob");
    builder.config("headBobDamping", "Head Bob Damping", ConfigType::SliderFloat,
                   f(mod.m_headBobDamping), "0.1", "3.0", "enableHeadBob");

    builder.registerModule();
}
