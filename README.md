# Setup
**Install Libraries**
```
vcpkg.exe install
```
**Set CMake**
```
cmake .. -DCMAKE_TOOLCHAIN_FILE=..\vcpkg\scripts\buildsystems\vcpkg.cmake
```
**Build File**
```
cmake --build .
```
# Program Output
[chat_client]
```
F:\CPP_CHAT_BOOST\build\Debug>.\chat_client.exe 127.0.0.1
Connecting to server at 127.0.0.1:12345...
Connected! Start chatting (type 'exit' to quit).
You: Hello
Server echoed: Hello

You:
```
[chat_server]
```
Chat Server started. Listening on port 12345...
New client connected! Handling connection...
Received from client: Hello
```