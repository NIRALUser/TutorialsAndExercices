/*=============================================================================
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
=============================================================================*/
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMedianImageFilter.h"
#include "MedianFilterCLP.h"
#include "stdlib.h"
#include "itkImageIOBase.h"

void GetImageType ( std::string fileName , 
                  itk::ImageIOBase::IOComponentType &componentType )
{
  typedef itk::Image< unsigned char, 3 > ImageType ;
  itk::ImageFileReader<ImageType>::Pointer imageReader =
                itk::ImageFileReader< ImageType >::New() ;
  imageReader->SetFileName( fileName.c_str() ) ;
  imageReader->UpdateOutputInformation() ;
  componentType = imageReader->GetImageIO()->GetComponentType() ;
}

template< class TImage >
int ReadImage( const char* fileName ,
               typename TImage::Pointer image )
{
  typedef TImage                            ImageType ;
  typedef itk::ImageFileReader< ImageType > ImageReaderType ;
  typename ImageReaderType::Pointer reader = ImageReaderType::New() ;
  reader->SetFileName( fileName ) ;
  try
  {
    reader->Update() ;
  }
  catch( itk::ExceptionObject& e )
  {
    std::cerr << e.what() << std::endl ;
    return 1 ;
  }
  image->Graft( reader->GetOutput() ) ;
  return 0 ;
}
/* Creates the Median Filter and the output image with the input type. */
template< class ComponentType >
int MedianFilter( std::string inputFileName , std::string outputFileName ,
               int radius )
{ 
  typedef itk::Image< ComponentType , 3 > ImageType ;
	typedef itk::MedianImageFilter < ImageType , ImageType > FilterType ;
	typename FilterType::Pointer medianFilter = FilterType::New() ;
	typename FilterType::InputSizeType filterRadius ;
  typename ImageType::Pointer image = ImageType::New() ;
  if( ReadImage< ImageType >( inputFileName.c_str() , image ) )
  {
    std::cout << "Image could not be read." << std::endl ;
    return EXIT_FAILURE ;
  }
	
	if( radius < 1 )
	{
  	std::cout << "Radius value must be non-zero positive integer. Set by default to 2." << std::endl ;
		filterRadius.Fill( 2 ) ;
	}
	else
	{
		filterRadius.Fill( radius ) ;
	}
	medianFilter->SetRadius( filterRadius ) ;
  medianFilter->SetInput( image ) ;
	
	typedef itk::ImageFileWriter< ImageType > WriterType ;  
	typename WriterType::Pointer writer = WriterType::New() ; 
	writer->SetInput( medianFilter->GetOutput() ) ; 
	writer->SetFileName( outputFileName ) ;
	writer->Update() ; 
  return EXIT_SUCCESS ;
}

int main( int argc , char *argv[] )
{	
	PARSE_ARGS ;
  itk::ImageIOBase::IOPixelType pixelType ;
  itk::ImageIOBase::IOComponentType componentType ;
  try
  {
    GetImageType( input , componentType ) ;
/* Apply the Median Filter according to the type of the input file */
    switch( componentType )
    {
      case itk::ImageIOBase::UCHAR:
      {
        return MedianFilter< unsigned char >( input , output , radius ) ;
        break ;
      }
      case itk::ImageIOBase::CHAR:
      {
        return MedianFilter< char >( input , output , radius ) ;
        break ;
      }
      case itk::ImageIOBase::USHORT:
      {
        return MedianFilter< unsigned short >( input , output , radius ) ;
        break ;
      }
      case itk::ImageIOBase::SHORT:
      {
        return MedianFilter< short >( input , output , radius ) ;
        break ;
      }
      case itk::ImageIOBase::UINT:
      {
        return MedianFilter< unsigned int >( input , output , radius ) ;
        break ;
      }
      case itk::ImageIOBase::INT:
      {
        return MedianFilter< int >( input , output , radius ) ;
        break ;
      }
      case itk::ImageIOBase::ULONG:
      {     
        return MedianFilter< unsigned long >( input , output , radius ) ;
        break ;
      }
      case itk::ImageIOBase::LONG:
      {
        return MedianFilter< long >( input , output , radius ) ;
        break ;
      }
      case itk::ImageIOBase::FLOAT:
      {
        return MedianFilter< float >( input , output , radius ) ;
        break ;
      }
      case itk::ImageIOBase::DOUBLE:
      {
        return MedianFilter< double >( input , output , radius ) ;
        break ;
      }
      default:
      case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
      {
        std::cerr << "Unknown and unsupported component type!" << std::endl ;
        return EXIT_FAILURE ;
      }
    }
  }
  catch( itk::ExceptionObject &excep )
  {
    std::cerr << argv[0] << ": exception caught !" << std::endl ;
    std::cerr << excep << std::endl ;
    return EXIT_FAILURE ;
  }
return EXIT_SUCCESS ;
}
