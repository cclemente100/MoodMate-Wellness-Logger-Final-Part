
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// ============================================================
// Base class: MoodEntry
// ============================================================
class MoodEntry {
private:
    string date;
    int rating;
    string note;

public:
    // Default constructor
    MoodEntry();

    // Parameterized constructor
    MoodEntry(string entryDate, int entryRating, string entryNote);

    // Setters
    void setDate(string entryDate);
    void setRating(int entryRating);
    void setNote(string entryNote);

    // Const getters
    string getDate() const;
    int getRating() const;
    string getNote() const;

    // Display the base portion of an entry
    void printEntry() const;
};

MoodEntry::MoodEntry()
    : date("Unspecified"), rating(3), note("No note") {
}

MoodEntry::MoodEntry(string entryDate, int entryRating,
                     string entryNote) {
    setDate(entryDate);
    setRating(entryRating);
    setNote(entryNote);
}

void MoodEntry::setDate(string entryDate) {
    if (entryDate.empty()) {
        date = "Unspecified";
    } else {
        date = entryDate;
    }
}

void MoodEntry::setRating(int entryRating) {
    if (entryRating < 1 || entryRating > 5) {
        rating = 3;
    } else {
        rating = entryRating;
    }
}

void MoodEntry::setNote(string entryNote) {
    if (entryNote.empty()) {
        note = "No note";
    } else {
        note = entryNote;
    }
}

string MoodEntry::getDate() const {
    return date;
}

int MoodEntry::getRating() const {
    return rating;
}

string MoodEntry::getNote() const {
    return note;
}

void MoodEntry::printEntry() const {
    cout << "Date: " << date << '\n';
    cout << "Mood rating: " << rating << "/5\n";
    cout << "Note: " << note << '\n';
}


// ============================================================
// Derived class: WellnessEntry
// WellnessEntry IS-A MoodEntry.
// ============================================================
class WellnessEntry : public MoodEntry {
private:
    double sleepHours;
    int exerciseMinutes;

public:
    // Default constructor
    WellnessEntry();

    // Parameterized constructor
    WellnessEntry(string entryDate, int entryRating,
                  string entryNote, double entrySleepHours,
                  int entryExerciseMinutes);

    // Setters
    void setSleepHours(double hours);
    void setExerciseMinutes(int minutes);

    // Const getters
    double getSleepHours() const;
    int getExerciseMinutes() const;

    // Display all five fields
    void printEntry() const;
};

WellnessEntry::WellnessEntry()
    : MoodEntry(), sleepHours(0.0), exerciseMinutes(0) {
}

WellnessEntry::WellnessEntry(
    string entryDate, int entryRating, string entryNote,
    double entrySleepHours, int entryExerciseMinutes)
    : MoodEntry(entryDate, entryRating, entryNote),
      sleepHours(0.0), exerciseMinutes(0) {

    setSleepHours(entrySleepHours);
    setExerciseMinutes(entryExerciseMinutes);
}

void WellnessEntry::setSleepHours(double hours) {
    if (hours < 0.0 || hours > 24.0) {
        sleepHours = 0.0;
    } else {
        sleepHours = hours;
    }
}

void WellnessEntry::setExerciseMinutes(int minutes) {
    if (minutes < 0 || minutes > 1440) {
        exerciseMinutes = 0;
    } else {
        exerciseMinutes = minutes;
    }
}

double WellnessEntry::getSleepHours() const {
    return sleepHours;
}

int WellnessEntry::getExerciseMinutes() const {
    return exerciseMinutes;
}

void WellnessEntry::printEntry() const {
    // Reuse the base-class display function.
    MoodEntry::printEntry();

    cout << "Sleep hours: " << sleepHours << '\n';
    cout << "Exercise minutes: " << exerciseMinutes << '\n';
}


// ============================================================
// Composition class: WellnessLogger
// WellnessLogger HAS-A collection of WellnessEntry objects.
// ============================================================
class WellnessLogger {
private:
    WellnessEntry entries[20];
    int entryCount;

public:
    WellnessLogger();

    bool addEntry(const WellnessEntry& entry);
    void displayEntries() const;
    bool updateEntry(int entryNumber, string date, int rating,
                     string note, double sleepHours,
                     int exerciseMinutes);
    void displayAverageRating() const;

