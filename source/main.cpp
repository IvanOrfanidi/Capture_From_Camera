#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // Open the default video camera.
    cv::VideoCapture cap(cv::VideoCaptureAPIs::CAP_ANY);
    if (cap.isOpened() == false) {
        std::cerr << "Cannot open the video camera!" << std::endl;
        return EXIT_FAILURE;
    }

    const auto width = cap.get(cv::CAP_PROP_FRAME_WIDTH); // Get the width of frames of the video.
    const auto height = cap.get(cv::CAP_PROP_FRAME_HEIGHT); // Get the height of frames of the video.
    std::cout << "Resolution of the video: " << width << " x " << height << "." << std::endl;

    const auto fps = cap.get(cv::CAP_PROP_FPS);
    std::cout << "Frames per seconds: " << fps << "." << std::endl;

    static constexpr std::string_view WINDOW_NAME = "My Camera";
    cv::namedWindow(WINDOW_NAME.data());

    static constexpr int DELAY_MS = 10;
    static constexpr int ESCAPE_KEY = 27;
    while (cv::waitKey(DELAY_MS) != ESCAPE_KEY) {
        cv::Mat frame;

        // Read a new frame from video.
        if (cap.read(frame) == false) { // Breaking the while loop if the frames cannot be captured.
            std::cerr << "Video camera is disconnected!" << std::endl;
            return EXIT_FAILURE;
        }

        // Show the frame in the created window.
        imshow(WINDOW_NAME.data(), frame);
    }
    cap.release();
    cv::destroyAllWindows();

    return EXIT_SUCCESS;
}