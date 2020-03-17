# SimpleModule
Hello world kernel module

## Build
- install your kernel version header package(test kernel `5.4.24-1-MANJARO`)
- `make`

## Test
Start server:

    lua server.lua

Load kernel module:

    sudo insmod hello.ko

You will see the hello world in server output.
Remove module and cleanup:

    sudo rmmod hello
    make clean