#include "command_caller.h"

#include <glibmm.h>
#include <iostream>
#include <vector>

///*
#include <cstdlib>
#include <cstdio>
//*/


std::string CommandCaller::get_status_str(){
  std::vector<std::string> args = {"pkexec", "aa-status","--json"};

  std::string child_output;
  std::string child_error;
  int exit_status = 0;

  Glib::spawn_sync("/usr/sbin/", args, Glib::SpawnFlags::SPAWN_DEFAULT, {}, &child_output, &child_error, &exit_status);

  if(exit_status != 0){
    std::cout << "Error calling '"<< args[0] <<"'. " << child_error << std::endl;
    child_output = "{\"processes\": {}, \"profiles\": {}";
  }

  return child_output;
}

//Status must be aa-complain, aa-enforce, or aa-disable
std::string CommandCaller::set_status(std::string profileName, std::string status){
  std::vector<std::string> args = {"pkexec", status, profileName};

  std::string child_output;
  std::string child_error;
  int exit_status = 0;


  //Executed in commandline, copied from status.cc 
  Glib::spawn_sync("/usr/sbin/", args, Glib::SpawnFlags::SPAWN_DEFAULT, {}, &child_output, &child_error, &exit_status);


  if(exit_status != 0){
    std::cout << "Error calling '"<< args[0] <<"'. " << child_error << std::endl;
    child_output = child_error;
  }

  return child_output;
}

std::string CommandCaller::get_unconfined(){
  std::vector<std::string> args = {"pkexec", "aa-unconfined"};

  std::string child_output;
  std::string child_error;
  int exit_status = 0;

  Glib::spawn_sync("/usr/sbin/", args, Glib::SpawnFlags::SPAWN_DEFAULT, {}, &child_output, &child_error, &exit_status);

  if(exit_status != 0){
    std::cout << "Error calling '"<< args[0] <<"'. " << child_error << std::endl;
    child_output = "";
  }

  return child_output;
}

std::string CommandCaller::get_logs_str(){
  std::vector<std::string> args = {"dmesg"};

  std::string child_output;
  std::string child_error;
  int exit_status = 0;

  Glib::spawn_sync("/usr/sbin/", args, Glib::SpawnFlags::SPAWN_DEFAULT, {}, &child_output, &child_error, &exit_status);

  if(exit_status != 0){
    std::cout << "Error calling '"<< args[0] <<"'. " << child_error << std::endl;
    child_output = "";
  }

  return child_output;
}

std::string CommandCaller::load_profile(std::string fullFileName){


  std::vector<std::string> args = {"pkexec", "mv", fullFileName, "/etc/apparmor.d"};
  //std::vector<std::string> args = {"echo", password, "|", "sudo", "-S", "mv", fullFileName, "/etc/apparmor.d"};

  std::string child_output;
  std::string child_error;
  int exit_status = 0;

  Glib::spawn_sync(".", args, Glib::SpawnFlags::SPAWN_DEFAULT, {}, &child_output, &child_error, &exit_status);

  if(exit_status != 0){
    std::cout << "Error calling '"<< args[0] <<"'. " << child_error << std::endl;

    return child_error;
  }


  std::string fileName; //name without path
  fileName = fullFileName.substr(fullFileName.find_last_of("/") + 1);

  args = {"pkexec", "apparmor_parser", "-r", "/etc/apparmor.d/" + fileName};
 // args = {"echo", password, "|", "sudo", "-S", "apparmor_parser", "-r", "/etc/apparmor.d/" + fileName};

  exit_status = 0;

  Glib::spawn_sync(".", args, Glib::SpawnFlags::SPAWN_DEFAULT, {}, &child_output, &child_error, &exit_status);

  if(exit_status != 0){
    std::cout << "Error calling '"<< args[0] <<"'. " << child_error << std::endl;

    return child_error;
  }

  //std::cout<<"load_profile ending\n";
  return fileName;

}