#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

string companyName = "AutoTech Industries";

class Vehicle {
protected:
    string brand, model;
public:
    static int count;

    Vehicle(string b, string m) {
        brand = b;
        model = m;
        count++;
    }

    virtual void displayInfo() {
        cout << "Brand: " << brand << ", Model: " << model << endl;
    }

    // NEW: file output version
    virtual void writeInfo(ofstream& out) {
        out << "Brand: " << brand << ", Model: " << model << "\n";
    }
};

int Vehicle::count = 0;

class Car : public Vehicle {
    int seats;
public:
    Car(string b, string m, int s) : Vehicle(b, m) {
        if (s < 0) throw invalid_argument("Seats cannot be negative");
        seats = s;
    }

    void displayInfo() override {
        cout << "Car | Brand: " << brand
             << ", Model: " << model
             << ", Seats: " << seats << endl;
    }

    void writeInfo(ofstream& out) override {
        out << "Car | Brand: " << brand
            << ", Model: " << model
            << ", Seats: " << seats << "\n";
    }
};

class Motorbike : public Vehicle {
    int engineCapacity;
public:
    Motorbike(string b, string m, int cc) : Vehicle(b, m) {
        if (cc < 0) throw invalid_argument("Engine capacity cannot be negative");
        engineCapacity = cc;
    }

    void displayInfo() override {
        cout << "Motorbike | Brand: " << brand
             << ", Model: " << model
             << ", Engine Capacity: " << engineCapacity << "cc" << endl;
    }

    void writeInfo(ofstream& out) override {
        out << "Motorbike | Brand: " << brand
            << ", Model: " << model
            << ", Engine Capacity: " << engineCapacity << "cc\n";
    }
};

int main() {
    cout << "Company: " << companyName << endl;

    Vehicle* vehicles[4];

    try {
        vehicles[0] = new Car("Toyota", "Corolla", 5);
        vehicles[1] = new Car("Toyota", "Probox", 4);
        vehicles[2] = new Motorbike("Yamaha", "R1", 1000);
        vehicles[3] = new Motorbike("Suzuki", "GSX", 750);
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\nVehicle Details:\n";
    for (int i = 0; i < 4; i++)
        vehicles[i]->displayInfo();

    cout << "\nTotal Vehicles Created: " << Vehicle::count << endl;

    // --- Write to file properly ---
    ofstream fileOut("vehicles.txt");
    if (fileOut.is_open()) {
        fileOut << "Company: " << companyName << "\n\n";
        for (int i = 0; i < 4; i++)
            vehicles[i]->writeInfo(fileOut);
        fileOut.close();
    }

    cout << "\nReading from file:\n";
    ifstream fileIn("vehicles.txt");
    if (fileIn.is_open()) {
        string line;
        while (getline(fileIn, line))
            cout << line << endl;
        fileIn.close();
    }

    return 0;
}
