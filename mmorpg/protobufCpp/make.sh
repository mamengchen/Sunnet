rm -rf ./server
g++ -std=c++17 *.cc -o server -pthread -lprotobuf -lboost_system
