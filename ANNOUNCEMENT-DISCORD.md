# Discord announcement — CameraOverhaul v1.1.0-beta

Copy the block below and paste it straight into Discord. Formatting is ready to go.

---

# CameraOverhaul — v1.1.0-beta

### Cinematic camera for Minecraft Bedrock

> Your camera stops being a static block. It **tilts** when you accelerate, **rolls** when you turn, and **breathes** when you stand still.

**Author:** `DrukisMC`
**Platform:** Minecraft Bedrock (Android · arm64)
**Loader:** LeviLauncher
**License:** GPL-3.0

## Download

**[Download CameraOverhaul.levipack](https://www.mediafire.com/file/tya11c4gnalecrm/CameraOverhaul.levipack/file)**

Source code: <https://github.com/DrukisMC/CameraOverhaul>

## Health warning — please read first

> ### This mod can cause motion sickness and nausea
>
> It directly alters camera movement. This can trigger **motion sickness**, nausea, dizziness, headaches, eye strain or disorientation — **even in people who have never experienced it before**.
>
> **Do not use it if you:**
> - are sensitive to motion sickness or travel sickness
> - have migraines, vertigo, or any vestibular disorder
> - have photosensitive epilepsy or a history of seizures
> - are pregnant, unwell, tired, or under the influence of alcohol
>
> **If you feel any discomfort, stop immediately.** Do not try to "push through it" — that usually makes it worse. Symptoms can persist for a while after you close the game.

### How to use it safely

**Start with the comfort preset, not the defaults:**

```
Overall Smoothness ......... 2.0
Forward Pitch Intensity .... 0.4
Vertical Pitch Intensity ... 0.3
Turning Roll Intensity ..... 0.4
Strafing Roll Intensity .... 0.4
Sway Intensity ............. 0.5
```

- Play for **10 to 15 minutes** and see how you feel
- Only raise values if you are completely comfortable, in steps of **0.2**
- Take a break every 30 minutes
- Play in a well-lit room, holding the device further from your face

**Every effect can be turned off.** Set any intensity to `0`, or use the **Pitch**, **Roll** and **Idle Sway** toggles to disable whole groups. Turn off all three and the mod becomes completely inert.

## What it does

**Movement pitch**
The camera tips forward as you accelerate and lifts as you fall, scaled by your real velocity.
`~2.5 degrees sprinting` · `~13.5 degrees in an elytra dive` · `~6 degrees at terminal fall speed`

**Turning roll**
Turning banks the camera into the corner, like a pilot rolling through a turn. Strafing adds its own roll.
`~11 degrees peak on hard turns`

**Idle sway**
Stand still and the camera begins to drift gently, like someone breathing. It fades out the instant you move.

## Configuration

**17 controls** in the LeviLauncher menu, organised into 3 groups. Disabling a group hides its controls.

| Group | Controls |
|---|---|
| **Pitch** | Intensity and smoothing (forward + vertical) |
| **Roll** | Intensity, accumulation, smoothing, strafing |
| **Idle Sway** | Intensity, frequency, delay, fade in/out timings |

**Overall Smoothness** adjusts the weight of the entire camera at once.
`Higher` = heavier and more cinematic · `Lower` = snappier and more responsive

**Suggested presets:**
```
Comfort ......... Smoothness 2.0 · Pitch 0.4 · Roll 0.4
Default ......... everything at 1.0
Cinematic ....... Smoothness 1.5 · Pitch 1.5 · Roll 1.4
```

## Is it safe on servers?

**Yes.** The mod **never** changes your character's actual rotation — only the visual camera transform. No movement packet is modified and nothing is sent to the server. It is purely visual and entirely client-side.

It gives no gameplay advantage: this is quality-of-life and visual polish, not a cheat.

## Under the hood

Game logic runs at **20 Hz** while rendering runs at **60 to 144 Hz**. In the first version the camera was calculated on the tick, so the same value was held for several frames and then jumped — that produced a stuttering feel.

Now the tick only publishes a **target**, and a **critically damped spring** chases that target **once per rendered frame**.

Measured result (20 Hz tick, 120 fps render):
```
before ..... 2.2743 degrees jump per frame
after ...... 0.2916 degrees jump per frame   ->  87% reduction
overshoot .. 0.000 degrees
```

The spring uses the exact closed-form solution instead of a step approximation, so it **cannot overshoot or blow up** if your frame rate drops. Tested at a steady 144 fps, a steady 30 fps, chaotic 12 to 144 fps, and across a half-second stall — stable in all of them.

Rotation is applied through **quaternion multiplication**, never converting to Euler angles. That avoids gimbal lock when you look straight up or straight down.

## Credits

Inspired by the **[CameraOverhaul](https://www.curseforge.com/minecraft/mc-mods/cameraoverhaul)** mod by **Mirsario & Contributors**, made for Minecraft Java.

This is an **independent reimplementation for Bedrock** — no code was copied. Both projects are GPL-3.0.

## Beta notice

Verified through builds, numeric simulation and static analysis, but it still has **limited real playtime**. If you hit a bug or anything feels off, reply here or open an issue on GitHub.

**Not included yet:** screen shakes (explosions, lightning). The game's native shake queue only holds 2 entries where the effect needs 64, so it requires a custom implementation. Planned for a future release.
