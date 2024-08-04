# Installing Dependencies

## 1 Boost.Asio

### 1.1 Ubuntu 
```
sudo apt install libboost-all-dev 
```

## 2. Install Shared Dependencies by Conan

### 2.1 Build
```
mkdir _build && cd _build

export CC=clang
export CXX=clang++

conan install .. --output-folder=. --remote=conancenter \
--build=fmt/11.0.2 \
--build=libcurl/8.8.0 \
--build=openssl/3.2.2 \
--build=zlib/1.3.1 \
--build=libtool/2.4.7 \
--build=inih/58
```
