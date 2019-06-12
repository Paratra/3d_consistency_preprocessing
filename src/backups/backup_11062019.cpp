// COPYRIGHT: Ming Song
// Fuer Masterarbeit an der IKG, Leibniz Univerisitaet Hannover, 2019.
// __function__: pre-processing ikg-data. Since there is enormous amount of the data, one has to use c++.
// __author__:  MingSong
#include "3d_consistency_graph/visualize_consistency.h"


bool is_file_exist(string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

stringstream VISUALIZE_CONSISTENCY::get_filename_from_date_cameranNum(string img_date, string img_camera_id){

  stringstream file_name;
  file_name << "170331_" << img_date << "_Camera_" << img_camera_id << ".png";
  return file_name;
}



void VISUALIZE_CONSISTENCY::sear_coordinates(vector<file_info>corr_info){

  // std::cout << corr_info.size() << '\n';
  string current_scan_row;
  string current_scan_col ;

  for (size_t i = 0; i < corr_info.size(); i++) {
  // for (size_t i = 0; i < 1; i++) {

    stringstream current_filename = get_filename_from_date_cameranNum(corr_info[i].img_date, corr_info[i].img_camera_id);
    current_scan_row = corr_info[i].scan_row;
    current_scan_col = corr_info[i].scan_col;

    std::cout << "############    "<< i << "  " << current_filename.str() << '\n';

    for (size_t j = 0; j < corr_info.size(); j++)
    {
      if (i != j)
      {
        if ( (current_scan_row == corr_info[j].scan_row) && (current_scan_col == corr_info[j].scan_col) )
        {
          string others_filename = get_filename_from_date_cameranNum(corr_info[j].img_date, corr_info[j].img_camera_id).str();
          std::cout << j <<get_filename_from_date_cameranNum(corr_info[j].img_date, corr_info[j].img_camera_id).str()<< '\n';
          show_img(_local_data_path, others_filename);

        }
      }
    }
    show_img(_local_data_path, current_filename.str());
    waitKey(10);
  }



}




void VISUALIZE_CONSISTENCY::show_img(string local_data_path, string img_name){


  string current_img_path = local_data_path + img_name;
  _current_img = imread(current_img_path.c_str(), IMREAD_COLOR);

  // std::cout << _current_img.at<Vec3b>(1,1) << '\n';

  if( _current_img.empty() ){                      // Check for invalid input
    cout <<  "Could not open or find the image" << std::endl ;
    exit(-1);
  }

  namedWindow( img_name, WINDOW_AUTOSIZE ); // Create a window for display.
  imshow( img_name, _current_img );                // Show our image inside it.


}



void VISUALIZE_CONSISTENCY::find_img_and_copy(string img_date, string img_camera_id){

  temp_name = get_filename_from_date_cameranNum(img_date, img_camera_id);
  // temp_name << "170331_" << img_date << "_Camera_2" << ".png";


  // printf("%s\n", img_date.c_str());
  if (temp_name.str() != file_name.str() && (img_camera_id == "2") && (img_date != "") )
  { // only act when the files are changed!

    file_name.str(""); // clear file name sstream
    file_name << temp_name.rdbuf(); //copy temp_name to file_name


    // std::cout << file_name.str() << '\n';
    // std::cout << img_date << '\n';

    string local_file = _local_data_path + file_name.str();

    // std::cout << is_file_exist(local_file) << '\n';

    if (!is_file_exist(local_file)) { // if the file doesn't exist, then move it to local_path

      string command = "cp -rf " + _ikg_data_path + file_name.str() + " " + _local_data_path; //configure a shell command
      system(command.c_str()); //excute the command that copy the img to local data folder
      std::cout << "Image " << file_name.str() << " is copied."<< '\n';
    }


    _img_list.push_back(file_name.str());

  }
  temp_name.str(""); // clear temp name sstream

}



void VISUALIZE_CONSISTENCY::read_corr(char const *path) {

  // f(path, "r");
  ifstream f(path,ios::in);
  // std::cout << typeid(f).name()<< '\n';

  if (! f.is_open())
    {
    cout << "open file failed! the programmer will exit!" << endl;
    exit(-1);
    }


  std::cout << "\033[1;33mProcessing...\033[0m" << "\n";
  int a = 0;
  while (! f.eof() )
    {
      f.getline (_aray_params->s, 100);

      const char *d = ",";
      char *p;
      p = strtok(_aray_params->s, d);

      // cout << p << endl;

      while(p){
        _content.push_back(p);
        p=strtok(NULL,d);
      }

      // #########   informations from corr
      // [camera_time, camera_id, scan_row, scan_col, image_row, image_col]

      _file_info.img_date = _content[0];
      _file_info.img_camera_id = _content[1];

      _file_info.scan_row = _content[2];
      _file_info.scan_col = _content[3];
      _file_info.image_row = _content[4];
      _file_info.image_col = _content[5];

      if (_file_info.img_camera_id == "2") {
        _corr_info.push_back(_file_info);
      }


      // std::cout << _corr_info.size() << '\n';

      // ######### copy img to local data folder
      find_img_and_copy(_file_info.img_date, _file_info.img_camera_id);


      // ########## control to only process data partially. cuz there is too much.

      // a += 1;
      // if (a>1500000) {
      //   // std::cout << "\033[1;32mDone !\033[0m" << "\n";
      //   break;
      // }

    }

  sear_coordinates(_corr_info);



  // show_img(_img_list);

  std::cout << "\033[1;32mDone!\033[0m" << "\n";

}


int main() {
  _corr_file_path = "/Users/mikesong/Desktop/Masterthesis/preperation_3/cpp_project_try/data/170331_092835_Scanner_2.corr";
  _ikg_data_path = "/Volumes/mingdisk/ImagesMaster/20170331_icsens/";
  _local_data_path = "../data/20170331_icsens/";

  VISUALIZE_CONSISTENCY visualize_consistency;
  visualize_consistency.read_corr(_corr_file_path);



  return 0;

}
