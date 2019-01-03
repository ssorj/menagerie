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
#include <proton/message.hpp>
#include <proton/messaging_handler.hpp>
#include <proton/sender.hpp>
#include <proton/target.hpp>

#include <iostream>
#include <string>

struct send_handler : public proton::messaging_handler {
    std::string address_ {};
    std::string message_body_ {};

    void on_connection_open(proton::connection& conn) override {
        std::cout << "SEND: Connected to '" << conn.container_id() << "'\n";
        conn.open_sender(address_);
    }

    void on_sendable(proton::sender& snd) override {
        proton::message msg {message_body_};
        snd.send(msg);

        std::cout << "SEND: Sent message '" << msg.body() << "'\n";

        snd.close();
        snd.connection().close();
    }
};

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "Usage: send <connection-url-1> <connection-url-2> <address> <message-body>\n";
        return 1;
    }

    proton::container cont {};

    send_handler h1 {};
    h1.address_ = argv[3];
    h1.message_body_ = argv[4];

    send_handler h2 {};
    h2.address_ = argv[3];
    h2.message_body_ = argv[4];

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
