#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <sstream>

using namespace std;
using namespace cv;

#define interval 1  //修改这里以改变多久保存一帧

#include <time.h>
#include <chrono>

/*
 * Author:周旭
 * email：zhouxu.zx.cn@gmail.com
 *
 * 为了更加清楚
 * 1.本程序是为了保存所需要截取的视频为每一帧的图像格式
 * 2.本程序保存的风格与TUM数据集相同，可适用于SLAM自己数据集的读取
 * 3.本程序保存的图像格式为png，大小为640*480
 * 4.在需要保存的文件夹内，需要新建一个名为rgb的文件夹和rgb.txt的文本文件分别用于保存图像和相关信息
 */

std::time_t getTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());//获取当前时间点
    std::time_t timestamp =  tp.time_since_epoch().count(); //计算距离1970-1-1,00:00的时间长度
    return timestamp;
}


int main(int argc,char ** argv)
{
    // 这里的参数更改为视频所在的绝对地址
	VideoCapture capture("/media/zhouxu/zhouxu/dataset/20221108_huawei_camera/VID_20221108_175409.mp4");
	if (!capture.isOpened()){
		return -1;
	}
	int imgIndex = 0;

	// 这里保存的是rgb图片的名称和即将读取图片的地址
	// 为防止意外，需要在相应地方新建一个rgb.txt
    string filename = "/home/zhouxu/dataset/20221108_huawei_camera/VID_20221108_175409/rgb.txt";
    ofstream outfile;
    outfile.open(filename);

	Mat frame;
	capture >> frame;
	while (!frame.empty()) {

        time_t timestamps;
        timestamps =  getTimeStamp();
        string timestamp_str = to_string(timestamps);
        timestamp_str.insert(timestamp_str.begin()+7,'.');
        string timestamp = timestamp_str;




        std::stringstream ss;
//        此处为当时适配KITTI数据集名称所使用的的代码
//        ss <<  "/home/zhouxu/dataset/VID_20221019_134435/"
//           << std::setw(6) << std::setfill('0') << imgIndex << ".png";

        // 这里保存的是图片的位置，保存到rgb文件夹里面
        ss<<"/home/zhouxu/dataset/20221108_huawei_camera/VID_20221108_175409/rgb/"<<timestamp<<".png";

        Mat dst(480, 640, CV_8UC3);
        resize(frame,frame,dst.size(),0,0,INTER_LINEAR);

		if (imgIndex % interval == 0) {
			//第一个参数是写入的文件名，第二个参数是Mat类型的图像数据。
			imwrite(ss.str().c_str(), frame);
		}

        outfile << timestamp <<" "<<"rgb/"<<timestamp<<".png" << endl;

		capture >> frame;
	}

    outfile.close();

	return 0;
}
