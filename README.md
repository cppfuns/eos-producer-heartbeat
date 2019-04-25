## 合约编译
cd heartbeat
eosio-cpp -o heartbeat.wasm heartbeat.cpp -I ./ --abigen
