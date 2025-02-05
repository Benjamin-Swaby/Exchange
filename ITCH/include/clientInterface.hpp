#include "itch.hpp"
#include <thread>

namespace ITCH41 {

    class ITCH_Client {
    private:
        int sessionSocket;

    protected:
        char* address;
        int port;
        virtual void log(const unsigned char* msg) = 0;

    public:
    
        void start_session(char* address, int port);
        void send_msg(const unsigned char* msg, int len);
        void stop_session();

        ~ITCH_Client() {
            //send_msg // send a logout message maybe
            stop_session();
        }

    };

}