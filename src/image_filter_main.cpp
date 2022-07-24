#include <image_filter.hpp>

#include <memory>
#include <string>
#include <iostream>

int main(int argc, char** argv){

    std::unique_ptr<image_filter::ImageFilter> filter;

    if(argc == 2){
        filter.reset(new image_filter::ImageFilter);
    }else{
        std::cerr << "Usage: " << argv[0] << " <target image> " << std::endl;
        return 1;
    }

    const std::string in_image_path = argv[1];
    filter->init(in_image_path);

    filter->enterMainLoop();

    return 0;
}

