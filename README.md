Minerva
=======

This is a client for rAthena. It will be super stripped down and look nothing like the current clients, but we want performance.

This is based on Linkz's [Dolori](https://gitlab.com/Dolori/Dolori). Check it out!

External dependencies
---------------------
* OpenGL
* DevIL
* SDL2_ttf

Build
-----
```shell
$ mkdir build && cd build
$ cmake ..
$ cmake --build . --config Debug
```

Current supported settings
--------------------------
* Packet version: 20130807
* Packet obfuscation: Disabled
* Client version: 45

Configuration file
------------------
Minerva uses a JSON file to store its configuration (graphics, sound, fonts, etc.).
Here's what its content might look like:

```json
{
  "graphics": {
    "fullscreen": false,
    "window_width": 800,
    "window_height": 600,
    "vsync": false,
    "msaa": 4
  },
  "fonts": {
    "font_folder": "/usr/share/fonts/truetype/msttcorefonts/"
  }
}
```
