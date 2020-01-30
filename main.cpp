#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    struct timespec start, end, temp1, temp2;

    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "Cannot open the video camera" << endl;
        cin.get();
        return -1;
    }

    string window_name = "My Camera Feed";
    namedWindow(window_name);

    double time_rendering = 0;
    double time_working = 0;
    unsigned long count = 0;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    while (true)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &temp1);

        Mat frame;

        if (!cap.read(frame))
        {
            cout << "Video camera is disconnected" << endl;
            cin.get();
            break;
        }


        for (int i = 0; i < frame.rows; i++)
            for (int j = 0; j < frame.cols; j++)
                if (frame.at<Vec3b>(i, j)[0] < frame.at<Vec3b>(i, j)[1] - 10 &&
                    frame.at<Vec3b>(i, j)[2] < frame.at<Vec3b>(i, j)[1] - 10 &&
                    frame.at<Vec3b>(i, j)[1] > 64)
                {
                    frame.at<Vec3b>(i, j)[0] = 183;
                    frame.at<Vec3b>(i, j)[1] = 60;
                    frame.at<Vec3b>(i, j)[2] = 23;
                }



        imshow(window_name, frame);

        count++;
        clock_gettime(CLOCK_MONOTONIC_RAW, &temp2);
        time_rendering += (temp2.tv_sec - temp1.tv_sec + 0.000000001 * (temp2.tv_nsec - temp1.tv_nsec));

        if (waitKey(10) == 27)
        {
            cout << "Stoppig the video" << endl;
            break;
        }
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    time_working = (end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));

    cout << "fps: " << (count / time_working) << endl;
    cout << "rendering time: " << (int) (time_rendering / time_working * 100) << "%" << endl;

    return 0;
}