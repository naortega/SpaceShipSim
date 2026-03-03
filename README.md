# SpaceShipSim

This is a small simulation program of a space ship (with infinite fuel) in a
frictionless environment (space). The idea is to use it for educational
purposes.

## Compiling

In order to build this program you will require the following dependencies:

- A C compiler that supports C99 or higher
- CMake 3.10 or higher
- Allegro 5

You can then compile the program via the following commands:

```bash
cd build/
cmake ..
make
```

This will create a release build with compiler optimizations. If you would like
a debug build then pass the `-DCMAKE_BUILD_TYPE=debug` flag to the `cmake`
command. If you would like to install then run `cmake` with the additional flag
`-DCMAKE_INSTALL_PREFIX=<install_dir>`. If you are installing as a user then
you may want to set the installation prefix to `/usr/local/`, and if you're
packaging then please consult your distribution's policies. With this you
should be able to run the `make install' target and install the binary.

## Contributing

If you would like to contribute to the project, send a patch file to my e-mail
address: <nortega@themusicinnoise.net>.

## License

As educational software, unless otherwise noted, all files are licensed under
the terms & conditions of the GNU General Public License version 3 or greater
(see `LICENSE' file for more information).
