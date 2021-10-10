
#include <gtkmm/window.h>
#include <gtkmm/treeview.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>

class Profilewindow
{
public:
  Profilewindow();
  void on_button_clicked();

protected:
  Glib::RefPtr<Gtk::Builder> builder;
  
  std::unique_ptr<Gtk::Window> p_win;
  std::unique_ptr<Gtk::Box> p_box;
  std::unique_ptr<Gtk::Label> p_name;

  std::unique_ptr<Gtk::ComboBoxText> p_modes;
  std::unique_ptr<Gtk::Button> p_confirm;
private:
  template <typename T_Widget>
  std::unique_ptr<T_Widget> get_widget(const Glib::ustring name, const Glib::RefPtr<Gtk::Builder> &builder);
};
