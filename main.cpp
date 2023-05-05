#include <iostream>
#include <boost/asio.hpp>
#include <string>

#include "Async/ContertManager/ContextManager.hpp"
#include "Net/Server.hpp"


//boost::asio::ip::tcp::socket* sockPtr;
//std::string str{"                              "};

//char vax[100];

//void read_handler(const boost::system::error_code& error, std::size_t readed)
//{
//    if (!error)
//    {
//        std::cout<<str<<std::endl;
//        auto buf=boost::asio::buffer(str);
//        boost::asio::async_read(*sockPtr, buf, read_handler);

//    }
//    else
//    {
//        std::cout<<"Closed"<<std::endl;
//    }

//}

//void accept_handler(const boost::system::error_code& error)
//    {
//        if (!error)
//        {
//            // Accept succeeded.

//            std::cout<<"ACC"<<std::endl;

//            auto buf=boost::asio::buffer(str);
//            boost::asio::async_read(*sockPtr, buf, read_handler);
//        }
//    }




int main()
{


//    Async::receive("1", "1\n2\n");
//    Async::receive("2", "{\n1\n2\n");

//    Async::receive("3", "4\n5\n6\n");
//    Async::receive("4", "4\n5\n6\n");
//    Async::receive("2", "}");

    boost::asio::io_context io_context;
    Net::Server server(io_context, 9000);
    io_context.run();

//    boost::asio::ip::tcp::acceptor ac{io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 9000)};
//    boost::asio::ip::tcp::socket socket{io_context};

//    sockPtr=&socket;

//    ac.async_accept(socket, accept_handler);

//    io_context.run();

//    while(true)
//    {

//    }


//    std::cout << "Hello World!" << std::endl;
    return 0;
}
