## CMake Compilation instructions

### Prerequisites

Having CMake (and a C++ compiler) installed. E.g. of CMake installation:  

```shell
sudo apt install cmake  
```

### Create build folder

```shell
cd MUII-ATR-Reto1  
mkdir build  
cd build  
```

### Configuring CMake with CMakeLists.txt

From the **build** folder, execute  
```shell
cmake ..  
```

### Building the project

From the **build** folder, execute  

```shell
cmake --build .
```