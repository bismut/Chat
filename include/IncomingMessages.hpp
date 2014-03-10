#ifndef INCOMINGMESSAGES_H
#define INCOMINGMESSAGES_H

// �����, ����������� �������� ��������� � �� ������������. (������� "��������")
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
        IncomingMessages(); // ���������� �����������

    private:
        static IncomingMessages* _instance;

        int _messagesCount;

};

#endif // MESSAGESANDHANDLERS_H
