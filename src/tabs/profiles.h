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
    void change_status();
  
  protected:
    // Signal handlers    
    void on_search_changed();

    void on_row_click(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
    bool change_status(const std::string& profile, const std::string& status);

    class StatusColumnRecord : public Gtk::TreeModel::ColumnRecord
    {
      public:
        StatusColumnRecord()
        {
          add(profile_col);
          add(status_col);
        }

      Gtk::TreeModelColumn<std::string> profile_col;
      Gtk::TreeModelColumn<std::string> status_col;
    };

    StatusColumnRecord col_record;
    Glib::RefPtr<Gtk::ListStore> list_store;
  private:
    Profilewindow pwindow;

};

#endif // TABS_PROFILES_H
