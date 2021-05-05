Simple GTK + webkit web browser which is written in C++ that has only one responsibility

# TAKING SCREENSHOTS

## Why
I got inspired by:
- https://github.com/fengidri/gethar
- https://github.com/hrnr/surf
- https://github.com/bthachdev/web_browser

to solve problem of simple web browser that can make screenshots in parallel and not eat
whole RAM/CPU of my server.

And also I wanted to check what's the state of C++ in 2021.

## Todo

- Add proper close after screenshot is taken
- Remove delay for screenshot and replace it with JS sniffer that will trigger screenshot
    when whole page is loaded

## Compile

g++-10 webshazam.c -o webshazam $(pkg-config --libs --cflags webkit2gtk-4.0 webkit2gtk-web-extension-4.0 gio-2.0)