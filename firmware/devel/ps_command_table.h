#ifndef PS_COMMAND_TABLE_H 
#define PS_COMMAND_TABLE_H 
#include <Arduino.h> 
#include "ArduinoJson.h"
#include "Array.h"
#include "ps_return_status.h"

namespace ps
{

    template<typename T>
    class NamedCommand
    {
        public:
            NamedCommand() {};
            NamedCommand(String newName, void (T::*newMethod)(JsonObject&));
            String name;
            void (T::*method)(JsonObject&) = nullptr;
    };

    template<typename T>
    NamedCommand<T>::NamedCommand(String newName, void (T::*newMethod)(JsonObject&))
        : name(newName), method(newMethod)
    {}


    template<typename T, size_t MAX_SIZE>
    class CommandTable
    {
        
        public:

            CommandTable(T *client=nullptr);
            void clearTable();
            void clear();
            size_t size();
            size_t maxSize();
            void setClient(T *client);
            void registerMethod(String name, void (T::*method)(JsonObject&));
            void registerMethod(String name); 

            ReturnStatus run(JsonObject &jsonRoot);

        protected:

            T *client_;
            Array<NamedCommand<T>,MAX_SIZE> table_;

    };


    template<typename T, size_t MAX_SIZE>
    CommandTable<T,MAX_SIZE>::CommandTable(T *client) : client_(client) {}


    template<typename T, size_t MAX_SIZE>
    void CommandTable<T,MAX_SIZE>::clearTable()
    {
        table_.clear();
    }


    template<typename T, size_t MAX_SIZE>
    void CommandTable<T,MAX_SIZE>::clear()
    {
        clearTable();
        client_ = nullptr;
    }


    template<typename T, size_t MAX_SIZE>
    size_t CommandTable<T,MAX_SIZE>::size()
    {
        return table_.size();
    }


    template<typename T, size_t MAX_SIZE>
    size_t CommandTable<T,MAX_SIZE>::maxSize()
    {
        return MAX_SIZE;
    }


    template<typename T, size_t MAX_SIZE>
    void CommandTable<T,MAX_SIZE>::setClient(T* client)
    {
        client_ = client;
    }


    template<typename T, size_t MAX_SIZE>
    void CommandTable<T,MAX_SIZE>::registerMethod(String name, void (T::*method)(JsonObject&))
    {
        NamedCommand<T> namedCommand(name,method);
        table_.push_back(namedCommand);
    }



    template<typename T, size_t MAX_SIZE>
    ReturnStatus CommandTable<T,MAX_SIZE>::run(JsonObject &jsonRoot)
    {
        ReturnStatus status;
        if (client_!= nullptr)
        {
            if (jsonRoot.containsKey("cmd"))
            {
                String cmd = String((const char *)(jsonRoot["cmd"]));

                // DEBUG
                //////////////////////////////////////////////////////
                Serial.print("cmd = ");
                Serial.println(cmd);
                //////////////////////////////////////////////////////

                for (size_t i=0; i<table_.size(); i++)
                {
                    if (cmd.equals(table_[i].name))
                    {
                        Serial.println("found cmd");
                    }

                }
            }
            else
            {
                Serial.println("command not found");
            }
        }
        else
        {
            status.success = false;
            status.message = String("CommandTable client in nullptr");
        }
        return status;
    }




} // namespace ps

#endif
