// #include <opencv2/opencv.hpp>
#include <iostream>
// #include <sys/wait.h>

using namespace std;
// using namespace cv;

/* void ExecuteShell(string& cmd) {
    FILE* fp = NULL;
    fp = popen(cmd.c_str(), "w");
    if (!fp) {
        cout << "LPR execute shell cmd failed~" << endl;
        exit(EXIT_FAILURE);
    }
    pclose(fp);
}

void Execute() {
    // 2、开启一个子线程来执行 test.py
    // string cmd = "cd /home/cwm/Graduation/cv/pythonmicroserver-update_weights && python test.py";
    string src_path = "/home/cwm/Graduation/cv/photos_raw";
    string dst_path = "/home/cwm/Graduation/cv/photos_lpr_result";
    string first_cmd = "cd /home/cwm/Graduation/cv/pythonmicroserver-update_weights";
    string second_cmd = "python test.py --src " + src_path + " --dst " + dst_path;
    string complete_cmd = first_cmd + " && " + second_cmd;
    ExecuteShell(complete_cmd);
} */

// class Test {
// public:
//     Test() {}

//     void* Execute(int num) {
//         row = new int(num);
//         return row;
//     }
// private:
//     int* row;
// };

// void* func1() {
//     Test* t = new Test();
//     return t -> Execute(50);
// }

int main() {
    double d = 200.0;
    double* a = new double(d);
    void* tmp_pt = a;
    double* b = reinterpret_cast<double*>(tmp_pt);
    unsigned int n1 = *b;
    float n2 = *b;
    int n3 = *b;
    cout << n1 << " " << n2 << " " << n3 << endl;
    return 0;
}