    bool saveToFile() const;
    void loadFromFile();
    int getEntryCount() const;
};

WellnessLogger::WellnessLogger() : entryCount(0) {
}

bool WellnessLogger::addEntry(const WellnessEntry& entry) {
    if (entryCount >= 20) {
        cout << "The log is full. No entry was added.\n";
        return false;
    }

    entries[entryCount] = entry;
    ++entryCount;

    cout << "Entry added successfully.\n";
    return true;
}

int WellnessLogger::getEntryCount() const {
    return entryCount;
}

void WellnessLogger::displayEntries() const {
    if (entryCount == 0) {
        cout << "The wellness log is empty.\n";
        return;
    }

    cout << "\n========== Wellness Entries ==========\n";

    for (int i = 0; i < entryCount; ++i) {
        cout << "\nEntry " << (i + 1) << '\n';
        cout << "--------------------------------------\n";
        entries[i].printEntry();
    }

    cout << "======================================\n";
}

bool WellnessLogger::updateEntry(
    int entryNumber, string date, int rating, string note,
    double sleepHours, int exerciseMinutes) {

    // Entry numbers shown to users begin at 1.
    if (entryNumber < 1 || entryNumber > entryCount) {
        cout << "Invalid entry number. No changes were made.\n";
        return false;
    }

    WellnessEntry& entry = entries[entryNumber - 1];

    // Update through public setters to preserve validation.
    entry.setDate(date);
    entry.setRating(rating);
    entry.setNote(note);
    entry.setSleepHours(sleepHours);
    entry.setExerciseMinutes(exerciseMinutes);

    cout << "Entry updated successfully.\n";
    return true;
}

void WellnessLogger::displayAverageRating() const {
    if (entryCount == 0) {
        cout << "No entries available to calculate an average.\n";
        return;
    }

    int total = 0;

    for (int i = 0; i < entryCount; ++i) {
        total += entries[i].getRating();
    }

    double average =
        static_cast<double>(total) / entryCount;

    cout << fixed << setprecision(1);
    cout << "Average mood rating: " << average << "/5\n";
    cout.unsetf(ios::floatfield);
    cout << setprecision(6);
}

bool WellnessLogger::saveToFile() const {
    ofstream outFile("moodmate.txt");

    if (!outFile.is_open()) {
        cout << "Error: Could not open moodmate.txt for saving.\n";
        return false;
    }

    // Write a complete snapshot, replacing previous contents.
    outFile << fixed << setprecision(2);

    for (int i = 0; i < entryCount; ++i) {
        outFile << entries[i].getDate() << '\n';
        outFile << entries[i].getRating() << '\n';
        outFile << entries[i].getNote() << '\n';
        outFile << entries[i].getSleepHours() << '\n';
        outFile << entries[i].getExerciseMinutes() << '\n';
    }

    outFile.close();

    if (outFile.fail()) {
        cout << "Error: A problem occurred while writing "
             << "moodmate.txt.\n";
        return false;
    }

    cout << "Saved " << entryCount
         << " entr(y/ies) to moodmate.txt.\n";
    return true;
}

void WellnessLogger::loadFromFile() {
    ifstream inFile("moodmate.txt");

    if (!inFile.is_open()) {
        // A missing file is normal on the first run.
        cout << "No existing moodmate.txt file found. "
             << "Starting with an empty log.\n";
        return;
    }

    string date;
    string ratingLine;
    string note;
    string sleepLine;
    string exerciseLine;

    int loaded = 0;

    while (true) {
        // EOF between records is normal.
        if (!getline(inFile, date)) {
            if (inFile.eof()) {
                break;
            }

            cout << "File read error. Stopping the load.\n";
            break;
        }

        // Detect a record that starts but is incomplete.
        if (!getline(inFile, ratingLine) ||
            !getline(inFile, note) ||
            !getline(inFile, sleepLine) ||
            !getline(inFile, exerciseLine)) {

            cout << "Malformed file: incomplete record. "
                 << "The incomplete record was skipped; "
                 << "loading stopped.\n";
            break;
        }

        // Parse every numeric field strictly.
        int rating;
        double sleepHours;
        int exerciseMinutes;

        istringstream ratingStream(ratingLine);
        istringstream sleepStream(sleepLine);
        istringstream exerciseStream(exerciseLine);

        char extraRating, extraSleep, extraExercise;

        if (!(ratingStream >> rating) ||
            (ratingStream >> extraRating) ||
            !(sleepStream >> sleepHours) ||
            (sleepStream >> extraSleep) ||
            !(exerciseStream >> exerciseMinutes) ||
            (exerciseStream >> extraExercise)) {

            cout << "Malformed file: a numeric field is invalid. "
                 << "The malformed record was skipped; "
                 << "loading stopped.\n";
            break;
        }

        // Never load beyond the fixed capacity.
        if (entryCount >= 20) {
            cout << "The file contains more than 20 records. "
                 << "Additional records were not loaded.\n";
            break;
        }

        // Reconstruct through the validating constructor.
        WellnessEntry entry(date, rating, note,
                            sleepHours, exerciseMinutes);

        entries[entryCount] = entry;
        ++entryCount;
        ++loaded;
    }

    cout << "Loaded " << loaded
         << " valid entr(y/ies) from moodmate.txt.\n";
    inFile.close();
}


