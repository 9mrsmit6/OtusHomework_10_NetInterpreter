#ifndef SERVER_HPP
#define SERVER_HPP
#include "Connection.hpp"
#include "../Async/NetReqHandler/Handler.hpp"

namespace Net
{
    using ba=boost::asio::ip::tcp;

    struct Server
    {
        Server(boost::asio::io_context& io_context, unsigned short port, const std::size_t bs):
            acceptor_(io_context, ba::endpoint(ba::v4(), port)),
            handler{bs}
        {
            accept();
        }

        private:
            ba::acceptor acceptor_;
            const boost::asio::socket_base::keep_alive kaOpt{true};
            Handler handler;

            void accept()
            {
                acceptor_.async_accept(
                        [this](boost::system::error_code ec, ba::socket socket)
                        {
                          if (!ec)
                          {
                            std::make_shared<Connection<Handler>>(socket, handler)->read();
                          }

                          accept();
                        });
            }


    };

}
#endif // SERVER_HPP
