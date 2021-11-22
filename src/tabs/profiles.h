#ifndef TABS_PROFILES_H
#define TABS_PROFILES_H

#include "status.h"

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

class Profiles : public Status
{
  public:
    Profiles();
    void refresh();
    void change_status();
  
  protected:
    void on_search_changed();
    void on_apply_button_pressed();
    void on_row_clicked(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
    bool execute_change(const std::string& profile, const std::string& status);

  private:
    const std::vector<std::string> col_names{"Profile", "Status"};
    std::shared_ptr<StatusColumnRecord> col_record;
    Gtk::Stack m_stack;
    std::shared_ptr<Gtk::TreeView> t_view;
};

#endif // TABS_PROFILES_H
