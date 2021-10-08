#include "profilewindow.h"

#include <gtkmm/button.h>
#include <gtkmm/label.h>

template <typename T_Widget>
std::unique_ptr<T_Widget> Profilewindow::get_widget(const Glib::ustring name, const Glib::RefPtr<Gtk::Builder> &builder){
  T_Widget *raw_addr = nullptr;
  builder->get_widget<T_Widget>(name, raw_addr);
  return std::unique_ptr<T_Widget>(raw_addr);
}

Profilewindow::Profilewindow()
: builder{Gtk::Builder::create_from_resource("/resources/profilewindow.glade")},
  p_win{Profilewindow::get_widget<Gtk::Window>("pr_win", builder)},
  p_box{Profilewindow::get_widget<Gtk::Box>("pr_box", builder)},
  p_name{Profilewindow::get_widget<Gtk::Label>("pr_name", builder)},
  p_modes{Profilewindow::get_widget<Gtk::ComboBoxText>("pr_modes", builder)},
  p_confirm{Profilewindow::get_widget<Gtk::Button>("pr_confirm", builder)}
{
  p_confirm->signal_clicked().connect(sigc::mem_fun(*this, &Profilewindow::on_button_clicked));
}

void Profilewindow::on_button_clicked()
{
  std::string choice = p_modes->get_active_text();
  if(choice.compare("Enforce") == 0)
  {
     
  }
  else if(choice.compare("Complain") == 0)
  {
  
  }
}
