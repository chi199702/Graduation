#include <pthread.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

class ProcessorTArm;

struct Package {
    Package(int _sequence, ProcessorTArm* _process) : sequence(_sequence), process(_process) {}
    int sequence;
    ProcessorTArm* process;
};

void* threadfunc(void* param);

class ProcessorTArm {
public:
    ProcessorTArm(const string& _name, const int& _age) : name(_name), age(_age) {}

    void process() {
        int sequence = 1;
        Package* package = new Package(sequence, this);
        pthread_t thread;
        if (pthread_create(&thread, NULL, threadfunc, &package) != 0) {
            cout << "线程创建失败~" << endl;
            return;
        }
        void* result_pt;
        if (pthread_join(thread, &result_pt) != 0) {
            cout << "线程执行失败~" << endl;
            return;
        }
        bool* value = reinterpret_cast<bool*>(result_pt);
        cout << "线程执行结果：" << *value << endl;
    }

    bool ExecuteModule(int sequence) {
        cout << "ExecuteModule execute~" << endl;
        cout << name << " " << age << endl;
        return true;
    }

private:
    string name;
    int age;
};

void* threadfunc(void* param) {
    cout << "线程开始执行~" << endl;
    Package* package = reinterpret_cast<Package*>(param);
    int sequence = package -> sequence;
    ProcessorTArm* process = package -> process;
    bool result = process -> ExecuteModule(sequence);
    bool* result_pt = new bool(result);
    return result_pt;
}

int main() {
    time_t first, second;
    first = time(NULL);
    sleep(2);
    second = time(NULL);
    cout << difftime(second, first) << endl;
    return 0;
}