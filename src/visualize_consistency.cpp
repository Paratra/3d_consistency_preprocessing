// COPYRIGHT: Ming Song
// Fuer Masterarbeit an der IKG, Leibniz Univerisitaet Hannover, 2019.
// __function__: pre-processing ikg-data. Since there is enormous amount of the data, one has to use c++.
// __author__:  MingSong
#include "3d_consistency_graph/visualize_consistency.h"

// ############################################################

bool is_file_exist(string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

// ############################################################

// void get_index_for_partialData(_) {
//
// }



// #############################################################
stringstream VISUALIZE_CONSISTENCY::get_filename_from_date_cameranNum(string img_date, string img_camera_id){

  stringstream file_name;
  file_name << "170331_" << img_date << "_Camera_" << img_camera_id << ".png";
  return file_name;
}

// ############################################################

void VISUALIZE_CONSISTENCY::sear_coordinates(vector<file_info>corr_info){

  // std::cout << corr_info.size() << '\n';
  string current_scan_row;
  string current_scan_col ;

  // for (size_t i = 0; i < corr_info.size(); i++)

  ofstream OutFile;

  std::cout << "Generating 3d-consistency files... " << '\n';
  for (size_t i = 0; i < corr_info.size(); i++)
  {
  // for (size_t i = 0; i < 1; i++) {

    stringstream current_filename = get_filename_from_date_cameranNum(corr_info[i].img_date, corr_info[i].img_camera_id);



    string txt_filename = "../3d_consistency/" + current_filename.str() + ".txt";

    bool same_file = is_file_exist(txt_filename); // see if the same txt file been manipulated!
    //
    // //
    // if ((current_filename.str() == "170331_092835877_Camera_2.png") ||
    //     (current_filename.str() == "170331_092836377_Camera_2.png") ||
    //     (current_filename.str() == "170331_092836877_Camera_2.png") ||
    //     (current_filename.str() == "170331_092837877_Camera_2.png") ||
    //     (current_filename.str() == "170331_092838377_Camera_2.png") ||
    //     (current_filename.str() == "170331_092838877_Camera_2.png") ||
    //     (current_filename.str() == "170331_092839377_Camera_2.png") ||
    //     (current_filename.str() == "170331_092839877_Camera_2.png") ||
    //     (current_filename.str() == "170331_092840377_Camera_2.png") ||
    //     (current_filename.str() == "170331_092840877_Camera_2.png") ||
    //     (current_filename.str() == "170331_092841377_Camera_2.png") ||
    //     (current_filename.str() == "170331_092841877_Camera_2.png") ) {
    //    // (current_filename.str() == "170331_092836877_Camera_2.png") ||
    //    // (current_filename.str() == "170331_092837877_Camera_2.png") {
    //
    //   continue;
    // }
    //
    // }else{
    //
    //
    //
    // }
    //


    //
    if ( i == 0 ) {
      std::cout << "Generating for: "<< current_filename.str() << '\n';
      OutFile.open(txt_filename, ios::binary | ios::app | ios::in | ios::out);

      // ###############################################################
      //##### control the index will only around target file ##########
      for (size_t temp_index = 0; temp_index < _sequence_info_vec.size(); temp_index++) {
        if ( _sequence_info_vec[temp_index].name == current_filename.str() ) {
          if ( temp_index == 0 ) {
            _search_start = temp_index;
            _search_end = _sequence_info_vec[temp_index+3].location; // 2's end plus 1
          }else if (temp_index == _sequence_info_vec.size()-1){
            _search_start = _sequence_info_vec[temp_index-2].location;
            _search_end = corr_info.size();
          }else if(temp_index == _sequence_info_vec.size()-2){
            _search_start = _sequence_info_vec[temp_index-1].location;
            _search_end = corr_info.size();
          }else{
            _search_start = _sequence_info_vec[temp_index-1].location;
            _search_end = _sequence_info_vec[temp_index+2].location;
          }
        }
      }
      // std::cout << _search_start << " " << _search_end << '\n';
      // ###############################################################

    }else{
      if (!same_file)
      {
        OutFile.close();
        std::cout << "Generating for: "<< current_filename.str() << '\n';
        OutFile.open(txt_filename, ios::binary | ios::app | ios::in | ios::out);

        // ###############################################################
        //##### control the index will only around target file ##########
        for (size_t temp_index = 0; temp_index < _sequence_info_vec.size(); temp_index++) {
          if ( _sequence_info_vec[temp_index].name == current_filename.str() ) {
            if ( temp_index == 0 ) {
              _search_start = temp_index;
              _search_end = _sequence_info_vec[temp_index+3].location; // 2's end plus 1
            }else if (temp_index == _sequence_info_vec.size()-1){
              _search_start = _sequence_info_vec[temp_index-2].location;
              _search_end = corr_info.size();
            }else if(temp_index == _sequence_info_vec.size()-2){
              _search_start = _sequence_info_vec[temp_index-1].location;
              _search_end = corr_info.size();
            }else{
              _search_start = _sequence_info_vec[temp_index-1].location;
              _search_end = _sequence_info_vec[temp_index+2].location;
            }
          }
        }
        // std::cout << _search_start << " " << _search_end << '\n';
        // ###############################################################




      }
      // else
      // {
      //   // std::cout << current_filename .str()<< " is exist!" << '\n';
      //   // OutFile.close();
      //   // std::cout << "1" << '\n';
      //   i += 1;
      // }
    }


    current_scan_row = corr_info[i].scan_row;
    current_scan_col = corr_info[i].scan_col;

    // std::cout << "############    "<< i << "  " < < current_filename.str() << '\n';

    // OutFile << (corr_info[i].image_col, corr_info[i].image_col) << '\n';
    OutFile << "(" << corr_info[i].image_row << " " << corr_info[i].image_col << ")";
    //






    int ind = 0;

    for (size_t j = _search_start; j < _search_end; j++)
    {
      if (i != j)
      {
        if ( (current_scan_row == corr_info[j].scan_row) && (current_scan_col == corr_info[j].scan_col) )
        {
          if ( ind < 2 )
          {

            string others_filename = get_filename_from_date_cameranNum(corr_info[j].img_date, corr_info[j].img_camera_id).str();

            OutFile << ", [" << others_filename<<" "<< "("<<corr_info[j].image_row << " " << corr_info[j].image_col << ") ]";
            ind += 1;



            // show_img(_local_data_path, others_filename, corr_info[j].image_col, corr_info[j].image_row);

            // corr_info.remove(j)
          }else{
          // std::cout << "2" << '\n';
            // ind = 0;
            break;

          }
        }
      }
    }





    OutFile << "\n";


    // show_img(_local_data_path, current_filename.str(), corr_info[i].image_col, corr_info[i].image_row);




    // exit(1);
    // waitKey(5);

    // OutFile.close();

  }
  OutFile.close();


}


// ############################################################

void VISUALIZE_CONSISTENCY::show_img(string local_data_path, string img_name, string image_col, string image_row){


  string current_img_path = local_data_path + img_name;
  _current_img = imread(current_img_path.c_str(), IMREAD_COLOR);

  int col = stoi( image_col );
  int row = stoi( image_row );

  // std::cout << col << " "<< row << '\n';

  _current_img(cv::Range( col-3, col+3 ), cv::Range( row-3, row+3 )) = 0;
  // _current_img(cv::Range(0, 10), cv::Range(0, 10)) = 0;
  // _current_img(cv::Range(0, 10), cv::Range(0, 10)) = 0;



  if( _current_img.empty() ){                      // Check for invalid input
    cout <<  "Could not open or find the image" << std::endl ;
    exit(-1);
  }

  namedWindow( img_name, WINDOW_AUTOSIZE ); // Create a window for display.
  imshow( img_name, _current_img );                // Show our image inside it.


}

// ############################################################

void VISUALIZE_CONSISTENCY::find_img_and_copy(vector<file_info> info){


  for (size_t i = 0; i < info.size(); i++) {
    /* code */


  string img_date = info[i].img_date;
  string img_camera_id = info[i].img_camera_id;

  temp_name = get_filename_from_date_cameranNum(img_date, img_camera_id); //result is stringstream
  // temp_name << "170331_" << img_date << "_Camera_2" << ".png";


  // printf("%s\n", img_date.c_str());
  if (temp_name.str() != file_name.str() && (img_date != "") )
  { // only act when the files are changed!

    sequence_info current_sequence_info;

    current_sequence_info.name = temp_name.str();
    current_sequence_info.location = i;

    // std::cout << i << '\n';

    _sequence_info_vec.push_back(current_sequence_info);


    // std::cout << _sequence_info_vec.size() << '\n';


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
}
// ############################################################

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
  int file_index = 0;
  while ( getline(f, str) )
    {
      file_info current_file_info;
      // f.getline (str, 100);

      const char *d = ",";
      char *p;
      p = strtok(&str[0u], d);

      // cout << p << endl;

      while(p){
        _content.push_back(p);
        p=strtok(NULL,d);
      }

      // #########   informations from corr
      // [camera_time, camera_id, scan_row, scan_col, image_row, image_col]

      current_file_info.id = file_index;

      current_file_info.img_date = _content[0];
      current_file_info.img_camera_id = _content[1];

      current_file_info.scan_row = _content[2];
      current_file_info.scan_col = _content[3];
      current_file_info.image_row = _content[4];
      current_file_info.image_col = _content[5];

      if (current_file_info.img_camera_id == "1") {
        _corr_info.push_back(current_file_info);
      }

      file_index += 1;


      // std::cout << _corr_info.size() << '\n';


      // ########## control to only process data partially. cuz there is too much.

      // a += 1;
      // if (a>1500000) {
      //   // std::cout << "\033[1;32mDone !\033[0m" << "\n";
      //   break;
      // }

    }
  // ######### copy img to local data folder
  find_img_and_copy(_corr_info);
  // #########
  sear_coordinates(_corr_info);



  // show_img(_img_list);

  std::cout << "\033[1;32mDone!\033[0m" << "\n";

}

// ############################################################

int main() {
  _corr_file_path = "../data/170331_092835_Scanner_2.corr";
  _ikg_data_path = "/Volumes/mingdisk/ImagesMaster/20170331_icsens/";
  _local_data_path = "../data/20170331_icsens/Camera_1";

  VISUALIZE_CONSISTENCY visualize_consistency;
  visualize_consistency.read_corr(_corr_file_path);

  return 0;

}
