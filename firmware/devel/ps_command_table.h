#ifndef PS_COMMAND_TABLE_H 
#define PS_COMMAND_TABLE_H 
#include <Arduino.h> 
#include "ArduinoJson.h"
#include "Array.h"
#include "ps_return_status.h"
#include "ps_keyvalue_command.h"

namespace ps
{

    template<typename T, size_t MAX_SIZE>
    class CommandTable
    {
        
        public:

            CommandTable(T *client=nullptr);

            void clear();
            void clearTable();

            size_t size();
            size_t maxSize();

            void setClient(T *client);
            void registerMethod(String key, String value, ReturnStatus (T::*method)(JsonObject&));

            ReturnStatus apply(String key, JsonObject &json);

        protected:

            T *client_;
            Array<KeyValueCommand<T>,MAX_SIZE> table_;

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
    void CommandTable<T,MAX_SIZE>::registerMethod(String key, String value, ReturnStatus (T::*method)(JsonObject&))
    {
        KeyValueCommand<T> kvCommand(key,value,method);
        table_.push_back(kvCommand);
    }



    template<typename T, size_t MAX_SIZE>
    ReturnStatus CommandTable<T,MAX_SIZE>::apply(String key, JsonObject &json)
    {
        ReturnStatus status;
        if (client_!= nullptr)
        {
            if ( json.containsKey(key.c_str()) )
            {
                String cmd = String((const char *)(json[key.c_str()])).trim();
                for (size_t i=0; i<table_.size(); i++)
                {
                    if (cmd.equals(table_[i].value()))
                    {
                        status = table_[i].applyMethod(client_,json);
                        status.command = cmd;
                        break;
                    }
                }
            }
            else
            {
                status.success = false;
                status.message = "CommandTable: command not found";
            }
        }
        else
        {
            status.success = false;
            status.message = "CommandTable: client is nullptr";
        }
        return status;
    }


} // namespace ps

#endif
