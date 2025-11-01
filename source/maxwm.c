// MaxWM.c - Simple X11 WM with floating windows & xterm spawn
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Display *dpy;
Window root;

int moving = 0;
Window moving_win = 0;
int start_x, start_y;   // Mouse start pos
int win_x, win_y;       // Window start pos

void spawn_xterm() {
    if (fork() == 0) {
        execlp("xterm", "xterm",
               "-fa", "Monocraft Nerd Font",
               "-fs", "12",
               "-geometry", "80x24+100+100",
               "-bg", "#202050", // default background
               "-fg", "#c0c0c0", // text color
               NULL);
        perror("xterm");
        exit(1);
    }
}

void setup() {
    dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
    root = DefaultRootWindow(dpy);

    XSelectInput(dpy, root,
        SubstructureRedirectMask |
        SubstructureNotifyMask |
        ButtonPressMask |
        ButtonReleaseMask |
        PointerMotionMask |
        KeyPressMask);

    spawn_xterm();
}

void run() {
    XEvent ev;

    int moving = 0;
    Window moving_win = 0;
    int start_x, start_y;   // Mouse start pos
    int win_x, win_y;       // Window start pos

    while (1) {
        XNextEvent(dpy, &ev);

        switch (ev.type) {

            case MapRequest: {
                XMapRequestEvent *e = &ev.xmaprequest;
                Window w = e->window;

                XMapWindow(dpy, w);
                XMoveResizeWindow(dpy, w, 100, 100, 800, 600);
                XSetWindowBorderWidth(dpy, w, 2);
                XSetWindowBorder(dpy, w, WhitePixel(dpy, DefaultScreen(dpy)));

                XSetInputFocus(dpy, w, RevertToPointerRoot, CurrentTime);
                XSelectInput(dpy, w, ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
                break;
            }

            case ButtonPress: {
                XButtonEvent *be = &ev.xbutton;
                Window w = be->subwindow ? be->subwindow : be->window;

                // SUPER + left click = "bone mode" drag
                if ((be->state & Mod4Mask) && be->button == Button1) {
										moving = 1;
										moving_win = w;
										start_x = be->x_root;
										start_y = be->y_root;

										XWindowAttributes attr;
										XRaiseWindow(dpy, moving_win);
										XGetWindowAttributes(dpy, moving_win, &attr);
										win_x = attr.x;
										win_y = attr.y;

										// Disable normal window input temporarily
										XGrabPointer(dpy, moving_win, True,
																 PointerMotionMask | ButtonReleaseMask,
																 GrabModeAsync, GrabModeAsync,
																 None, None, CurrentTime);
								}
                break;
            }

            case MotionNotify: {
                if (moving) {
                    XMotionEvent *me = &ev.xmotion;
                    int dx = me->x_root - start_x;
                    int dy = me->y_root - start_y;
                    XMoveWindow(dpy, moving_win, win_x + dx, win_y + dy);
                }
                break;
            }

            case ButtonRelease: {
                if (moving && ev.xbutton.button == Button1) {
                    moving = 0;
                    moving_win = 0;

                    XUngrabPointer(dpy, CurrentTime);
                    XUngrabKeyboard(dpy, CurrentTime);
                }
                break;
            }

            case KeyPress: {
                XKeyEvent *key = &ev.xkey;
                KeySym ks = XLookupKeysym(key, 0);

                // Ctrl+Shift+Escape = exit WM
                if ((ks == XK_Escape) && ((key->state & (ControlMask | ShiftMask)) == (ControlMask | ShiftMask))) {
                    XCloseDisplay(dpy);
                    exit(0);
                }

                // SUPER + Enter = spawn xterm
                else if ((ks == XK_Return) && ((key->state & Mod4Mask) == Mod4Mask)) {
                    spawn_xterm();
                }

                // SUPER + R = spawn rofi
                else if ((ks == XK_r) && (key->state & Mod4Mask)) {
                    if (fork() == 0) execlp("rofi", "rofi", "-show", "drun", "-display", ":2", NULL);
                }
                break;
            }

            case DestroyNotify: {
                if (ev.xdestroywindow.window == moving_win) moving_win = 0;
                break;
            }
        }
    }
}

int main() {
    setup();
    run();
    return 0;
}
