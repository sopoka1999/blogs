# godot

## 从源码编译godot引擎

For compiling under macOS, the following is required:

-   [Python 3.6+](https://www.python.org/downloads/macos/).
-   [SCons 3.0+](https://scons.org/pages/download.html) build system.
-   [Xcode](https://apps.apple.com/us/app/xcode/id497799835) (or the more lightweight Command Line Tools for Xcode).
-   [Vulkan SDK](https://sdk.lunarg.com/sdk/download/latest/mac/vulkan-sdk.dmg) for MoltenVK (macOS doesn't support Vulkan out of the box).
    适用于 MoltenVK 的 Vulkan SDK（macOS 不支持开箱即用的 Vulkan）。



## 编译

```shell
cd godot-master
scons platform=macos arch=arm64
```

