#include <iostream>
#include <string>
#include <fstream>
using namespace std;


enum SEVERITY
{
    CRITICAL = 0,
    ERROR      = 1,
    WARNING = 2,
    INFO          = 3
};

struct LOG
{
    string date;
    string time;
    SEVERITY severity = SEVERITY::INFO;
    string message;

    fstream logFile;
    SEVERITY logLevel = INFO;
    
    string toString();

    void close();
    bool open(string filename);
    void Message(SEVERITY severity, string message);
    void info(string msg);
};

string severityToString(SEVERITY severity)
{
    switch (severity)
    {
    case CRITICAL:
        return "CRITICAL";
    case ERROR:
        return "ERROR";
    case WARNING:
        return "WARN";
    case INFO:
        return "INFO";
    default:
        return "UNKNOWN";
        break;
    }
}

string LOG::toString()
{
    return date + " " + time + " " + severityToString(severity) + " " + message;
}

void LOG::Message(SEVERITY severity, string message)
{
    if (severity <= logLevel)
    {
        LOG logEntry
        {
            "2021-02-23",
            "08:40:00",
            severity,
            message
        };

        logFile << logEntry.toString() << endl;
    }
}

void LOG::info(string msg)
{
    Message(SEVERITY::INFO, msg);
}

bool LOG::open(string filename)
{
    logFile.open(filename, ios::out | ios::app);
    return logFile.is_open();
}

void LOG::close()
{
    logFile.close();
}

int main()
{
    LOG log;

    if (log.open("mylog.txt"))
    {
        log.Message(SEVERITY::INFO, "Program startup complete.");

        int a;
        string choice;
        cin >> choice;
        try
        {
            a = stoi(choice);
        }
        catch (const std::exception& ex)
        {
            log.Message(SEVERITY::CRITICAL, ex.what());
        }

        log.Message(SEVERITY::INFO, "Terminating program.");

        log.close();
    }
}

