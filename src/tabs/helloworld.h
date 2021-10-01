#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/builder.h>
class Helloworld : public Gtk::ScrolledWindow
{
public:
  Helloworld();
  void on_button_clicked();
protected:
  Glib::RefPtr<Gtk::Builder> builder;
  
  std::unique_ptr<Gtk::TreeView> s_view;
  //std::unique_ptr<Gtk::ScolledWindow> s_win;
  std::unique_ptr<Gtk::Box> s_box;

  std::unique_ptr<Gtk::Button> h_button;
  std::unique_ptr<Gtk::Label> h_label;
private:
  template <typename T_Widget>
  std::unique_ptr<T_Widget> get_widget(const Glib::ustring name, const Glib::RefPtr<Gtk::Builder> &builder);
};
