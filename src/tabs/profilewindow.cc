#include "profilewindow.h"
#include <iostream>
#include <giomm.h>
#include <glibmm.h>

template <typename T_Widget>
std::unique_ptr<T_Widget> Profilewindow::get_widget(const Glib::ustring name, const Glib::RefPtr<Gtk::Builder> &builder){
  T_Widget *raw_addr = nullptr;
  builder->get_widget<T_Widget>(name, raw_addr);
  return std::unique_ptr<T_Widget>(raw_addr);
}

Profilewindow::Profilewindow(const std::string& profile, const std::string& status)
: builder{Gtk::Builder::create_from_resource("/resources/profilewindow.glade")},
  p_box{Profilewindow::get_widget<Gtk::Box>("pr_box", builder)},
  p_name{Profilewindow::get_widget<Gtk::Label>("pr_name", builder)},
  p_modes{Profilewindow::get_widget<Gtk::ComboBoxText>("pr_modes", builder)},
  p_confirm{Profilewindow::get_widget<Gtk::Button>("pr_confirm", builder)}
{
  c_status = std::make_unique<std::basic_string<char>>(status);
  c_profile = std::make_unique<std::basic_string<char>>(profile);
  p_confirm->signal_clicked().connect(sigc::mem_fun(*this, &Profilewindow::on_button_clicked));
  this->add(*p_box);
  p_name->set_label(profile);
  this->show_all();
}

void Profilewindow::on_button_clicked()
{
  std::string choice = p_modes->get_active_text();
  std::cout << choice << std::endl;
  std::string new_status;
  if(choice.compare("Enforce") == 0)
  {
     new_status = "aa-enforce";
  }
  else if(choice.compare("Complain") == 0)
  {
     new_status = "aa-complain";
  }
  std::basic_string<char> temp_s = *c_status;
  std::string temp_s2 = temp_s.c_str();
  std::cout << temp_s2 << std::endl;
  if(temp_s2.compare("enforce") == 0 && new_status.compare("aa-complain") == 0) //lowering mode of enforcement, send warning
  {
         std::cout << "test" << std::endl;
         w_settings.reset(new Warning(*c_profile, *c_status, *w_dialog));
  	  w_dialog.reset(new Gtk::Dialog("Warning"));
  	  w_dialog->set_modal(true);
  	  w_dialog->get_content_area()->pack_start(*w_settings, true, true);
  	  w_dialog->set_size_request(DEFAULT_POPUP_WIDTH2/2, DEFAULT_POPUP_HEIGHT2/2);
  	  w_dialog->set_default_size(DEFAULT_POPUP_WIDTH2, DEFAULT_POPUP_HEIGHT2);
  	  w_dialog->show();
  }
  else
  {
     std::vector<std::string> args = {"sudo", new_status, *c_profile};

     std::string child_output;
     std::string child_error;
     int exit_status = 0;


     //Executed in commandline, copied from status.cc 
     Glib::spawn_sync("/usr/sbin/", args, Glib::SpawnFlags::SPAWN_DEFAULT, {}, &child_output, &child_error, &exit_status);


     if(exit_status != 0){
       std::cout << "Error calling '"<< args[0] <<"'. " << child_error << std::endl;
       child_output = "{\"processes\": {}, \"profiles\": {}";
  }
  }
}
