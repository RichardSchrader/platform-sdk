#ifndef AIRMAP_CMDS_AIRMAP_CMD_AUTHORIZE_PASSWORD_H_
#define AIRMAP_CMDS_AIRMAP_CMD_AUTHORIZE_PASSWORD_H_

#include <airmap/cmds/airmap/cmd/flags.h>

#include <airmap/authenticator.h>
#include <airmap/client.h>
#include <airmap/util/cli.h>
#include <airmap/util/formatting_logger.h>
#include <airmap/util/tagged_string.h>

namespace airmap {
namespace cmds {
namespace airmap {
namespace cmd {

class AuthorizePassword : public util::cli::CommandWithFlagsAndAction {
 public:
  AuthorizePassword();

 private:
  using Username = util::TaggedString<util::tags::MustNotBeEmpty>;
  using Password = util::TaggedString<util::tags::MustNotBeEmpty>;
  using Device   = util::TaggedString<util::tags::MustNotBeEmpty>;

  util::FormattingLogger log_{create_null_logger()};
  struct {
    Client::Version version{Client::Version::production};
    Logger::Severity log_level{Logger::Severity::info};
    Required<ApiKey> api_key;
    Required<ClientId> client_id;
    Required<Username> username;
    Required<Password> password;
    Required<Device> device;
  } params_;
};

}  // namespace cmd
}  // namespace airmap
}  // namespace cmds
}  // namespace airmap

#endif  // AIRMAP_CMDS_AIRMAP_CMD_AUTHORIZE_PASSWORD_H_
