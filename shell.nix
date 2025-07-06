{ pkgs ? import <nixpkgs> { } }:

with pkgs;

mkShell rec {
  nativeBuildInputs = [
    cmake
  ];

  buildInputs = [
    flac
    freetype
    glew
    libjpeg
    libvorbis
    openal
    udev
    xorg.libXi
    xorg.libX11
    xorg.libXcursor
    xorg.libXrandr
    xorg.libXrender
    xorg.xcbutilimage
  ];
}
