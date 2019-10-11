#include "itkImageFileReader.h"
#include "itkGDCMImageIO.h"
#include "opencv2/opencv.hpp"

#include <list>
#include <fstream>

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cerr << "Usage: " << std::endl;
        std::cerr << argv[0] << " DicomImage\n";
        return EXIT_FAILURE;
    }

    using InputPixelType = signed short;
    constexpr unsigned int InputDimension = 2;

    using InputImageType = itk::Image<InputPixelType, InputDimension>;
    using ReaderType = itk::ImageFileReader<InputImageType>;
    ReaderType::Pointer reader = ReaderType::New();

    using ImageIOType = itk::GDCMImageIO;
    ImageIOType::Pointer gdcmImageIO = ImageIOType::New();
    reader->SetImageIO(gdcmImageIO);

    reader->SetFileName(argv[1]);

    try
    {
        reader->Update();
    }
    catch (itk::ExceptionObject &e)
    {
        std::cerr << "exception in file reader " << std::endl;
        std::cerr << e << std::endl;
        return EXIT_FAILURE;
    }

    InputImageType::Pointer image = reader->GetOutput();
    // InputImageType::IndexType ind = image->GetBufferedRegion().GetIndex();
    InputImageType::SizeType size = reader->GetOutput()->GetLargestPossibleRegion().GetSize();
    InputImageType::IndexType index = reader->GetOutput()->GetLargestPossibleRegion().GetIndex();
    // std::cerr << index << std::endl;
    // std::cerr << size << std::endl;
    InputImageType::IndexType ind;
    ind[0] = 513;
    ind[1] = 513;
    InputImageType::PixelType testval = image->GetPixel(ind);

    cv::Mat out(512,512,CV_64F);
    for (int i = 0; i < size[0]; i++)
    {
        ind[0] = i;
        for (int j = 0; j < size[1]; j++)
        {
            ind[1] = j;
            InputImageType::PixelType tmpval = image->GetPixel(ind);
            if (tmpval > 2000)
            {
                tmpval = 0;
            }
            if (tmpval < -100)
            {
                tmpval = -100;
            }
            if (tmpval > 400)
            {
                tmpval = 400;
            }
            double tmp = double(tmpval + 100) / 500;
            out.at<double>(j,i)=tmp*255;
        }
    }
    // std::memcpy((void*)out.data, &imgvec, imgvec.size()*sizeof(int));

    // std::cerr << ind << std::endl;

    // std::cerr << testval << std::endl;
    // std::cerr << out << std::endl;

    // cv::Mat img = itk::itkOpenCVImageBridge::ITKImageToCVMat<InputImageType>(reader->GetOutput());

    cv::imwrite("test2.png", out);

    return EXIT_SUCCESS;
}