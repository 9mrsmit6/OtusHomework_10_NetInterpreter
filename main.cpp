#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include "Options/Options.hpp"

#include "Net/Server.hpp"


int main(int argc, const char *argv[])
{

    auto rawOptions=Options::getRawOptions(argc,argv);

    if(!rawOptions)
    {
        std::cout<<"Options Parse Error";
        return -1;
    }


    boost::asio::io_context io_context;
    Net::Server server(io_context, rawOptions->port, rawOptions->sBlockSize);
    io_context.run();

    return 0;
}
