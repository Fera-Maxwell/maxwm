# MaxWM
**"Maximum windows. Minimum sanity."**

MaxWM is a small (and slightly cursed) tiling window manager written for X11.
It’s my own experiment in controlling windows *my way* — lightweight, fun, and probably broken in exciting new ways.

---

## ⚙️ Got
These things *actually* work (somehow):
- Picom support (kinda finicky but hey, it breathes)
- Window borders :D
- Moving windows around like a boss
- `feh` for backgrounds (because Nitrogen vanished from the repo, like my will to debug)

---

## 🚫 Don’t Got
Still missing / too lazy to add (for now):
- Workspaces (coming soon-ish?)
- Wayland support (ew, no)
- Rofi
- Kitty
- Animations (you want eye candy? get KDE ;3)

---

## 🧠 Will Add
Plans for world domination:
- Workspaces (and if that works, scratchpad too :>)
- **maxcom** — a customized compositor tuned just for MaxWM
- On I3 when you record a window that is on another workspace it doesn't record it so I will add a keybind to make it force draw even if it is on another workspace (maybe make the scratchpad force draw even if it isn't being used)

---

## 🙅‍♂️ Won’t Add
Some things are sacred:
- Wayland support (because f*** you ;3)

---

## 🔧 Will Fix
Stuff that *should* work but doesn’t:
- Rofi (refuses to start, probably mad at X11)
- Kitty (same issue, maybe — maybe not ¯\\_(ツ)_/¯)

---

## 🖥️ How to TRY
It is just a simple thing
- 1 : Build it (Literally takes No seconds because it is 1 file) ```gcc source/maxwm.c -o maxwm -lX11```
- 2 : Run Xephyr to test it, I reccomend using it like ```Xephyr :5 -screen 800x600``` If you don't have Xephyr then download it based on your Distribution.
- 3 : Run MaxWM in the Xephyr to test yourself ```export DISPLAY=:5 && ./maxwm```
If you have Recomendations and wanna help then make ISSUES to tell me.

---

## 🧾 License
Licensed under the **Creative Commons Attribution-NonCommercial 4.0 (CC BY-NC 4.0)** license.
You can modify, fork, and use it for anything *non-commercial* — just credit me, ok? :3

---

## 💬 How to access me
If you got REAL AND WANT TO BE HEARD **LIKE REALLY HEARD**

Then dm me on Discord ```fera_maxwell```

Or email me ```kiziltasenes44@gmail.com```
