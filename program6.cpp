#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib> 
#include <vector>
#include <set>
using namespace std;
using namespace std::chrono;

class SelectiveRepeatARQ 
{
private:
    int frameNumber;   
    int window;    
    double timeout;   
    

public:
    SelectiveRepeatARQ(int frames, int winSize, double timeoutPeriod) 
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
            vector<int> lostFrame, lostACK;
            cout << endl << "Sending frames: ";
            for (int i = base; i < end; i++) 
            {
                cout << i << " ";

                int random = rand();

                // Frame lost
                if(random % 10 < 1)
                {
                    lostFrame.push_back(i);
                }

                // ACK lost
                else if(random % 10 < 3)
                {
                    lostACK.push_back(i);
                }
            }
            cout << endl;

            // Show lost frames
            for (int f : lostFrame) 
            {
                cout << "Frame " << f << " lost! It will be resent after timeout." << endl;
            }

            // Show lost ACKs
            for (int a : lostACK) 
            {
                cout << "ACK for Frame " << a << " lost! It will be resent after timeout." << endl;
            }

            // Simulating transmission delay
            this_thread::sleep_for(duration<double>(timeout));

           // Resending...
           if (!lostFrame.empty() || !lostACK.empty()) 
           {
                cout << "Timeout: Resending lost frames...\n";
                for (int f : lostFrame) 
                {
                    cout << "Resending Frame " << f << " due to Frame loss...\n";
                }
                for (int a : lostACK) 
                {
                    cout << "Resending Frame " << a << " due to ACK loss...\n";
                }
            }

            cout << "ACK received for frames " << base << " to " << end - 1 << ". Moving window forward." << endl;
            
            base = end;
        }
        cout<< endl;
        cout << "All frames transmitted successfully!" << endl;
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

    SelectiveRepeatARQ protocol(frameNumber, windowSize, timeout);
    protocol.sendFrames();
    return 0;
}
