#include <iostream>
#include <opencv2/opencv.hpp>

#include <boost/program_options.hpp>

#include <project_version.h>

int main(int argc, char* argv[])
{
    std::string filename;
    size_t customWidth;
    size_t customHeight;
    boost::program_options::options_description desc("options");
    desc.add_options()
        // All options:
        ("filename,f", boost::program_options::value<std::string>(&filename)->default_value(""), "video file name.\n") //
        ("width", boost::program_options::value<size_t>(&customWidth)->default_value(0), "width of the frames in the video stream.\n") //
        ("height", boost::program_options::value<size_t>(&customHeight)->default_value(0), "height of the frames in the video stream.\n") //
        ("version,v", "print version number and exit.\n") // Version
        ("help,h", "produce help message.\n"); // Help
    boost::program_options::variables_map options;
    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), options);
        boost::program_options::notify(options);
    } catch (const std::exception& exception) {
        std::cerr << "error: " << exception.what() << std::endl;
        return EXIT_FAILURE;
    }
    if (options.count("help")) {
        std::cout << desc << std::endl;
        return EXIT_SUCCESS;
    }
    if (options.count("version")) {
        std::cout << "version: " + std::string(PROJECT_VERSION) << std::endl;
        return EXIT_SUCCESS;
    }

    cv::VideoCapture capture;
    if (filename.empty()) {
        capture.open(cv::VideoCaptureAPIs::CAP_ANY);
    } else {
        capture.open(filename);
    }

    if (!capture.isOpened()) {
        std::cerr << "Cannot open the video camera!" << std::endl;
        return EXIT_FAILURE;
    }

    size_t width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    size_t height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
    width = (customWidth == 0) ? width : customWidth;
    height = (customHeight == 0) ? height : customHeight;
    const cv::Size customSize(width, height);

    std::cout << "Resolution of the video: " << width << "x" << height << "." << std::endl;
    std::cout << "Frames per seconds: " << capture.get(cv::CAP_PROP_FPS) << "." << std::endl;

    static constexpr std::string_view WINDOW_NAME = "My Camera";
    cv::namedWindow(WINDOW_NAME.data());

    static constexpr int DELAY_MS = 1;
    static constexpr int ESCAPE_KEY = 27;
    while (cv::waitKey(DELAY_MS) != ESCAPE_KEY) {
        cv::Mat frame;
        if (!capture.read(frame)) {
            std::cerr << "Video camera is disconnected!" << std::endl;
            return EXIT_FAILURE;
        }

        if (customWidth != 0 || customHeight != 0) {
            cv::resize(frame, frame, customSize, 0, 0);
        }

        imshow(WINDOW_NAME.data(), frame);
    }
    capture.release();
    cv::destroyAllWindows();
}