#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMedianImageFilter.h"
#include "MedianFilterCLP.h"
#include "stdlib.h"

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
	
    	if(radius < 1)
    	{
        	std::cout<<"Radius value must be non-zero positive integer. Set by default to 2."<<std::endl;
		 
		filterRadius.Fill(2);
    	}
	else
	{
		filterRadius.Fill(radius);
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
