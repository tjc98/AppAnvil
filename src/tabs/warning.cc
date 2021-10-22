#include "warning.h"
#include <iostream>
#include <giomm.h>
#include <glibmm.h>

template <typename T_Widget>
  std::unique_ptr<T_Widget> Warning::get_widget(const Glib::ustring name, const Glib::RefPtr<Gtk::Builder> &builder){
  T_Widget *raw_addr = nullptr;
  builder->get_widget<T_Widget>(name, raw_addr);
  return std::unique_ptr<T_Widget>(raw_addr);
}

Warning::Warning(const std::string& profile, const std::string& status, Gtk::Dialog& dialog)
: builder{Gtk::Builder::create_from_resource("/resources/warning.glade")},
  w_box1{Warning::get_widget<Gtk::Box>("w_box1", builder)},
  w_box2{Warning::get_widget<Gtk::Box>("w_box2", builder)},
  w_label{Warning::get_widget<Gtk::Label>("w_label", builder)},
  w_button1{Warning::get_widget<Gtk::Button>("w_button1", builder)},
  w_button2{Warning::get_widget<Gtk::Button>("w_button2", builder)}
{
  //auto w_dialog = Gtk::make_managed<Gtk::Dialog>(dialog);
  w_status = std::make_unique<std::basic_string<char>>(status);
  w_profile = std::make_unique<std::basic_string<char>>(profile);
  w_button1->signal_clicked().connect(sigc::mem_fun(*this, &Warning::do_continue));
  w_button2->signal_clicked().connect(sigc::mem_fun(*this, &Warning::not_continue));
  this->add(*w_box1);
  this->show_all();
}

void Warning::do_continue() //confirms change in mode of enforcement
{
  std::vector<std::string> args = {"sudo", *w_status, *w_profile};
  std::string child_output;
  std::string child_error;
  int exit_status = 0;


  //Executed in commandline, copied from status.cc 
  Glib::spawn_sync("/usr/sbin/", args, Glib::SpawnFlags::SPAWN_DEFAULT, {}, &child_output, &child_error, &exit_status);


  if(exit_status != 0){
    std::cout << "Error calling '"<< args[0] <<"'. " << child_error << std::endl;
    child_output = "{\"processes\": {}, \"profiles\": {}";
  }
  //*w_dialog->close();
}  

void Warning::not_continue() //no change to mode of enforcement
{
  //*w_dialog->close();
}

