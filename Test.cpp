#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/wait.h>

using namespace std;
using namespace cv;

void ExecuteShell(string& cmd) {
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
}

int main() {
    // Mat image = imread("/home/cwm/Graduation/cv/photos/1.png");
    // Mat result = Trim(image);
    // cout << result.size().width << " " << result.size().height << endl;
    // imwrite("/home/cwm/Graduation/cv/photo_results/1.png", result);

    Execute();

    return 0;
}