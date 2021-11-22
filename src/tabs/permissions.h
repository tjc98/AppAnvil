#ifndef TABS_PERMISSIONS_H
#define TABS_PERMISSIONS_H

#include "status.h"
#include "parser.h"

#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/enums.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/searchentry.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treeviewcolumn.h>
#include <gtkmm/stack.h>
#include <memory>
#include <string>
#include <vector>

class Permissions : public Status
{
  public:
    Permissions();
    void refresh();
    void change_status();
    
  protected:
    void list_perms(std::string filename);
    std::shared_ptr<Parser> parse;
    
  private:
    const std::vector<std::string> col_names{"Program", "Permissions"};
    std::shared_ptr<StatusColumnRecord> col_record;
    Gtk::TreeRow new_row;
    std::string perms;
    std::string program;
    std::string permissions;
    
};

#endif // TABS_PPERMISSIONS_H
