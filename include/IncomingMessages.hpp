#ifndef INCOMINGMESSAGES_H
#define INCOMINGMESSAGES_H

// Класс, описывающий входящие сообщения и их обработчиков. (Паттерн "одиночка")
class IncomingMessages
{
    public:
        enum Message : char
        {
            EMPTY,
            LETTER
        };

        virtual ~IncomingMessages();
        static IncomingMessages* Instance();

        IncomingMessages::Message ConvertToMessage(char* buffer, int sizeOfBuffer);

        int getMessagesCount();

    protected:
        IncomingMessages(); // защищенный конструктор

    private:
        static IncomingMessages* _instance;

        int _messagesCount;

};

#endif // MESSAGESANDHANDLERS_H
