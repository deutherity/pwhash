# pwhash
generates exact same passwords based on your original password using hash algorithms
works only in linux on X11


If you want to install this, there are 2 ways
1) On archlinux download PKGBUILD and run ```makepkg -si``` inside a folder with it.
2) You also can compile this from sources. To do so ```git clone``` this repo and run inside of it ```cmake -B ./build && cmake --build ./build```. After this you may find your executable in ./build. Do whatever you want with it.

To compile it yourself you will need:
1) cmake>=3
2) openssl>=1
3) xclip>=0.13
4) way to find openssl (i use extra-cmake-modules package from archlinux) for cmake