// ============================================================
// Input helpers
// Read whole lines to handle spaces and invalid console input.
// ============================================================

string readText(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

int readInt(const string& prompt) {
    string line;
    int value;
    char extra;

    while (true) {
        cout << prompt;
        getline(cin, line);

        istringstream input(line);

        if ((input >> value) && !(input >> extra)) {
            return value;
        }

        cout << "Please enter a whole number.\n";
    }
}

double readDouble(const string& prompt) {
    string line;
    double value;
    char extra;

    while (true) {
        cout << prompt;
        getline(cin, line);

        istringstream input(line);

        if ((input >> value) && !(input >> extra)) {
            return value;
        }

        cout << "Please enter a valid number.\n";
    }
}

WellnessEntry collectEntry() {
    string date = readText("Enter date: ");
    int rating = readInt("Enter mood rating (1-5): ");
    string note = readText("Enter note: ");
    double sleepHours = readDouble("Enter sleep hours (0-24): ");
    int exerciseMinutes =
        readInt("Enter exercise minutes (0-1440): ");

    return WellnessEntry(date, rating, note,
                         sleepHours, exerciseMinutes);
}


// ============================================================
// Main menu
// ============================================================
int main() {
    WellnessLogger logger;

    cout << "====================================\n";
    cout << "           Welcome to MoodMate\n";
    cout << "====================================\n";

    // Load saved entries before showing the menu.
    logger.loadFromFile();

    bool running = true;

    while (running) {
        cout << "\n------------- Main Menu -------------\n";
        cout << "1. Add wellness entry\n";
        cout << "2. View entries\n";
        cout << "3. Update an entry\n";
        cout << "4. View average mood rating\n";
        cout << "5. Save entries\n";
        cout << "6. Save and exit\n";
        cout << "-------------------------------------\n";

        int choice = readInt("Choose an option: ");

        switch (choice) {
        case 1: {
            WellnessEntry entry = collectEntry();
            logger.addEntry(entry);
            break;
        }

        case 2:
            logger.displayEntries();
            break;

        case 3: {
            if (logger.getEntryCount() == 0) {
                cout << "No entries are available to update.\n";
                break;
            }

            logger.displayEntries();

            int number =
                readInt("Enter the entry number to update: ");

            // Reject invalid numbers before collecting new data.
            if (number < 1 ||
                number > logger.getEntryCount()) {
                cout << "Invalid entry number. "
                     << "No changes were made.\n";
                break;
            }

            cout << "Enter the replacement values.\n";

            WellnessEntry replacement = collectEntry();

            logger.updateEntry(
                number,
                replacement.getDate(),
                replacement.getRating(),
                replacement.getNote(),
                replacement.getSleepHours(),
                replacement.getExerciseMinutes());
            break;
        }

        case 4:
            logger.displayAverageRating();
            break;

        case 5:
            logger.saveToFile();
            break;

        case 6:
            // Stay in the menu if saving fails.
            if (logger.saveToFile()) {
                cout << "Thank you for using MoodMate. Goodbye!\n";
                running = false;
            }
            break;

        default:
            cout << "Invalid menu choice. "
                 << "Please select a number from 1 to 6.\n";
        }
    }

    return 0;
}
