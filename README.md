g++ webshazam.c -o webshazam $(pkg-config --libs --cflags webkit2gtk-4.0 webkit2gtk-web-extension-4.0 gio-2.0)