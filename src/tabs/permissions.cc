#include "permissions.h"

Permissions::Permissions()
: col_record{StatusColumnRecord::create(Status::get_view(), col_names)}
{
   this->show_all();
}

void Permissions::list_perms(std::string filename){
   perms = parse->get_perms(filename);
   new_row = col_record->new_row();
   col_record->set_row_data(new_row, 0, program);
   col_record->set_row_data(new_row, 1, permissions);
}
