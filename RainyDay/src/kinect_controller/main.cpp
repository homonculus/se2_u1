
/// [headers]
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>

#include <opencv2/opencv.hpp>
#include "kinect_controller.h"


using namespace cv;

int main(int argc, char *argv[]){
    KinectController my_controller(4,4);
  	std::cout << "HELLO THERE IAM TRYING TO BE HERE! 1" << std::endl;
  	my_controller.print_dimensions();

}
