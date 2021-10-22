#include <gtkmm/treeview.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/dialog.h>
#include "status.h"

class Warning : public Gtk::ScrolledWindow
{
public:
  Warning(const std::string& profile, const std::string& status, Gtk::Dialog& dialog);
  void do_continue();
  void not_continue();

protected:
  Glib::RefPtr<Gtk::Builder> builder;
  
  std::unique_ptr<Gtk::Box> w_box1;
  std::unique_ptr<Gtk::Box> w_box2;
  std::unique_ptr<Gtk::Label> w_label;

  std::unique_ptr<Gtk::Button> w_button1;
  std::unique_ptr<Gtk::Button> w_button2;
  
  std::unique_ptr<std::basic_string<char>> w_status;
  std::unique_ptr<std::basic_string<char>> w_profile;
  Gtk::Dialog w_dialog;
private:
  template <typename T_Widget>
  std::unique_ptr<T_Widget> get_widget(const Glib::ustring name, const Glib::RefPtr<Gtk::Builder> &builder);
};
