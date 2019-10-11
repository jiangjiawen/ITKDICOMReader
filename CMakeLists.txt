cmake_minimum_required(VERSION 3.0)
project(IOExamples)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(ITK REQUIRED NO_CMAKE_FIND_ROOT_PATH)

add_executable(DicomImageReadWrite main.cpp)
target_link_libraries(DicomImageReadWrite  ${ITK_LIBRARIES})

find_package(OpenCV REQUIRED NO_CMAKE_FIND_ROOT_PATH)
target_link_libraries(DicomImageReadWrite "opencv_core" "opencv_highgui" "opencv_imgcodecs" "opencv_imgproc")