#ifndef CONTEXTMANAGER_HPP
#define CONTEXTMANAGER_HPP


#include "../Parsing/Parser.hpp"
#include "../Analize/Analizer.hpp"
#include <memory>
#include <unordered_map>
#include <string>

using CurParser= Parsing::Parser<Analize::Analizer>;

//Модифицтрованный обработчик комманд.
//Есть основной парсер и map с обработчиками динамических блоков. Где в качестве ключа строка ip адреса инициатора.
//Если основной парсер ловит динамический блок то он помещаетя в коллекцию а на его место создается новый.

struct Handler
{
    Handler(const std::size_t stblockSize_):
        stblockSize{stblockSize_},
        commonParser{std::make_shared<CurParser>(stblockSize)}
    {

    }

    void execute(const std::string& ip, std::istream& work)
    {
        if(!executeBusy(ip, work))  //Сначала динамические блоки
        {
            commonParser->parse(work);  //Потом статические
            if(commonParser->isBusy())  //Если попался динамический и парсер теперь занят
            {
                busyParsers[ip]=std::move(commonParser);
                commonParser=std::make_shared<CurParser>(stblockSize);
            }
        }
    }

//    ~ConnectionManager()
//    {
//        for(auto& a:busyParsers)
//        {
//            a.second->eof();
//        }
//        commonParser->eof();

//    }

    private:

        const std::size_t stblockSize{3};

        std::shared_ptr<CurParser> commonParser;
        std::unordered_map<std::string, std::shared_ptr<CurParser> > busyParsers;

        bool executeBusy(const std::string& ip, std::istream& work)
        {
            //Обработка динамических блоков
            try
            {
                //Ищем блок в коллекции и обрабатываем
                auto& parser=busyParsers.at(ip);
                parser->parse(work);
                if(parser->isBusy())
                {
                    return true;
                }
                else
                {
                    busyParsers.erase(ip); //Если он закончил то удаляем его
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
