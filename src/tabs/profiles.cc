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

  col_record->clear();
  for(auto prof = profiles.begin(); prof != profiles.end(); prof++){
    std::string key = prof.key().asString();
    if(filter(key)){
      auto row = col_record->new_row();
      col_record->set_row_data(row, 0, key);
      col_record->set_row_data(row, 1, profiles.get(key, UNKNOWN_STATUS).asString());
      num_found++;
    }
  }

  Status::set_status_label_text(" " + std::to_string(num_found) + " matching profiles");
}

void Profiles::change_status(){
  //s_row = s_view.get_selection();
  std::cout << "button works\n" << std::endl;
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
  std::vector<std::string> args = {"sudo", opposite_status, profile};

  std::string child_output;
  std::string child_error;
  int exit_status = 0;


  //Executed in commandline, copied from status.cc 
  Glib::spawn_sync("/usr/sbin/", args, Glib::SpawnFlags::SPAWN_DEFAULT, {}, &child_output, &child_error, &exit_status);


  if(exit_status != 0){
    std::cout << "Error calling '"<< args[0] <<"'. " << child_error << std::endl;
    child_output = "{\"processes\": {}, \"profiles\": {}";
  }

  return true;

}

Profiles::Profiles()
: col_record{StatusColumnRecord::create(Status::get_view(), col_names)}
{


  auto func = sigc::mem_fun(*this, &Profiles::on_search_changed);
  auto func_2 = sigc::mem_fun(*this, &Profiles::on_apply_button_pressed);
  Status::set_refresh_signal_handler(func);
  Status::set_apply_signal_handler(func_2);



  this->show_all();
}

void Profiles::on_search_changed(){
  refresh();
}


void Profiles::on_apply_button_pressed(){
  change_status();
}

