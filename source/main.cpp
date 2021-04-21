#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    //Open the default video camera
    cv::VideoCapture cap(0);

    // if not success, exit program
    if (cap.isOpened() == false) {
        std::cout << "Cannot open the video camera" << std::endl;
        std::cin.get(); //wait for any key press
        return EXIT_FAILURE;
    }

    double dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    std::cout << "Resolution of the video : " << dWidth << " x " << dHeight << std::endl;

    std::string window_name = "My Camera Feed";
    cv::namedWindow(window_name); //create a window called "My Camera Feed"

    while (true) {
        cv::Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video

        //Breaking the while loop if the frames cannot be captured
        if (bSuccess == false) {
            std::cout << "Video camera is disconnected" << std::endl;
            std::cin.get(); //Wait for any key press
            return EXIT_FAILURE;
        }

        //show the frame in the created window
        imshow(window_name, frame);

        //wait for for 10 ms until any key is pressed.
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop
        //If any key is not pressed withing 10 ms, continue the loop
        static constexpr int ESCAPE = 27;
        static constexpr int DELAY = 1;
        if (cv::waitKey(DELAY) == ESCAPE) {
            std::cout << "Esc key is pressed by user. Stoppig the video" << std::endl;
            break;
        }
    }

    return EXIT_SUCCESS;
}