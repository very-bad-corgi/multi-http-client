# Installing Dependencies

Boost.Asio
```
sudo apt-get install libboost-all-dev
```

Если требуется произвести сборку зависимостей
```
export CC=clang
export CXX=clang++

conan install . --remote=conancenter --build=fmt/11.0.2 --build=libcurl/8.8.0 --build=openssl/3.2.2 --build=zlib/1.3.1 --build=libtool/2.4.7
```
