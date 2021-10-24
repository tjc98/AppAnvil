#include "helloworld.h"

template <typename T_Widget>
std::unique_ptr<T_Widget> Helloworld::get_widget(const Glib::ustring name, const Glib::RefPtr<Gtk::Builder> &builder){
  T_Widget *raw_addr = nullptr;
  builder->get_widget<T_Widget>(name, raw_addr);
  return std::unique_ptr<T_Widget>(raw_addr);
}

Helloworld::Helloworld()
: builder{Gtk::Builder::create_from_resource("/resources/hello.glade")},
  s_box{Helloworld::get_widget<Gtk::Box>("h_box", builder)},
  h_button{Helloworld::get_widget<Gtk::Button>("hellobutton", builder)},
  h_label{Helloworld::get_widget<Gtk::Label>("hellolabel", builder)}
{
  this->add(*s_box);
  h_button->signal_clicked().connect(sigc::mem_fun(*this, &Helloworld::on_button_clicked));
}

void Helloworld::on_button_clicked()
{
  h_label->set_text("Hello world");
}

