# Realistic Head Bob (1.26.50+)

Built on **CameraOverhaul 1.1.3-beta-1.26.50** hooks (confirmed working path for 1.26.50 / nearby 1.26.52).

## Features

- **Step head-bob** (modes: default / bodycam / comfort / custom)
- Original cinematic pitch / roll / idle sway

## Install

1. LeviLauncher  
2. Import `RealisticHeadBob.levipack`  
3. Minecraft **1.26.50** or **1.26.52** (same signature set as CO 1.26.50)

## Config

```text
/sdcard/games/CameraOverhaul/config.json
```
(key group still `RealisticHeadBob` after rename)

Or in-game Mod Menu if PL menu works on your Levi version.

## Build

```sh
xmake f -y -p android -a arm64-v8a -m release --ndk=/path/to/ndk
xmake -y
```

GitHub Actions: push → workflow Build → artifact `RealisticHeadBob.levipack`

## Credits

- Camera hooks / signatures: CameraOverhaul Bedrock (GPL-3.0)
- Step bob: Realistic Head Bobbing style spring-damper
