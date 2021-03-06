// AirMap Platform SDK
// Copyright © 2018 AirMap, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef AIRMAP_MONITOR_DAEMON_H_
#define AIRMAP_MONITOR_DAEMON_H_

#include <airmap/authenticator.h>
#include <airmap/client.h>
#include <airmap/context.h>
#include <airmap/flights.h>
#include <airmap/grpc/server/executor.h>
#include <airmap/logger.h>
#include <airmap/mavlink/channel.h>
#include <airmap/mavlink/vehicle.h>
#include <airmap/mavlink/vehicle_tracker.h>
#include <airmap/monitor/fan_out_traffic_monitor.h>

#include <airmap/monitor/telemetry_submitter.h>
#include <airmap/util/formatting_logger.h>

#include <memory>
#include <thread>

namespace airmap {
/// namespace monitor bundles up all types and functions used in running AirMap's monitor daemon.
namespace monitor {

/// Daemon respresents AirMap and all of its services within
/// the system. It listens to incoming data (both in terms of
/// sensors as well as in terms of control messages) and enables
/// a drone operation platform to deeply integrate airspace intelligence
/// in its operations.
class Daemon : public mavlink::VehicleTracker::Monitor, public std::enable_shared_from_this<Daemon> {
 public:
  /// Configuration bundles up construction time parameters.
  struct Configuration {
    Credentials credentials;                    ///< Credentials used to authenticate with the AirMap services.
    std::string aircraft_id;                    ///< The id of the aircraft that the monitor runs on.
    std::shared_ptr<Logger> logger;             ///< The logger instance.
    std::shared_ptr<mavlink::Channel> channel;  ///< The MavLink channel that should be monitored.
    std::shared_ptr<Context> context;           ///< Target context for incoming calls.
    std::shared_ptr<airmap::Client> client;     ///< The client used to communicate with the AirMap cloud services.
    std::string grpc_endpoint;                  ///< The local endpoint that the service should be exposed on.
  };

  // create returns a new Daemon instance ready for startup.
  static std::shared_ptr<Daemon> create(const Configuration& configuration);

  ~Daemon();

  /// Puts the daemon to execution.
  void start();

 protected:
  // From VehicleTracker::Monitor
  void on_vehicle_added(const std::shared_ptr<mavlink::Vehicle>& vehicle) override;
  void on_vehicle_removed(const std::shared_ptr<mavlink::Vehicle>& vehicle) override;

 private:
  /// Daemon initializes a new instance with the functional
  /// dependencies provided via 'configuration'.
  explicit Daemon(const Configuration& configuration);

  /// finalize sets up all internal event connections that require
  /// shared_from_this() to work properly.
  std::shared_ptr<Daemon> finalize();

  void handle_mavlink_message(const mavlink_message_t& msg);

  Configuration configuration_;

  util::FormattingLogger log_;
  std::shared_ptr<FanOutTrafficMonitor> fan_out_traffic_monitor_;
  std::shared_ptr<grpc::server::Executor> executor_;
  std::thread executor_worker_;
  std::shared_ptr<mavlink::LoggingVehicleTrackerMonitor> vehicle_tracker_monitor_;
  mavlink::VehicleTracker vehicle_tracker_;
  mavlink::Channel::Subscription mavlink_channel_subscription_;
  mavlink::Channel::Subscription logging_channel_subscription_;
};

}  // namespace monitor
}  // namespace airmap

#endif  // AIRMAP_DAEMON_H_
