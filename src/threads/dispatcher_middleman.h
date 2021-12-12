#ifndef SRC_THREADS_DISPATCHER_MIDDLEMAN_H
#define SRC_THREADS_DISPATCHER_MIDDLEMAN_H

#include "../tabs/logs.h"
#include "../tabs/processes.h"
#include "../tabs/profiles.h"
#include "../tabs/file_chooser.h"
#include "../tabs/permissions.h"

#include <glibmm/dispatcher.h>
#include <mutex>

/**
 * Class to extend some of the functionality of `Dispatcher` to easier facilitate inter-thread
 * communication between the second thread and main thread. This is needed to prevent some
 * concurrency errors with the GUI.
 **/
class DispatcherMiddleman
{
  public:
    // Constructor
    DispatcherMiddleman(std::shared_ptr<Profiles> prof, std::shared_ptr<Processes> proc, std::shared_ptr<Logs> logs, std::shared_ptr<FileChooser> file_chooser, std::shared_ptr<Permissions> perms);

    // Send methods (called from second thread)
    void update_profiles(std::string confined);
    void update_processes(std::string confined, std::string unconfined);
    void update_logs(std::string logs);

  protected:
    enum CallState {
      NONE,
      PROFILE,
      PROCESS,
      LOGS,
      FILECHOOSER,
      PERMISSIONS
    };

    // Receive method (called from main thread)
    void handle_signal();

  private:
    Glib::Dispatcher dispatch;

    CallState state;
    std::string data1;
    std::string data2;

    std::shared_ptr<Profiles> prof;
    std::shared_ptr<Processes> proc;
    std::shared_ptr<Logs> logs;
    std::shared_ptr<FileChooser> file_chooser;
    std::shared_ptr<Permissions> perms;

    // Synchronization
    std::mutex mtx;
};

#endif // SRC_THREADS_DISPATCHER_MIDDLEMAN_H
