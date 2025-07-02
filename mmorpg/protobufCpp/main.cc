#include <boost/asio.hpp>
#include <set>
#include "chat.pb.h"

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace std;



class Session : public std::enable_shared_from_this<Session> {

public:
    Session(tcp::socket socket, std::set<shared_ptr<Session>>& sessions) : socket_(std::move(socket)), sessions_(sessions) {}

    void start() {
        readHeader();
    }
private:

    void readHeader() {
        auto self(shared_from_this());
        async_read(socket_, buffer(header_, 4), [this, self](boost::system::error_code ec, size_t) {
            if (!ec) { 
                uint32_t length = *reinterpret_cast<uint32_t*>(header_);
                readBody(length);
            }
        });
    }


    void readBody(uint32_t length) {
        auto self(shared_from_this());
        std::vector<char> data(length);
        async_read(socket_, buffer(data), [this, self, data](boost::system::error_code ec, size_t) {
            if (!ec) {
                chat::ChatMessage message;
                message.ParseFromArray(data.data(), data.size());
                handleMessage(message);
                readHeader();
            }
        });
    }

    void handleMessage(const chat::ChatMessage& msg) {
        std::string serialized;
        msg.SerializeToString(&serialized);
        uint32_t length = serialized.size();
        std::vector<char> buffer(sizeof(length) + serialized.size());
        memcpy(buffer.data(), &length, sizeof(length));
        memcpy(buffer.data() + sizeof(length), serialized.data(), serialized.size());

        for (auto& session : sessions_) {
            if (session.get() != this) {
                write(session->socket_,boost::asio::buffer(buffer));
            }
        }
    }
    tcp::socket socket_;
    std::set<std::shared_ptr<Session>>& sessions_;
    char header_[4];
};


class Server {
    public:
    Server(io_context& io, short port) : acceptor_(io, tcp::endpoint(tcp::v4(), port)) {
        accpet();
    } 
private:

    void accpet() {
        acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                auto session = std::make_shared<Session>(std::move(socket), sessions_);
                sessions_.insert(session);
                session->start();
            }
            accpet();
        });
    }
    tcp::acceptor acceptor_;
    std::set<std::shared_ptr<Session>> sessions_;
};

int main() {
    io_context io;
    Server server(io, 12345);
    io.run();
    return 0;
}