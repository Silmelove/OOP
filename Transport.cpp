#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ---------------- Base Class ----------------
class Vehicle {
protected:
    string route;
    int capacity;
    int booked;
    bool status; 
public:
    Vehicle(string r, int c) : route(r), capacity(c), booked(0), status(true) {}
    virtual ~Vehicle() {}

    virtual double calculateTravelTime(double distance) {
      
        double speed = 50.0;
        return distance / speed;
    }

    bool bookPassenger(const string& passengerName) {
        if (booked < capacity) {
            booked++;
            cout << "Passenger " << passengerName << " booked successfully on route " << route << "\n";
            return true;
        }
        else {
            cout << "Booking failed! Vehicle is full." << endl;
            return false;
        }
    }

    virtual void displayInfo() {
        cout << "Vehicle Route: " << route
            << " | Capacity: " << capacity
            << " | Booked: " << booked
            << " | Status: " << (status ? "On-time" : "Delayed") << endl;
    }
};

// ---------------- Derived Class ----------------
class ExpressBus : public Vehicle {
private:
    double speed; 
public:
    ExpressBus(string r, int c, double s) : Vehicle(r, c), speed(s) {}

    double calculateTravelTime(double distance) override {
        return distance / speed; 
    }

    void displayInfo() override {
        cout << "Express Bus Route: " << route
            << " | Capacity: " << capacity
            << " | Booked: " << booked
            << " | Speed: " << speed << " km/h" << endl;
    }
};


class Passenger {
private:
    string name;
    int ticketID;
public:
    Passenger(string n, int id) : name(n), ticketID(id) {}
    void displayInfo() {
        cout << "Passenger: " << name << " | Ticket ID: " << ticketID << endl;
    }
};


class Schedule {
private:
    string departureTime;
    string arrivalTime;
    Vehicle* assignedVehicle; 
public:
    Schedule(string dep, string arr, Vehicle* v) : departureTime(dep), arrivalTime(arr), assignedVehicle(v) {}

    void displayInfo() {
        cout << "Schedule: " << departureTime << " -> " << arrivalTime << endl;
        assignedVehicle->displayInfo();
    }
};


class Station {
private:
    string name;
    string location;
    int maxSchedules;
    vector<Schedule> schedules;
public:
    Station(string n, string loc, int maxS = 10) : name(n), location(loc), maxSchedules(maxS) {}

    bool addSchedule(const Schedule& s) {
        if ((int)schedules.size() < maxSchedules) {
            schedules.push_back(s);
            cout << "Schedule added to station " << name << "\n";
            return true;
        }
        else {
            cout << "Cannot add schedule, max limit reached!" << endl;
            return false;
        }
    }

    void displaySchedules() {
        cout << "--- Station: " << name << " at " << location << " ---" << endl;
        for (size_t i = 0; i < schedules.size(); i++) {
            schedules[i].displayInfo();
        }
    }
};

int main() {
    cout << "==============================\n";
    cout << " Public Transportation System \n";
    cout << "==============================\n\n";

    //Create Vehicles
    Vehicle v1("City-A to City-B", 3);
    ExpressBus eb1("City-C to City-D", 2, 80.0);

    cout << ">>> VEHICLE INFORMATION <<<\n";
    v1.displayInfo();
    eb1.displayInfo();
    cout << "------------------------------\n\n";

    //Create Passengers
    Passenger p1("Alice", 101);
    Passenger p2("Bob", 102);
    Passenger p3("Charlie", 103);
    Passenger p4("David", 104);

    cout << ">>> PASSENGER INFORMATION <<<\n";
    p1.displayInfo();
    p2.displayInfo();
    p3.displayInfo();
    p4.displayInfo();
    cout << "------------------------------\n\n";

    // Booking Passengers
    cout << ">>> BOOKING TEST <<<\n";
    if (v1.bookPassenger("Alice")) cout << "Alice booked on Vehicle\n";
    if (v1.bookPassenger("Bob")) cout << " Bob booked on Vehicle\n";
    if (v1.bookPassenger("Charlie")) cout << " Charlie booked on Vehicle\n";
    if (!v1.bookPassenger("David")) cout << " David booking failed (Vehicle full)\n";

    if (eb1.bookPassenger("Alice")) cout << " Alice booked on ExpressBus\n";
    if (eb1.bookPassenger("Bob")) cout << " Bob booked on ExpressBus\n";
    if (!eb1.bookPassenger("Charlie")) cout << " Charlie booking failed (ExpressBus full)\n";
    cout << "------------------------------\n\n";

    // Travel time test
    cout << ">>> TRAVEL TIME TEST <<<\n";
    cout << "Normal Vehicle (100 km): " << v1.calculateTravelTime(100) << " hours\n";
    cout << "Express Bus (100 km): " << eb1.calculateTravelTime(100) << " hours\n";
    cout << "------------------------------\n\n";

    // Create Schedules
    Schedule s1("08:00", "10:00", &v1);
    Schedule s2("09:00", "11:00", &eb1);

    // Create Station and add schedules
    Station st("Central Station", "Downtown");
    cout << ">>> ADDING SCHEDULES TO STATION <<<\n";
    st.addSchedule(s1);
    st.addSchedule(s2);

    // Try to add more schedules than limit
    for (int i = 0; i < 11; i++) {
        Schedule temp("12:00", "14:00", &v1);
        if (!st.addSchedule(temp)) {
            cout << "✘ Schedule " << i + 3 << " not added (limit reached)\n";
            break;
        }
    }
    cout << "------------------------------\n\n";

    cout << ">>> STATION SCHEDULES <<<\n";
    st.displaySchedules();
    cout << "==============================\n";
    cout << "          END OF TEST          \n";
    cout << "==============================\n";

    return 0;
}
