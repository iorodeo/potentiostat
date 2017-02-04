#ifndef PS_COMMAND_TABLE_H 
#define PS_COMMAND_TABLE_H 
#include <Arduino.h> 
#include "ArduinoJson.h"
#include "Array.h"

namespace ps
{

    template<typename T>
    class NamedCommand
    {
        public:

            String name;
            void (T::*method)(JsonObject& ) = nullptr;
    };


    template<typename T, size_t MAX_SIZE>
    class CommandTable
    {
        
        public:

            CommandTable(T *client=nullptr);
            //void clear();
            //void size();
            //void maxSize();
            void setClient(T *client);
            void registerMethod(String name, void (T::*method)(JsonObject&));
            void registerMethod(String name); 

        protected:

            T *client_;
            Array<NamedCommand<T>,MAX_SIZE> table_;

    };


    template<typename T, size_t MAX_SIZE>
    CommandTable<T,MAX_SIZE>::CommandTable(T *client) : client_(client) {}


    template<typename T, size_t MAX_SIZE>
    void CommandTable<T,MAX_SIZE>::setClient(T* client)
    {
        client_ = client;
    }


    template<typename T, size_t MAX_SIZE>
    void CommandTable<T,MAX_SIZE>::registerMethod(String name, void (T::*method)(JsonObject&))
    {
        NamedCommand<T> namedCommand = {name,method};
        table_.push_back(namedCommand);
    }







} // namespace ps

#endif
