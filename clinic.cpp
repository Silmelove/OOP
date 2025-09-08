#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;

/* --- Liet ke trang thai lich hen --- */
enum class ApptStatus { SCHEDULED, COMPLETED, CANCELED };

/* --- Appointment class --- */
class Appointment {
private:
    int id;
    string date;
    string time;
    string reason;
    string doctorId;
    ApptStatus status;

public:
    Appointment(int _id, const string& _date, const string& _time,
        const string& _reason, const string& _doctorId)
        : id(_id), date(_date), time(_time), reason(_reason), doctorId(_doctorId), status(ApptStatus::SCHEDULED) {}

    int getId() const { return id; }
    string getDoctorId() const { return doctorId; }
    ApptStatus getStatus() const { return status; }

    void cancel() {
        if (status == ApptStatus::CANCELED) {
            cout << "[Appointment] " << id << " da bi huy roi.\n";
            return;
        }
        status = ApptStatus::CANCELED;
    }
    void setStatus(ApptStatus s) { status = s; }

    void display() const {
        cout << "  [Lich#" << id << "] " << date << " " << time << " | " << reason
            << " | Bac si: " << doctorId << " | Trang thai: ";
        switch (status) {
        case ApptStatus::SCHEDULED: cout << "Da dat"; break;
        case ApptStatus::COMPLETED: cout << "Hoan tat"; break;
        case ApptStatus::CANCELED: cout << "Da huy"; break;
        }
        cout << '\n';
    }
};

/* --- Person (cac thuoc tinh chung) --- */
class Person {
protected:
    string name;
    string id;
    int age;
public:
    Person(const string& _name, const string& _id, int _age) : name(_name), id(_id), age(_age) {}
    virtual ~Person() {}
    string getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
};

/* --- Patient class --- */
class Patient : public Person {
private:
    vector<string> history; // luu lich su kham
public:
    Patient(const string& _name, const string& _id, int _age) : Person(_name, _id, _age) {}
    virtual ~Patient() {
        cout << "[Patient] Huy object benh nhan " << id << " - " << name << '\n';
    }

    void addHistoryEntry(const string& entry) { history.push_back(entry); }

    virtual bool scheduleAppointment(vector<Appointment>& appointments,
        const string& date, const string& time,
        const string& reason, const string& doctorId) {
        int newId = static_cast<int>(appointments.size()) + 1;
        appointments.emplace_back(newId, date, time, reason, doctorId);
        addHistoryEntry("Dat lich: " + date + " " + time + " - " + reason);
        cout << "[Patient] " << name << " (ID:" << id << ") da dat lich #" << newId << ".\n";
        return true;
    }

    virtual void display() const {
        cout << "Benh nhan: " << name << " (ID:" << id << "), Tuoi: " << age << '\n';
        cout << "  Lich su y te:\n";
        if (history.empty()) cout << "    - (chua co muc)\n";
        for (const auto& e : history) cout << "    - " << e << '\n';
    }
};

/* --- ChronicPatient: ke thua Patient --- */
class ChronicPatient : public Patient {
private:
    string disease;
    string diagnosisDate;
public:
    ChronicPatient(const string& _name, const string& _id, int _age,
        const string& _disease, const string& _diagnosisDate)
        : Patient(_name, _id, _age), disease(_disease), diagnosisDate(_diagnosisDate) {}

    bool scheduleAppointment(vector<Appointment>& appointments,
        const string& date, const string& time,
        const string& reason, const string& doctorId) override {
        addHistoryEntry("Chronic: " + disease + " (Diag: " + diagnosisDate + ")");
        cout << "[ChronicPatient] Kiem tra tan suat cho benh nhan man tinh " << getId() << '\n';
        return Patient::scheduleAppointment(appointments, date, time, reason + " [Chronic]", doctorId);
    }

    void display() const override {
        Patient::display();
        cout << "  Benh man tinh: " << disease << " (Chan doan: " << diagnosisDate << ")\n";
    }
};

/* --- Doctor class --- */
class Doctor : public Person {
private:
    string specialty;
public:
    vector<int> assignedAppointmentIds;
    Doctor(const string& _name, const string& _id, const string& _specialty)
        : Person(_name, _id, 0), specialty(_specialty) {}
    string getSpecialty() const { return specialty; }

    void viewAppointments(const vector<Appointment>& appointments) const {
        cout << "Bac si: " << name << " (ID:" << id << ") - Chuyen khoa: " << specialty << '\n';
        bool any = false;
        for (int apptId : assignedAppointmentIds) {
            for (const auto& a : appointments) {
                if (a.getId() == apptId) { a.display(); any = true; }
            }
        }
        if (!any) cout << "  (Chua co lich gan cho bac si nay)\n";
    }

    void updateAppointmentStatus(vector<Appointment>& appointments, int apptId, ApptStatus status) {
        for (auto& a : appointments) {
            if (a.getId() == apptId) {
                a.setStatus(status);
                cout << "[Doctor] Bac si " << name << " cap nhat lich #" << apptId << " => ";
                if (status == ApptStatus::COMPLETED) cout << "Hoan tat\n";
                else if (status == ApptStatus::CANCELED) cout << "Da huy\n";
                else cout << "Da dat\n";
                return;
            }
        }
        cout << "[Doctor] Khong tim thay lich #" << apptId << '\n';
    }

