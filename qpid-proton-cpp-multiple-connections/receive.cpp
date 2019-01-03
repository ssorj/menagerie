/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#include <proton/connection.hpp>
#include <proton/connection_options.hpp>
#include <proton/container.hpp>
#include <proton/delivery.hpp>
#include <proton/message.hpp>
#include <proton/messaging_handler.hpp>
#include <proton/receiver.hpp>
#include <proton/source.hpp>

#include <iostream>
#include <string>

struct receive_handler : public proton::messaging_handler {
    std::string address_ {};
    int desired_ {0};
    int received_ {0};

    void on_connection_open(proton::connection& conn) override {
        std::cout << "RECEIVE: Connected to '" << conn.container_id() << "'\n";
        conn.open_receiver(address_);
    }

    void on_message(proton::delivery& dlv, proton::message& msg) override {
        std::cout << "RECEIVE: Received message '" << msg.body() << "'\n";

        received_++;

        if (received_ == desired_) {
            dlv.receiver().close();
            dlv.connection().close();
        }
    }
};

int main(int argc, char** argv) {
    if (argc != 4 && argc != 5) {
        std::cerr << "Usage: receive <connection-url-1> <connection-url-2> <address> [<message-count>]\n";
        return 1;
    }

    proton::container cont {};

    receive_handler h1 {};
    h1.address_ = argv[3];

    receive_handler h2 {};
    h2.address_ = argv[3];

    if (argc == 5) {
        h1.desired_ = std::stoi(argv[4]);
        h2.desired_ = std::stoi(argv[4]);
    }

    cont.connect(argv[1], proton::connection_options {h1});
    cont.connect(argv[2], proton::connection_options {h2});
    
    try {
        cont.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
