#include "permissions.h"
Permissions::Permissions()
: col_record{StatusColumnRecord::create(Status::get_view(), col_names)}
{
  std::string test1 = "test 1";
  std::string test2 = "test 2";
  auto row = col_record->new_row();
  col_record->set_row_data(row, 0, test1);
  col_record->set_row_data(row, 1, test2);
  this->show_all();
}

void Permissions::add_data_to_record(std::string data){

  int num_found = 0;

  col_record->clear();
  /*
  for(){
    auto row = col_record->new_row();
    col_record->set_row_data(row, 0, key);
    col_record->set_row_data(row, 1, profiles.get(key, UNKNOWN_STATUS).asString());
    num_found++;
  }

  Status::set_status_label_text(" " + std::to_string(num_found) + " matching profiles");
  */
}