    void display() const {
        cout << "Bac si: " << name << " (ID:" << id << "), Chuyen khoa: " << specialty << '\n';
    }
};

/* --- Clinic --- */
class Clinic {
public:
    vector<Patient*> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

    ~Clinic() {
        for (auto p : patients) delete p;
        patients.clear();
    }

    Patient* findPatientById(const string& pid) {
        for (auto p : patients) if (p->getId() == pid) return p;
        return nullptr;
    }
    Doctor* findDoctorById(const string& did) {
        for (auto& d : doctors) if (d.getId() == did) return &d;
        return nullptr;
    }

    void addPatient(Patient* p) {
        if (findPatientById(p->getId())) {
            cout << "[Clinic] Benh nhan da ton tai: " << p->getId() << '\n';
            return;
        }
        patients.push_back(p);
        cout << "[Clinic] Them benh nhan: " << p->getName() << " (ID:" << p->getId() << ")\n";
    }
    void addDoctor(const Doctor& d) {
        if (findDoctorById(d.getId())) {
            cout << "[Clinic] Bac si da ton tai: " << d.getId() << '\n';
            return;
        }
        doctors.push_back(d);
        cout << "[Clinic] Them bac si: " << d.getName() << " (ID:" << d.getId() << ")\n";
    }

    void scheduleAppointmentForPatient(const string& patientId, const string& doctorId,
        const string& date, const string& time, const string& reason) {
        Patient* p = findPatientById(patientId);
        Doctor* d = findDoctorById(doctorId);
        if (!p) { cout << "[Clinic] Khong tim thay benh nhan " << patientId << '\n'; return; }
        if (!d) { cout << "[Clinic] Khong tim thay bac si " << doctorId << '\n'; return; }

        bool ok = p->scheduleAppointment(appointments, date, time, reason, doctorId);
        if (ok && !appointments.empty()) {
            int apptId = appointments.back().getId();
            d->assignedAppointmentIds.push_back(apptId);
            cout << "[Clinic] Gan lich #" << apptId << " cho bac si " << d->getName() << '\n';
        }
    }

    void cancelAppointment(int apptId) {
        for (auto& a : appointments) {
            if (a.getId() == apptId) {
                a.cancel();
                cout << "[Clinic] Da huy lich #" << apptId << '\n';
                return;
            }
        }
        cout << "[Clinic] Khong tim thay lich #" << apptId << '\n';
    }

    void showAllAppointments() const {
        cout << "\n=== TAT CA LICH HEN ===\n";
        if (appointments.empty()) { cout << " (khong co lich)\n"; return; }
        for (const auto& a : appointments) a.display();
    }

    void showAllPatients() const {
        cout << "\n=== DANH SACH BENH NHAN ===\n";
        if (patients.empty()) { cout << " (khong co benh nhan)\n"; return; }
        for (const auto& p : patients) p->display();
    }

    void showAllDoctors() const {
        cout << "\n=== DANH SACH BAC SI ===\n";
        if (doctors.empty()) { cout << " (khong co bac si)\n"; return; }
        for (const auto& d : doctors) d.display();
    }
};

/* --- Main --- */
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Clinic clinic;

    // Them bac si
    clinic.addDoctor(Doctor("Nguyen Van A", "D001", "Noi tong quat"));
    clinic.addDoctor(Doctor("Tran Thi B", "D002", "Endocrinology"));

    // Them benh nhan
    clinic.addPatient(new Patient("Le Thi C", "P001", 30));
    clinic.addPatient(new ChronicPatient("Pham Van D", "P002", 55, "Tieu duong", "2025-06-15"));

    // Them lich su
    Patient* p1 = clinic.findPatientById("P001");
    Patient* p2 = clinic.findPatientById("P002");
    if (p1) p1->addHistoryEntry("2024-12-10: Tiem phong cum");
    if (p2) p2->addHistoryEntry("2025-06-15: Duong huyet cao - ke don thuoc");

    // Dat lich
    clinic.scheduleAppointmentForPatient("P001", "D001", "2025-09-10", "09:00", "Kham dinh ky");
    clinic.scheduleAppointmentForPatient("P002", "D002", "2025-09-11", "10:00", "Tai kham tieu duong");

    // Benh nhan khong ton tai
    clinic.scheduleAppointmentForPatient("P999", "D001", "2025-09-12", "11:00", "Test");

    // Hien thi du lieu
    clinic.showAllPatients();
    clinic.showAllDoctors();
    clinic.showAllAppointments();

    // Bac si cap nhat
    Doctor* doc = clinic.findDoctorById("D002");
    if (doc) {
        doc->viewAppointments(clinic.appointments);
        if (!doc->assignedAppointmentIds.empty()) {
            int appt = doc->assignedAppointmentIds.front();
            doc->updateAppointmentStatus(clinic.appointments, appt, ApptStatus::COMPLETED);
        }
    }

    clinic.showAllAppointments();

    // Huy 1 lich
    clinic.cancelAppointment(1);
    clinic.showAllAppointments();

    cout << "\n[Ket thuc chuong trinh]\n";
    return 0;
}
