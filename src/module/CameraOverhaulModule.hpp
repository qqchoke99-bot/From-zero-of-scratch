#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <string_view>

class CameraOverhaulModule {
public:
    static CameraOverhaulModule& get();

    static constexpr std::string_view name = "RealisticHeadBob";
    static constexpr std::string_view moduleId = "realistic_headbob.camera";

    void init();
    void setEnabled(bool state);
    bool enabled() const { return m_enabled; }

    void onTick(void* player);
    void applyToCamera(void* cameraComponent);

    void loadConfig(const nlohmann::json& j);
    void saveConfig(nlohmann::json& j);

    void resetState();

    bool  m_enabled = true;

    // --- cinematic (CameraOverhaul) ---
    bool  m_enablePitch = true;
    float m_forwardPitchIntensity = 1.0f;
    float m_forwardPitchSmoothing = 1.0f;
    float m_verticalPitchIntensity = 1.0f;
    float m_verticalPitchSmoothing = 1.0f;

    bool  m_enableRoll = true;
    float m_turningRollIntensity = 1.0f;
    float m_turningRollAccumulation = 1.0f;
    float m_turningRollSmoothing = 1.0f;
    float m_strafingRollIntensity = 1.0f;

    bool  m_enableSway = true;
    float m_swayIntensity = 1.0f;
    float m_swayFrequency = 1.0f;
    float m_swayFadeInDelay = 3.0f;
    float m_swayFadeInLength = 4.0f;
    float m_swayFadeOutLength = 1.0f;

    float m_transitionSmoothing = 1.0f;

    // --- realistic step head-bob ---
    bool        m_enableHeadBob = true;
    std::string m_headBobMode = "bodycam"; // default | bodycam | comfort | custom
    float       m_headBobStrength = 1.0f;
    float       m_headBobStepRate = 1.0f;
    float       m_headBobSmoothHz = 1.75f;
    float       m_headBobDamping = 1.25f;

private:
    CameraOverhaulModule() = default;

    bool m_hooked = false;
};
