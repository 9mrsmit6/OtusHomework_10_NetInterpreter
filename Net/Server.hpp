#ifndef SERVER_HPP
#define SERVER_HPP
#include "Connection.hpp"
#include "../Async/ContertManager/ContextManager.hpp"

namespace Net
{
    using ba=boost::asio::ip::tcp;

    struct Server
    {
        Server(boost::asio::io_context& io_context, short port):
            acceptor_(io_context, ba::endpoint(ba::v4(), port))
        {
            accept();
        }

        private:
            ba::acceptor acceptor_;
            const boost::asio::socket_base::keep_alive kaOpt{true};
            ConnectionManager man{3};

            void accept()
            {
                acceptor_.async_accept(
                        [this](boost::system::error_code ec, ba::socket socket)
                        {
                          if (!ec)
                          {
                            std::make_shared<Connection<ConnectionManager>>(socket, man)->read();
                          }

                          accept();
                        });
            }


    };

}
#endif // SERVER_HPP
