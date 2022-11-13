#include "LPR.h"

void LPR::InitParams(vector<void*> params) {}

vector<vector<Mat>>& LPR::Execute() {
    cout << "LPR~ start" << endl;
    {
        // 创建车牌识别源文件夹
        Uuid creator;
        src_path += creator.create_uuid();
        string create_src_dir = "mkdir " + src_path;
        ExecuteShell(create_src_dir);
    }
    
    // 1、将 Mat 写出到 src_path
    vector<vector<Mat>>& _raw_images = get_raw_images();
    for (vector<Mat>& images : _raw_images) {
        WriteMat(images);
    }

    {
        // 创建车牌识别目标文件夹
        Uuid creator;
        dst_path += creator.create_uuid();
        string create_dst_dir = "mkdir " + dst_path;
        ExecuteShell(create_dst_dir);
    }
    
    // 2、开启一个子线程来执行 test.py
    // string cmd = "cd /home/cwm/Graduation/cv/pythonmicroserver-update_weights && python test.py";
    string first_cmd = "cd /home/cwm/Graduation/cv/pythonmicroserver-update_weights";
    string second_cmd = "python test.py --src " + src_path + " --dst " + dst_path;
    string complete_cmd = first_cmd + " && " + second_cmd;
    ExecuteShell(complete_cmd);

    // 3、将结果集读入成 Mat
    ReaderImages reader;
    vector<Mat>& images = get_result_image();
    images = reader.read(dst_path);
    PushBack(images);
    cout << "LPR~ end" << endl;
    return get_result_image_s();
}

void LPR::WriteMat(vector<Mat>& images) {
    WriterImages writer;
    writer.WriterMat(images, src_path);
}

void LPR::ExecuteShell(string& cmd) {
    FILE* fp = NULL;
    fp = popen(cmd.c_str(), "w");
    if (!fp) {
        cout << "LPR execute shell cmd failed~" << endl;
        exit(EXIT_FAILURE);
    }
    pclose(fp);
}

vector<Mat> LPR::ReadImage() {
    ReaderImages read_images;
    return read_images.read(dst_path);
}