#ifndef PS_COMMAND_TABLE_H 
#define PS_COMMAND_TABLE_H 
#include <Arduino.h> 
#include "ArduinoJson.h"
#include "Array.h"
#include "ps_return_status.h"

namespace ps
{

    // KeyValueCommand
    // --------------------------------------------------------------------------------------------

    template<typename T>
    class KeyValueCommand
    {
        public:
            KeyValueCommand() {};
            KeyValueCommand(String key, String value, ReturnStatus (T::*method)(JsonObject&));

            String key();
            void setKey(String key);

            String value();
            void setValue(String value);

            void setMethod(ReturnStatus (T::*method)(JsonObject&));
            ReturnStatus applyMethod(T* client, JsonObject &json);

        protected:
            String key_;
            String value_;
            ReturnStatus (T::*method_)(JsonObject&) = nullptr;
    };


    template<typename T>
    KeyValueCommand<T>::KeyValueCommand(String key, String value, ReturnStatus (T::*method)(JsonObject&))
        : key_(key), value_(value), method_(method) 
    {}


    template<typename T>
    String KeyValueCommand<T>::key()
    {
        return key_;
    }


    template<typename T>
    void KeyValueCommand<T>::setKey(String key)
    {
        key_ = key;
    }


    template<typename T>
    String KeyValueCommand<T>::value()
    {
        return value_;
    }


    template<typename T>
    void KeyValueCommand<T>::setValue(String value)
    {
        value_ = value;
    }


    template<typename T>
    void KeyValueCommand<T>::setMethod(ReturnStatus (T::*method)(JsonObject&))
    {
        method_ = method;
    }


    template<typename T>
    ReturnStatus KeyValueCommand<T>::applyMethod(T *client, JsonObject &json)
    {
        ReturnStatus status;
        if (method_ != nullptr)
        {
            status = ((*client).*(method_))(json);
        }
        else
        {
            status.success = false;
            status.message = "KeyValueCommand: method is nullptr";
        }
        return status;
    }


    // CommandTable
    // --------------------------------------------------------------------------------------------

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
