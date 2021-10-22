#ifndef TABS_PROFILES_H
#define TABS_PROFILES_H

#include "status.h"
#include "profilewindow.h"

#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/enums.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/searchentry.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treeviewcolumn.h>
#include <memory>
#include <string>
#include <vector>

class Profiles : public Status
{
  public:
    Profiles();
    void refresh();
  
  protected:
    // Signal handlers    
    void on_search_changed();
    void on_row_click(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);

  private:
    const std::vector<std::string> col_names{"Profile", "Status"};
    std::shared_ptr<StatusColumnRecord> col_record;
};

#endif // TABS_PROFILES_H
