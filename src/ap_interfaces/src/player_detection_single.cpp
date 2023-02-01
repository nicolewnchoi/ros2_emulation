#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <deque>
#include <thread>
#include <stdlib.h>
#include <mutex> 

//print to file
#include <iostream>
#include <fstream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "ap_interfaces/msg/score.hpp"
#include "ap_interfaces/msg/pos.hpp"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video.hpp>

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include "CameraFLIR.h"

//#include "image_transport/image_transport.hpp"
//#include "sensor_msgs/image_encodings.hpp"

using namespace std;
using namespace std::chrono_literals;
using namespace cv;
using namespace std::chrono;
using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;

int frameId;

class PublisherNode : public rclcpp::Node
{
    ap_interfaces::msg::Pos * pos_raw;
public:
    PublisherNode(ap_interfaces::msg::Pos * pos)
        : Node("PlayerDetectionPublisher"), count_(0), pos_raw(pos), flag(0)
    {
        publisher_ = this->create_publisher<ap_interfaces::msg::Pos>("pos_raw", 10);
    }
    void publishMsg(ap_interfaces::msg::Pos *pos){
            ap_interfaces::msg::Pos pos_raw_msg = *pos;

            //test time duration
            pos_raw_msg.timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

            count_++;
            
            std::string output;
            output += " ";
            output += std::to_string(pos_raw_msg.total);
            output += " ";
            output += std::to_string((pos_raw_msg.x)[0]);
            output += " ";
            output += std::to_string((pos_raw_msg.y)[0]);

            // Prep display message
            RCLCPP_INFO(
                this->get_logger(), "\nPublishing '%s'", output.c_str());
                
            //lets ad the time this message was published to the message so qwe can compare inside 
            // unity
            //https://stackoverflow.com/questions/31255486/how-do-i-convert-a-stdchronotime-point-to-long-and-back
            double time_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
            pos_raw_msg.msg_sent_ms = time_ms;    //set the system time the message is sent
            //

            this->publisher_->publish(pos_raw_msg);
    }

private:
    rclcpp::Publisher<ap_interfaces::msg::Pos>::SharedPtr publisher_;
    size_t count_;
    int flag;
};



Mat Init_background(Mat first_frame){
    // read from file
    // int img_height = 750;
    // int img_width = 960;
    // Mat background_raw = imread("D:/Airplay_ros_main/ros2_emulation/src/ap_interfaces/src/background960_750.jpg");

    // roi960*750
    // int bg_height = 750;
    // int bg_width = 960;
    // int bg_cut_start_x = 160;
	// int bg_cut_start_y = 137;
    //960*640
    // int img_height = 640;
    // int img_width = 960;
    // int cut_start_x = 200;
	// int cut_start_y = 192;

    //table demo
    int img_height = 480;
    int img_width = 720;
    int cut_start_x = 300;
	int cut_start_y = 320;


    Mat background_raw(first_frame, Rect(cut_start_x, cut_start_y, img_width, img_height));
    //remove all green
    // vector<Mat> channels;
    // Mat background_removegreen;
    // split(background_raw, channels);
    // channels[1] = Mat::zeros(background_raw.rows, background_raw.cols, CV_8UC1);
    // merge(channels, background_removegreen);

    //convert_to_grey
    // Mat background_grey;
    // cvtColor(background_raw, background_grey, cv::COLOR_BGR2GRAY);

	return background_raw;

}


