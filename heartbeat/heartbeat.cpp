#include "heartbeat.hpp"
using namespace heartbeat;

void heartbeat_contract::heartbeat( name _user, std::string& _metadata_json ) {
  // to sign the action with the given account
  require_auth( _user.value );

  hbtable obj(_self, _self.value); // code, scope

  // create new / update hb depends whether the user account exist or not
  if (isnewuser(_user)) {
    // insert object
    obj.emplace( _user, [&]( auto& address ) {
      address.user                 = _user;
      address.metadata_json        = _metadata_json;
      address.timestamp            = now();
    });
  } else {
    auto &hb = obj.get(_user.value);
    // update object
    obj.modify( hb, _user, [&]( auto& address ) {
      address.metadata_json        = _metadata_json;
      address.timestamp   = now();
    });
  }
}

bool heartbeat_contract::isnewuser( name user ) {
  hbtable hbobj(_self, _self.value);
  // get object by secordary key
  auto hb = hbobj.find(user.value);
  return hb == hbobj.end();
}


     