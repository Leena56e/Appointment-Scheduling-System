#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // Add this to use std::remove

using namespace std;

// Class to represent an Appointment
class Appointment {
public:
    string providerName;
    string clientName;
    string date;  // Full date in the format YYYY-MM-DD
    string time;
    string status; // "Booked", "Cancelled", "Pending"
    string month;  // The month of the appointment
    int week;      // The week of the month (1-4)
    string day;    // Day of the appointment (e.g., "Monday")

    Appointment(string provider, string client, string date, string time, string month, int week, string day)
    {
        providerName = provider;
        clientName = client;
        this->date = date;
        this->time = time;
        this->month = month;
        this->week = week;
        this->day = day;
        status = "Booked";
    }

    // Display appointment details
    void display() {
        cout << "Provider: " << providerName << "\n"
             << "Client: " << clientName << "\n"
             << "Date: " << date << " (" << month << ", Week " << week << ", " << day << ")\n"
             << "Time: " << time << "\n"
             << "Status: " << status << endl;
    }

    // Save appointment to file
    void saveToFile()
    {

        ofstream outFile("appointments.txt", ios::app); // Open in append mode
        if (outFile.is_open()) {
            outFile << providerName << "," << clientName << "," << date << "," << time << "," << status << ","
                    << month << "," << week << "," << day << endl;
            outFile.close();
        }
        else {
            cout << "Failed to open file!" << endl;
        }
    }
};

// Class to represent a Service Provider
class Provider {
public:
    string name;
    vector<string> availableSlots; // List of time slots

    Provider(string name) {
        this->name = name;
    }

    // Add available time slots
    void addAvailableSlot(string time) {
        availableSlots.push_back(time);
    }

    // Display available slots
    void displayAvailableSlots() {
        cout << "Available slots for " << name << ":\n";
        for (string slot : availableSlots) {
            cout << slot << endl;
        }
    }
};

// Function to simulate booking an appointment
void bookAppointment(Provider &provider, string clientName, string date, string time, string month, int week, string day) {
    Appointment newAppointment(provider.name, clientName, date, time, month, week, day);

    // Remove the selected time from the available slots
    provider.availableSlots.erase(remove(provider.availableSlots.begin(), provider.availableSlots.end(), time), provider.availableSlots.end());

    cout << "Appointment booked successfully for " << clientName << " on " << date << " (" << month << ", Week " << week << ", " << day << ") at " << time << endl;

    // Save the appointment to file
    newAppointment.saveToFile();
}

int main() {
    // Create a provider and add available slots
    Provider doc("Dr. Smith");
    doc.addAvailableSlot("10:00 AM");
    doc.addAvailableSlot("11:00 AM");

    // Display available slots
    doc.displayAvailableSlots();

    // Book an appointment
    bookAppointment(doc, "John Doe", "2025-03-21", "10:00 AM", "March", 3, "Friday");

    return 0;
}