deque<Mat> background_subtraction(Mat frame_input, Mat background_input){

    Mat recording;
	Mat result;
	Mat result_hsv;
	Mat testmat;

    //table demo
    int img_height = 480;
    int img_width = 720;
    int cut_start_x = 300;
	int cut_start_y = 320;
    
    // green color
    int low_H = 39;
    int low_S = 58;
    int low_V = 81;
    int high_H = 114;
    int high_S = 255;
    int high_V = 255;
    

    

    // old version
    int low_H_all = 0;
	int low_S_all = 0;
	int low_V_all = 60;
    int high_H_all = 360 / 2;
	int high_S_all = 235;
	int high_V_all = 255;
	Mat result_hsv_copy;
	Mat result_final, result_all;
    Mat green_mask, colorMask;
    Mat only_green;
	vector<Mat> channels;

    deque<Mat> Buffer;

    Mat current(frame_input, Rect(cut_start_x, cut_start_y, img_width, img_height));
    
    // old version
    absdiff(current, background_input, result);

    cvtColor(result, result_hsv, COLOR_BGR2HSV);
    // split(result_hsv, channels);

    if (!frame_input.empty())
    {

        // merge(channels, result_hsv);
        inRange(result_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), green_mask);
        inRange(result_hsv, Scalar(low_H_all, low_S_all, low_V_all), Scalar(high_H_all, high_S_all, high_V_all), result_all);
        //preprocess
        // Mat elementErosion = getStructuringElement(MORPH_ELLIPSE, Size(2 * 3 + 1, 2 * 3 + 1));
        // erode(green_mask, green_mask, elementErosion);
        // Mat elementDilate = getStructuringElement(MORPH_ELLIPSE,  Size(2 * 6 + 1, 2 * 6 + 1));
        // dilate(green_mask, green_mask, elementDilate);

        bitwise_xor(green_mask, result_all, result_final);
        //absdiff(result_hsv, only_green, result_final);
        // // int threshold_value = 120;
        // int threshold_type = 0; //0 Binary
        // int const max_binary_value = 255;
        // threshold( result_final, result_final, threshold_value, max_binary_value, threshold_type );
        // imshow("result_all:",result_all);
        // imshow("green_mask:",green_mask);
        // imshow("result_final:",result_final);
        Buffer.push_back(result_final);
    }

    // HSV
    // absdiff(current, background_input, result);
    // cvtColor(result, result_hsv, COLOR_BGR2HSV);
    // inRange(result_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), green_mask);
    // bitwise_and(result_hsv, result_hsv, result_final, green_mask);
    // imshow("remove green:", result_final);
    // cvtColor(result_final, result_final, COLOR_HSV2BGR);
    // cvtColor(result_final, result_final, COLOR_BGR2GRAY);
    // // threshold to binary
    
    // Buffer.push_back(result_final);

    // another try
    // absdiff(current, background_input, result);

    // cvtColor(result, result_hsv, COLOR_BGR2HSV);
    // cvtColor(result, result_grey, COLOR_BGR2GRAY);
    // inRange(result_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), green_mask);
    // int morphosize = 1;
    // int opIterations = 1;
    // Mat MorphoElement = getStructuringElement( MORPH_RECT, Size( 2*morphosize + 1, 2*morphosize+1 ));
    // morphologyEx(green_mask, green_mask, MORPH_CLOSE, MorphoElement);
    // add(green_mask, result_grey, colorMask);
    // // split(result_hsv, channels);

        
    // // merge(channels, result_hsv);
    // // //cvtColor(result_hsv, result_final, cv::COLOR_BGR2GRAY);
    // // inRange(result_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), result_final);
    // // Buffer.push_back(result_hsv);
    // imshow("colorMask:", colorMask);
    // int threshold_value = 0;
    // int threshold_type = 0; //0 Binary
    // int const max_binary_value = 255;
    // threshold( colorMask, result_final, threshold_value, max_binary_value, threshold_type );
    // Buffer.push_back(result_final);

    return Buffer;
	

}

Mat AverageFrame(vector<Mat> frames){
    Mat temp;
    Mat temp1;
    Mat result;
    cout << frames[0].size() << endl;
    frames[0].convertTo(temp, CV_32FC3);
    Mat avgImg(frames[0].rows, frames[0].cols, CV_32FC3);
    avgImg = temp;
    //Mat captured_img;
    //cout<< "frames size:" << frames.size() << endl;
    if (frames.size() > 1){

        for(int i = 1 ; i < frames.size(); i++){
            // captured_img = frames[i];
            // accumulate(captured_img, avgImg);
            frames[i].convertTo(temp1, CV_32FC3);
            //accumulate(temp, avgImg);
            avgImg += temp1;
            cout<< i << endl;
        }

    }
    //avgImg = avgImg / float(frames.size());
    avgImg = avgImg / float(frames.size());
    avgImg.convertTo(result, CV_8UC3);

    //cout << "result size: " << avgImg.size() << endl;
    return result;

}

