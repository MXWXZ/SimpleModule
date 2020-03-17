# SimpleModule
Hello world kernal module

## Build
- install your kernal version header package(test kernal `5.4.24-1-MANJARO`)
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