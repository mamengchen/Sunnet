# ! /bin/bash

# 设置路径
PROTOC=protoc
PLUGIN_LUA=plugin/protoc-gen-lua
CPP_OUT=gen/cpp
LUA_OUT=gen/lua

# 创建输出目录
mkdir -p $CPP_OUT
mkdir -p $LUA_OUT


echo "Compiling to C++..."
$PROTOC --proto_path=. --cpp_out=$CPP_OUT common/*.proto client/*.proto

echo "Compiling to Lua..."
chmod +x $PLUGIN_LUA
$PROTOC --proto_path=. --plugin=protoc-gen-lua=$PLUGIN_LUA --lua_out=$LUA_OUT common/*.proto client/*.proto