void detect_pos(ap_interfaces::msg::Pos* pos_raw, std::shared_ptr<PublisherNode> &node) {
    int first_flag = 0;

    FILE *fp = fopen("cam_detect_duration.csv","w+");

    double intial_time = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
    double last_flush_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();

    Mat frame, frame_rgb, fgMask, fgMask_gray;
    Mat fgMask_erode, fgMask_dilate;
    Mat frame_diff;
    Mat input, input_erode, input_dilate, input_grey;
    vector<Mat> captured_frames;
    Mat avgframe;

    CameraFLIR theFLIRCamera;
    theFLIRCamera.Initialize();
    //cout<< "FLIR Initialize completed"<<endl;

    Mat Background(480, 720, CV_8UC3, Scalar());
    
    deque<Mat> buffer;

    //para in while loop
    vector<Point> contours_poly_temp;
    Point2f centers_contours_temp;
    float radius_contours_temp;
    vector<Point2f>centers;
    vector<float>radius;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //test_HSV();
    //test_thres();
    while(true){
        double start_loop_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
        auto timestart =  duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        frame = theFLIRCamera.GrabFrame(0);
        double frame_grab_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
        frameId++;
        //cvtColor(frame, frame_rgb, cv::COLOR_BGR2RGB);
        //cout << "grab frane!" << endl;
        if(frame.empty()){
            pos_raw->total = -1;
            //pos1->timestamp = static_cast<double>(time.nano);
            (pos_raw->x)[0] = -1;
            (pos_raw->y)[0] = -1;
            (pos_raw->player_id)[0] = -1;
            (pos_raw->size)[0] = -1;

        }else{
            // start time
            

            if (first_flag < 11){
                // cout<< "frame type: " << type2str(frame.type()) << endl;
                //cout<< "first_flag: "<<first_flag << endl;
                captured_frames.push_back(frame);
                // cout <<"captured_frames: "<< captured_frames.size() << endl;
                //cout << "start average frame" << endl;
                //cout << "frame size:" << frame.size() << endl;
                avgframe = AverageFrame(captured_frames);
                cout << "finish averaging frame " << endl;
                Background = Init_background(avgframe);
                
                if (first_flag == 10){

                    imwrite("result10.jpg", Background);
                }
                
                first_flag++;
                //cout << "background size: " << Background.size() <<endl;
            }

            buffer = background_subtraction(frame, Background);
            //cout << "get buffer " << endl;

            //check whether there are available frames in buffer
			if (!buffer.empty())
			{
				frame_diff = static_cast<int>(buffer.size());
				input = buffer.back().clone(); //choose the most recent frame as input
				buffer.clear();
			}

            //GaussianBlur(input, input_erode, Size(3, 3), 0, 0);
            Mat elementErosion = getStructuringElement(MORPH_ELLIPSE, Size(2 * 3 + 1, 2 * 3 + 1));
            erode(input, input_erode, elementErosion);
            //cout <<"erode end"<<endl;
       
            Mat elementDilate = getStructuringElement(MORPH_ELLIPSE,  Size(2 * 6 + 1, 2 * 6 + 1));
	        dilate(input_erode, input_dilate, elementDilate);

            // extract contours and find blob
            contours.clear();
            hierarchy.clear();
            findContours(input_dilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
            size_t size_contours = contours.size();
            
            centers.clear();
            radius.clear();

            
            for( size_t k = 0; k < size_contours; k++ ){
                if (contourArea(contours[k]) > 100){
                    approxPolyDP( contours[k], contours_poly_temp, 3, true );
                    minEnclosingCircle( contours_poly_temp, centers_contours_temp, radius_contours_temp );
                    if (radius_contours_temp > 1000 || radius_contours_temp < 30) {continue;}
                    centers.push_back(centers_contours_temp);
                    radius.push_back(radius_contours_temp);
                }
            }

            
            if (!centers.empty()){
                (pos_raw->total) = centers.size();
                pos_raw->id = frameId;
                pos_raw->frame_grab_ms = frame_grab_ms;  
                for(int i = 0; i < centers.size(); i++){
                    circle( input_dilate, centers[i], (int)radius[i] + 10, (0,0,255), 8);
                    (pos_raw->x)[i] = (float)centers[i].x;
                    (pos_raw->y)[i] = (float)(480 - centers[i].y);
                    (pos_raw->size)[i] = (float)radius[i];
                }
                double frame_done_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
                pos_raw->frame_done_processing_ms = frame_done_ms;  

                node->publishMsg(pos_raw);
            }


            /* debug print statements to file for timing purposes
            fprintf(fp,"%.2f\n",(start_loop_ms-intial_time));
            if(start_loop_ms-last_flush_ms>60000){
                cout<<"Flushing now"<<endl;
                fflush(fp);
                exit(0);
                last_flush_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
            }
            */

            //Test add sleep to slow down processing 
            double now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
            double dur_ms = now_ms - start_loop_ms;
            if(dur_ms < 33){
                int diff_ms = (int)(33 - dur_ms);
                // cout << "sleep for " << diff_ms << "ms" << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(diff_ms));
            }
            /**/
        }
        
    }
}
int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);

    ap_interfaces::msg::Pos pos_raw;
    frameId = 0;

    rclcpp::init(argc, argv);

    std::shared_ptr<PublisherNode> node = std::make_shared<PublisherNode>(&pos_raw);
    detect_pos(&pos_raw,node);

    // std::thread th_detect(detect_pos,&pos_raw);

    // // You MUST use the MultiThreadedExecutor to use, well, multiple threads
    // rclcpp::executors::MultiThreadedExecutor executor;
    // auto player_detection_pubnode = std::make_shared<PublisherNode>(&pos_raw);

    // executor.add_node(player_detection_pubnode);

    // executor.spin();
    // th_detect.join();
    rclcpp::shutdown();
    return 0;
}