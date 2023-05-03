#ifndef CONTEXTMANAGER_HPP
#define CONTEXTMANAGER_HPP


#include "../Parsing/Parser.hpp"
#include "../Analize/Analizer.hpp"
#include <memory>
#include <unordered_map>
#include <string>

using CurParser= Parsing::Parser<Analize::Analizer>;

struct ConnectionManager
{
    ConnectionManager(const std::size_t stblockSize_):
        stblockSize{stblockSize_},
        commonParser{std::make_shared<CurParser>(stblockSize)}
    {

    }

    void execute(std::string ip, std::string work)
    {
        if(!executeBusy(ip, work))
        {
            commonParser->parse(work);
            if(commonParser->isBusy())
            {
                busyParsers[ip]=std::move(commonParser);
                commonParser=std::make_shared<CurParser>(stblockSize);
            }
        }
    }

    private:
        const std::size_t stblockSize{3};

        std::shared_ptr<CurParser> commonParser;
        std::unordered_map<std::string, std::shared_ptr<CurParser> > busyParsers;

        bool executeBusy(std::string ip, std::string work)
        {
            try
            {
                auto& parser=busyParsers.at(ip);
                parser->parse(work);
                if(parser->isBusy())
                {
                    return true;
                }
                else
                {
                    busyParsers.erase(ip);
                    return true;
                }
            }
            catch(...)
            {
                return false;
            }

        }



};



#endif // CONTEXTMANAGER_HPP
