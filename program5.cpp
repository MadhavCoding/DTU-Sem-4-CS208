#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib> 
using namespace std;
using namespace std::chrono;

class GoBackNARQ 
{
private:
    int frameNumber;   
    int window;    
    double timeout;    

public:
    GoBackNARQ(int frames, int winSize, double timeoutPeriod) 
    {
        frameNumber = frames;
        window = winSize;
        timeout = timeoutPeriod;
    }

    void sendFrames() 
    {
        int base = 0;  

        while (base < frameNumber) 
        {
            int end = min(base + window, frameNumber);  
            cout << endl << "Sending frames: ";
            for (int i = base; i < end; i++) 
            {
                cout << i << " ";
            }
            cout << endl;

            int lostFrame = -1, lostAck = -1;
            
            // Frame Lost
            if (rand() % 10 < 1) 
            {
                lostFrame = base + rand() % (end - base); 
                cout << "Frame " << lostFrame << " lost! Resending all frames from " << lostFrame << " onward after timeout...\n";
            }

            // ACK Lost
            if (rand() % 10 < 2 && lostFrame == -1) 
            { 
                lostAck = base + rand() % (end - base);
                cout << "ACK for Frame " << lostAck << " lost! Resending Frame " << lostAck << " after timeout...\n";
            }

            // Transmission delay
            this_thread::sleep_for(duration<double>(timeout));

            if (lostFrame != -1) 
            {
                base = lostFrame;  
                continue;  
            }

            if (lostAck != -1) 
            {
                base = lostAck;  
                continue;  
            }

            cout << "ACK received for frames " << base << " to " << end - 1 << ". Moving window forward.\n";
            base = end;
        }
        cout << "All frames transmitted successfully!\n";
    }
};

int main() 
{
    int frameNumber;
    int windowSize;
    double timeout;
    cout<<"Enter number of frames : ";
    cin>>frameNumber;
    cout<<"Enter window size : ";
    cin>>windowSize;
    cout<<"Enter timeout : ";
    cin>>timeout;

    GoBackNARQ protocol(frameNumber, windowSize, timeout);
    protocol.sendFrames();
    return 0;
}
