#ifndef AIRMAP_CMDS_AIRMAP_CMD_START_FLIGHT_COMMS_H_
#define AIRMAP_CMDS_AIRMAP_CMD_START_FLIGHT_COMMS_H_

#include <airmap/cmds/airmap/cmd/flags.h>

#include <airmap/client.h>
#include <airmap/flight.h>
#include <airmap/flights.h>
#include <airmap/telemetry.h>
#include <airmap/util/cli.h>
#include <airmap/util/formatting_logger.h>
#include <airmap/util/tagged_string.h>

namespace airmap {
namespace cmds {
namespace airmap {
namespace cmd {

class StartFlightComms : public util::cli::CommandWithFlagsAndAction {
 public:
  StartFlightComms();

 private:
  util::FormattingLogger log_{create_null_logger()};
  struct {
    Client::Version version{Client::Version::production};
    Logger::Severity log_level{Logger::Severity::info};
    Required<ApiKey> api_key;
    Required<Authorization> authorization;
    Required<FlightId> flight_id;
  } params_;
};

}  // namespace cmd
}  // namespace airmap
}  // namespace cmds
}  // namespace airmap

#endif  // AIRMAP_CMDS_AIRMAP_CMD_START_FLIGHT_COMMS_H_
