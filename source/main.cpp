#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // Open the default video camera.
    cv::VideoCapture cap(cv::VideoCaptureAPIs::CAP_ANY);

    // If not success, exit program.
    if (cap.isOpened() == false) {
        std::cerr << "Cannot open the video camera!" << std::endl;
        return EXIT_FAILURE;
    }

    const double width = cap.get(cv::CAP_PROP_FRAME_WIDTH); // Get the width of frames of the video.
    const double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT); // Get the height of frames of the video.
    std::cout << "Resolution of the video : " << width << " x " << height << std::endl;

    static constexpr std::string_view window_name = "My Camera";
    cv::namedWindow(window_name.data()); // Create a window called "My Camera".

    cv::Mat frame;
    // Wait for for 10 ms until any key is pressed.
    // If any key is not pressed withing 10 ms, continue the loop.
    static constexpr int ESCAPE_KEY = 27;
    static constexpr int DELAY_MS = 10;
    while (cv::waitKey(DELAY_MS) != ESCAPE_KEY) {
        // Read a new frame from video.
        if (cap.read(frame) == false) { // Breaking the while loop if the frames cannot be captured.
            std::cerr << "Video camera is disconnected!" << std::endl;
            return EXIT_FAILURE;
        }

        // Show the frame in the created window.
        imshow(window_name.data(), frame);
    }
    std::cout << "Esc key is pressed by user. Stoppig the video." << std::endl;

    return EXIT_SUCCESS;
}