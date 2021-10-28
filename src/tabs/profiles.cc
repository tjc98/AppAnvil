#include "jsoncpp/json/json.h"
#include "profiles.h"

#include <giomm.h>
#include <glibmm.h>
#include <iostream>
#include <string>
#include <vector>

// refresh() is based on assumptions about the output of aa-status.
// If those assumptions are incorrect, or aa-status changes, this could crash.
void Profiles::refresh(){
  Json::Value root = Status::get_status_JSON();
  Json::Value profiles = root["profiles"];

  int num_found = 0;

  list_store->clear();
  for(auto prof = profiles.begin(); prof != profiles.end(); prof++){
    std::string key = prof.key().asString();
    if(filter(key)){
      auto row = *(list_store->append());
      row[col_record.profile_col] = key;
      row[col_record.status_col] =  profiles.get(key, UNKNOWN_STATUS).asString();
      num_found++;
    }
  }

  s_found_label->set_text(" " + std::to_string(num_found) + " matching profiles");
}

void Profiles::order_columns(){
  // Notice the column retrieved is a TreeViewColumn, not a TreeModelColumn like was used with s_record
  // The column numbers depend on the order the are added to s_view
  auto *profile_view_col = s_view->get_column(0);
  profile_view_col->set_reorderable();
  profile_view_col->set_resizable();
  profile_view_col->set_min_width(MIN_COL_WIDTH);
  profile_view_col->set_sort_column(col_record.profile_col);

  auto *status_view_col = s_view->get_column(1);
  status_view_col->set_reorderable();
  status_view_col->set_resizable();
  status_view_col->set_min_width(MIN_COL_WIDTH);
  status_view_col->set_sort_column(col_record.status_col);
}

bool Profiles::change_status(const std::string& profile, const std::string& status){
  std::string opposite_status; //Stores command based on the current status
  if(status == "enforce"){
    opposite_status = "aa-complain";
  }
  if(status == "complain"){
    opposite_status = "aa-enforce";
  }

//Command to execute to change the correct profile to the opposite status
  std::vector<std::string> args = {"pkexec", opposite_status, profile};

  std::cout << args[0] + " " + args[1] + " " + args[2] << std::endl;
  std::string child_output;
  std::string child_error;
  int exit_status = 0;


  //Executed in commandline, copied from status.cc 
  //Glib::spawn_sync("/usr/sbin/", args, Glib::SpawnFlags::SPAWN_DEFAULT, {}, &child_output, &child_error, &exit_status);
  Glib::spawn_sync("/usr/sbin/", args, Glib::SpawnFlags::SPAWN_SEARCH_PATH, {}, &child_output, &child_error, &exit_status);


  if(exit_status != 0){
    std::cout << "Error calling '"<< args[0] <<"'. " << child_error << std::endl;
    child_output = "{\"processes\": {}, \"profiles\": {}";
  }

  return true;

}

Profiles::Profiles()
:  list_store{Gtk::ListStore::create(col_record)}
{
  s_view->set_model(list_store);
  s_view->append_column("Profile", col_record.profile_col);
  s_view->append_column("Status", col_record.status_col);

  refresh();
  order_columns();

  auto sig_handler = sigc::mem_fun(*this, &Profiles::on_search_changed);
  s_search->signal_search_changed().connect(sig_handler, true);
  s_use_regex->signal_clicked().connect(sig_handler, true);
  s_match_case->signal_clicked().connect(sig_handler, true);
  s_whole_word->signal_clicked().connect(sig_handler, true);
  s_view->signal_row_activated().connect(sigc::mem_fun(*this, &Profiles::on_row_click)); //signal when row in TreeView is clicked
  this->show_all();
}

void Profiles::on_search_changed(){
  refresh();
}
void Profiles::on_row_click(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) //method to handle signal_row_clicked
{
  const auto iter = list_store->get_iter(path); //convert the path to an iter so you can actually use it.
  //std::cout << Gtk::TreeModel::get_iter(path) << std::endl;
  if(iter) //Just makes sure the conversion worked.
  {
	  const auto row = *iter; //derefrence the iter to actually access the row
	  
	  //Note, I had to cast these to basic_string<char> because they were under some weird type called TreeValueProxy
	  auto path = (std::basic_string<char>) row[col_record.profile_col]; //The path field from the row
	  auto status = (std::basic_string<char>) row[col_record.status_col]; //The status field from the row
	  std::cout << "Row activated: ID=" << path.c_str() << ", Name=" << status.c_str() << std::endl; //c_str converts basic_string to an actual string

    //Executes change_status to switch the status, prints an error if it doesn't work.
    if(!change_status(path, status))
    {
      std::cout << "Error changing the status" << std::endl;
    }
  }
  //Profilewindow(); //This isn't doing anything yet

  //Refresh after changing the status so that it shows up
  refresh();
  order_columns();
}
