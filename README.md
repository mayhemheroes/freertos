# Mayhem Harnessing for FreeRTOS

## Building and Running

First run cmake configuration with (note it will take some time without any output as during the process it will fetch FreeRTOS and other dependencies):
```
cmake -B mayhem .
# don't worry it didn't hang, just wait for it
```
Now you can either build all harness with:
```
cmake --build mayhem
```
You can also build a specific harness:
```
cmake --build mayhem --target <name>
```

Each harness will have the following structure:
```
mayhem/harnesses/<target>/
|-- Mayhemfile
`-- root
    `-- <target>
```

Notice, that the `Mayhemfile` is generated. There is even a
cmake target that will run it, e.g.,
```
cmake --build mayhem --target run_<target>
```
Will build and run a target with the given name.


## Adding New Harnesses

To add a new harness for target `foo` create a new folder `foo` in the harnesses directory, that contains a `harness.c` file, which implements then `int mayhem_process_input(char *buf, size_t len)` function, and then add to the top-level CMakeLists.txt a call `create_harness(foo)`.
