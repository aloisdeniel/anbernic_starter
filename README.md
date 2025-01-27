![photo](doc/photo.png)

![animation](doc/screenshot.gif)

An example program based on SDL2 that is compatible with Anbernic Linux based handhelds.

> Tested on Anbernic RG35XX H

## Build

To build the program for an Anbernic device, you need to target the ARM64 architecture. The easiest way to achieve this if you're not running on this architecture is to run it from a Linux VM, like the pre-built [UTM Ubuntu Virtual Machine].

You will need at least the base tools first :

```sh
sudo apt update
sudo apt install build-essential libsdl2-dev
```

Then, simply run `make` :

```sh
make
```

This should output two files in the `build` directory : `cube` and `cube.sh`

## Deploy

To run the program on your Anbernic device, you can use the `make deploy` command.

Since this command uses SSH to send the files, make sure to enable SSH connection on your device and to update the `Makefile` with your device IP and target directory first.

Then your app should be available on your device after a library update!
