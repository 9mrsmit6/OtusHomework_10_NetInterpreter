#include "async.h"
#include "ContertManager/ContextManager.hpp"

#include <string>
#include <iostream>



namespace Async
{
//    using CurParser= Parsing::Parser<Analize::Analizer>;

    std::size_t connect(std::size_t bs)
    {
//       return ContextManger<CurParser>::getInstance().createNewContext(bs);
        return 0;
    }
    bool disconnect(std::size_t context)
    {
//        ContextManger<CurParser>::getInstance().eraseContext(context);
        return true;
    }
    bool receive(std::size_t context, const std::string& work)
    {
//        try //Малоли контекста такого нет
//        {
//            CurParser& obj= ContextManger<CurParser>::getInstance().getContext(context);
//            obj.parse(work);
//            return true;
//        }
//        catch(...)
//        {
//            return false;
//        }

        return true;


    }

}
