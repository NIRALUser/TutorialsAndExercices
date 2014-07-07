#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMedianImageFilter.h"
#include "MedianFilterCLP.h"

int main(int argc, char *argv[])
{	
	PARSE_ARGS;	

 
	//Image Type//
	typedef itk::Image<unsigned char, 3> ImageType;

	//Input Image//
	typedef itk::ImageFileReader<ImageType> ReaderType; 
	ReaderType::Pointer reader = ReaderType::New(); 
	reader->SetFileName(argv[1]); 

	//MedianImage Filtering//
	typedef itk::MedianImageFilter <ImageType, ImageType> FilterType;
	FilterType::Pointer medianFilter=FilterType::New();
	FilterType::InputSizeType filterRadius;
	filterRadius.Fill(2);
    	if(argc > 2)
    	{
        	filterRadius.Fill(atoi(argv[3]));
    	}
    	medianFilter->SetRadius(filterRadius);
    	medianFilter->SetInput( reader->GetOutput() );
	
	//Output Image
	typedef itk::ImageFileWriter<ImageType> WriterType;  
	WriterType::Pointer writer = WriterType::New(); 
	writer->SetInput(medianFilter->GetOutput()); 
	writer->SetFileName(argv[2]);
	writer->Update(); 
}
