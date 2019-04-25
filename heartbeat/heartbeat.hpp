// Smart Contract Name: heartbeat_contract
// Table struct:
//   notestruct: multi index table to store the heartbeat data
//     user(account_name/uint64): account name for the bp
//     metadata_json(string): the metadata
//     timestamp(uint64): the last update block time
// Public method:
//   isnewuser => to check if the given account name has entry in table or not
// Public actions:
//   heartbeat => put the metadata into the multi-index table and sign by the given account

#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

namespace heartbeat{
    using namespace eosio;
    using eosio::name;

    struct [[eosio::table("hbstruct"), eosio::contract("heartbeat")]] hbstruct {
        name  user;      // account name for the user
        std::string   metadata_json;      // the note message
        uint64_t      timestamp; // the store the last update block time
        // primary key
        uint64_t primary_key() const { return user.value; }
    };

    typedef eosio::multi_index< "hbstruct"_n, hbstruct> hbtable;

    class [[eosio::contract("heartbeat")]] heartbeat_contract : public eosio::contract {
        public:
            using eosio::contract::contract; // 引入父命名空间
            ACTION heartbeat( name _user, std::string& _metadata_json );
        private:
            bool isnewuser( name user );
    };
}
