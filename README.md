# hashserver
sha256 calculation server

Required packages to build: cmake, g++, boost and openssl
```
sudo apt install cmake g++ libboost-all-dev libssl-dev
```
Build from build folder:
```
cmake -DCMAKE_BUILD_TYPE=Release <path_to_this_file_location>
make all
```
Run:
```
hashserver <port>
```
Run tests:
```
ctest
```
