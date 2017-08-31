
#ifndef AIRMAP_CODEC_JSON_AUTHENTICATOR_H_
#define AIRMAP_CODEC_JSON_AUTHENTICATOR_H_

#include <airmap/authenticator.h>

#include <nlohmann/json.hpp>

#include <vector>

namespace airmap {
namespace codec {
namespace json {

void decode(const nlohmann::json& j, Authenticator::OAuthToken& token);
void decode(const nlohmann::json& j, Authenticator::OAuthToken::Type& type);
void decode(const nlohmann::json& j, Authenticator::AnonymousToken& token);
void decode(const nlohmann::json& j, Authenticator::RefreshedToken& token);
void decode(const nlohmann::json& j, Authenticator::RefreshedToken::Type& type);
void encode(nlohmann::json& j, const Authenticator::GrantType& type);
void encode(nlohmann::json& j, const Authenticator::Scope& scope);
void encode(nlohmann::json& j, const Authenticator::Connection& connection);
void encode(nlohmann::json& j, const Authenticator::AuthenticateWithPassword::Params& params);
void encode(nlohmann::json& j, const Authenticator::AuthenticateAnonymously::Params& params);
void encode(nlohmann::json& j, const Authenticator::RenewAuthentication::Params& params);

}  // namespace json
}  // namespace codec
}  // namespace airmap

#endif  // AIRMAP_CODEC_JSON_AUTHENTICATOR_H_
