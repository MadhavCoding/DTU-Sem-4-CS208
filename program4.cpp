#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib> 
using namespace std;
using namespace std::chrono;

class StopAndWaitARQ {
private:
    int frameNumber;
    double timeout; 

public:
    StopAndWaitARQ(int frames, double timeoutPeriod) 
    {
        frameNumber = frames;
        timeout = timeoutPeriod;
    }

    void sendFrame() {
        int frame = frameNumber;
        frameNumber = 1;
        while (frameNumber <= frame) 
        {  
            cout << "Sending Frame " << frameNumber << "..."<<endl;
            
            if (rand() % 10 < 3) {
                cout << "Frame : " << frameNumber << " lost! Resending after timeout"<<endl;
                this_thread::sleep_for(duration<double>(timeout)); 
                continue;  
            }

            cout << "Frame : " << frameNumber << " sent successfully"<<endl;

            // Start timer for ACK reception
            auto start = high_resolution_clock::now();

            if (rand() % 10 < 3) {
                this_thread::sleep_for(duration<double>(timeout + 0.001)); 
                cout << "Acknowledgement for Frame : " << frameNumber << " lost! Resending frame after timeout..."<<endl;
                continue;
            }

            this_thread::sleep_for(duration<double>(timeout - 0.0005)); 

            cout << "Acknowledgement received for Frame " << frameNumber << " \nMoving to next frame." << endl << endl;

            frameNumber++; 
        }
    }
};

int main() {
    int frameNumber;
    double timeout;
    cout<<"Enter number of frames : ";
    cin>>frameNumber;
    cout<<"Enter timeout : ";
    cin>>timeout;
    StopAndWaitARQ protocol(frameNumber, timeout);
    protocol.sendFrame();
    return 0;
}
