#ifndef __VISUALIZE_CONSISTENCY__
#define __VISUALIZE_CONSISTENCY__
#ifdef __APPLE__
        #include <sys/uio.h>
#else
        #include <sys/io.h>
#endif

#include <iostream>
#include <opencv2/tracking.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <typeinfo>
#include <vector>


using namespace std;
using namespace cv;

// global Parameters
vector<string> _img_list; // name of all images.
const char * _corr_file_path;
string _ikg_data_path;
string _local_data_path;

struct file_info{

  int id;

	string img_date;
	string img_camera_id;

	string scan_row;
	string scan_col;
	string image_row;
	string image_col;

};

struct sequence_info{

	string name;
  int location;

};





class VISUALIZE_CONSISTENCY
{
public: //Accessable for all entities.

//Parameters



//Functions
	void read_corr(const char *path);
	void show_img(string local_data_path, string img_name, string image_col, string image_row);
  stringstream get_filename_from_date_cameranNum(string img_date, string img_camera_id);




private: //Only accessable for this class members.

	// Parameters
	vector<const char*>_content;
	vector<file_info>_corr_info;
  vector<sequence_info>_sequence_info_vec;
  int _search_start, _search_end;

	stringstream file_name;
	stringstream temp_name;



	Mat _current_img;


	string str;
	//


	// functions ??
	void find_img_and_copy(vector<file_info> info);
  void sear_coordinates(vector<file_info> corr_info);


};

#endif // endif __VISUALIZE_CONSISTENCY__
