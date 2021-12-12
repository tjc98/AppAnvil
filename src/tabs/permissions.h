#ifndef TABS_PERMISSIONS_H
#define TABS_PERMISSIONS_H

#include "status.h"
#include "status_column_record.h"

class Permissions : public Status {
  public:
    Permissions();
    void add_data_to_record(std::string data);
  private:
    const std::vector<std::string> col_names{"Path", "Permissions"};
    std::shared_ptr<StatusColumnRecord> col_record;
};

#endif // TABS_PERMISSIONS_H
