#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <memory>
#include <utility>
#include <iostream>
#include <boost/asio.hpp>



namespace Net
{
    using ba=boost::asio::ip::tcp;

    template<class Handler>
    struct Connection: public std::enable_shared_from_this<Connection<Handler>>
    {
        Connection(ba::socket& socket_, Handler& handler_):
            socket(std::move(socket_)),
            handler{handler_}
        {

        }

        void read()
        {
            auto self(this->shared_from_this());

            boost::asio::async_read_until(socket, buf, "\n",
                    [this, self](boost::system::error_code ec, std::size_t length)
                    {
                        std::istream is{&buf};
                        handler.execute(socket.remote_endpoint().address().to_string(), is);

                        if (!ec)
                        {
                            read();
                        }
                    });
        }
        private:
            ba::socket socket;
            boost::asio::streambuf buf;
            Handler& handler;

    };
}

#endif // CONNECTION_HPP
