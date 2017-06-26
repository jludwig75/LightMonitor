#include <Windows.h>
#include <thread>

extern void setup();
extern void loop();


int main(int argc, char *argv[])
{
    for (setup(); ; )
    {
        loop();
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }

    return 0;
}