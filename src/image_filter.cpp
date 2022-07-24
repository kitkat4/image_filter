#include <image_filter.hpp>


namespace image_filter{

ImageFilter* ImageFilter::instance_ = nullptr;

ImageFilter::ImageFilter():
    nfeatures_(500),
    threshold_(100){

    instance_ = this;
}

ImageFilter::~ImageFilter(){

    cv::destroyAllWindows();

    instance_ = nullptr;
}

void ImageFilter::init(const std::string& image_path){

    image_ = cv::imread(image_path);
    image_org_ = image_.clone();

    if(image_path.rfind('/') == std::string::npos){
        window_name_ = image_path;
    }else{
        window_name_ = image_path.substr(image_path.rfind('/'),
                                         image_path.size() - image_path.rfind('/'));
    }

    cv::namedWindow(window_name_, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_EXPANDED);

    cv::createButton("reset", callbackResetButton);
    cv::createTrackbar("nfeatures", "", &nfeatures_, 10000, nullptr);
    cv::createButton("ORB", callbackOrbButton);
    cv::createTrackbar("threshold", "", &threshold_, 255, nullptr);
    cv::createButton("threshold", callbackThresholdButton);
}

void ImageFilter::enterMainLoop(){

    int key;
    bool finish = false;

    while(! finish){
        
        cv::imshow(window_name_, image_);
        key = cv::waitKey(1);

        switch(key){
        case 'q':
            finish = true;
            break;
        // default:
            // do nothing
        }
    }
}

void ImageFilter::callbackResetButton(int state, void * data){

    instance_->image_ = instance_->image_org_.clone();
}

void ImageFilter::callbackOrbButton(int state, void * data){

    // force reset
    if(instance_->image_org_.channels() != 1){
        cv::cvtColor(instance_->image_org_, instance_->image_, cv::COLOR_BGR2GRAY);
    }

    cv::Ptr<cv::ORB> orb = cv::ORB::create(instance_->nfeatures_,
                                           1.2f, 8, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 20);

    my_utils_kk4::StopWatch stop_watch;
    stop_watch.start();

    orb->detect(instance_->image_, instance_->keypoints_, cv::noArray());
    orb->compute(instance_->image_, instance_->keypoints_, instance_->descriptors_);

    stop_watch.stop();

    cv::cvtColor(instance_->image_, instance_->image_, cv::COLOR_GRAY2BGR);

    instance_->drawKeyPoints(instance_->image_, instance_->keypoints_);

    std::cout << "[ INFO] Extracted " << instance_->keypoints_.size() << " keypoints in " << stop_watch.getResult() * 1000 << " ms" << std::endl;
                                       ;
}


void ImageFilter::callbackThresholdButton(int state, void * data){

    if(instance_->image_.channels() != 1){
        cv::cvtColor(instance_->image_, instance_->image_, cv::COLOR_BGR2GRAY);
    }
    cv::threshold(instance_->image_, instance_->image_, instance_->threshold_, 255, cv::THRESH_BINARY);
}

void ImageFilter::drawKeyPoints(cv::Mat image, const std::vector<cv::KeyPoint>& keypoints){

    const cv::Point2f offset(2, 2);

    for(size_t i = 0; i < keypoints.size(); i++){

        const cv::KeyPoint p = keypoints[i];;
        cv::rectangle(image, p.pt - offset, p.pt + offset, cv::Scalar(0, 255, 0), 1, cv::LINE_8, 0);
    }
}
    

}
