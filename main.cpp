#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>

using namespace std; 

const double pi = 3.14159;
const double sampleSpeed = 441;

class WaveGenerator {
private:
    int selectBit;    // to select which wave
    double Vmax;      // peak to 0 amplitude (y-axis)
    double freq;      // waveslengths per second
    double offset;    // voltage value offset (y-axis shift)
    double dutyRatio; // ratio between high and low states
    double duration;  // timespan of the wave (x-axis)
    double phase;     // phase shift of wave (x-axis shift)
    string Name;      // name of wave

public:
    // Constructor
    WaveGenerator() : Vmax(0.00), freq(0.00), offset(0.00),
 dutyRatio(0.00), duration(0.00), phase(0.00) {}

    // Main function to take parameters and generate sine wave
    void run() {
        waveSelect();
        parameters();
        wave();
        uploadToGitHub();
    }

private:
  void waveSelect() {
      while(true) {
      cout << "------------------------------" << endl;
      cout << "Pick a waveform" << endl;
      cout << "1) Sine wave" << endl;
      cout << "2) Square wave" << endl;
      cout << "3) Triangle wave" << endl;
      cout << "4) Sawtooth wave" << endl;
      cout << "------------------------------" << endl;
      cout << "0) End Program\n" << endl;
      cin >> selectBit;
    if (selectBit == 1) {
      Name = "Sine";  
    } else if (selectBit == 2) {
      Name = "Square";
    } else if (selectBit == 3) {
      Name = "Triangle";      
    } else if (selectBit == 4) {
      Name = "Sawtooth";
    } else if (selectBit == 0) {
      cout << "Program ended";
      exit(0);
    } else {
      cout << "\n No wave selected" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
      if (selectBit >0 && selectBit <5) { 
        cout << "\n\n" << endl;
        cout << Name << " Wave Generator" << endl;
        cout << "------------------------------" << endl;
        break;
      }
    }
  }
  void parameters() {
        while (true) {
            cout << "Duration (s): ";
            cin >> duration;

            cout << "Amplitude (V): ";
            cin >> Vmax;

            cout << "Offset (V): ";
            cin >> offset;

            cout << "Phase shift (°): ";
            cin >> phase;

            if(selectBit > 1) {
              cout << "Duty cycle (%): ";
              cin >> dutyRatio;
            }

            cout << "Frequency (Hz): ";
            cin >> freq;
            if (freq <= 0) {
              cout << "Frequency must be a positive number.\n" << endl;
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }
        cout << "------------------------------" << endl;
        cout << "Parameters set successfully!" << endl;
        cout << "Duration: " << duration << " s" << endl;
        cout << "Amplitude: " << Vmax << " V" << endl;
        cout << "Offset: " << offset << " V" << endl;
        if(selectBit > 1) {
          cout << "Duty cycle: " << dutyRatio << " %: " << endl;      
        }
        cout << "Phase shift: " << phase << " °" << endl;
        cout << "Frequency: " << freq << " Hz" << endl;
        cout << "------------------------------" << endl;
    }
  void wave() {
    if (selectBit == 1) {
      ofstream file("sine_wave.csv");
      if (file.is_open()) {
        
        double step = 1.0 / sampleSpeed;
        for (double t = 0.0; t <= duration; t += step) {
          double magnitude = (Vmax * sin((2 * pi * freq * t) + ((phase * pi)/180))) + offset;
          file << t << "," << magnitude << endl;
          }
        file.close();
        cout << "\nWave successfully generated.";
        } 
      else { cout << "File cannot be opened." << endl; }
    } 
      else if (selectBit == 2) {
        ofstream file("square_wave.csv");
        if (file.is_open()) {
         
          double step = 1.0 / sampleSpeed;
            for (double t = 0.0; t <= duration; t += step) {
            double value = (Vmax * sin((2 * pi * freq * t) + ((phase * pi)/180))) + offset;
            double magnitude = (value >= offset + Vmax - (Vmax * dutyRatio)/50) ? Vmax + offset : -Vmax + offset;
            file << t << "," << magnitude << endl;
            }
          double value = (Vmax * sin((2 * pi * freq * duration) + ((phase * pi)/180))) + offset;
          double magnitude = (value >= offset + Vmax - (Vmax * dutyRatio)/50) ? Vmax + offset : -Vmax + offset;
          file << duration << "," << magnitude << endl;
          file.close();
          cout << "\nWave successfully generated.";
          } else { cout << "File cannot be opened." << endl; }
      }
    }
  void uploadToGitHub() {
    
    }
};

int main() {

  WaveGenerator generator;

  generator.run();

  return 0;
}
