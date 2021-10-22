
#include <gtkmm/treeview.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/dialog.h>
#include "status.h"
#include "warning.h"

constexpr int DEFAULT_POPUP_WIDTH2 = 800;
constexpr int DEFAULT_POPUP_HEIGHT2 = 500;


class Profilewindow : public Gtk::ScrolledWindow
{
public:
  Profilewindow(const std::string& profile, const std::string& status);
  void on_button_clicked();

protected:
  Glib::RefPtr<Gtk::Builder> builder;
  
  std::unique_ptr<Gtk::Box> p_box;
  std::unique_ptr<Gtk::Label> p_name;

  std::unique_ptr<Gtk::ComboBoxText> p_modes;
  std::unique_ptr<Gtk::Button> p_confirm;
  
  std::unique_ptr<std::basic_string<char>> c_status;
  std::unique_ptr<std::basic_string<char>> c_profile;
  
  std::unique_ptr<Gtk::Dialog> w_dialog;
  std::unique_ptr<Warning> w_settings; 
private:
  template <typename T_Widget>
  std::unique_ptr<T_Widget> get_widget(const Glib::ustring name, const Glib::RefPtr<Gtk::Builder> &builder);
};
