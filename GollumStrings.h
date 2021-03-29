
#pragma once

using namespace std;

const string GOLLUM_USAGE = R"(
    usage: gollum <action> <options>
    actions:
        - list      (lists all credentials from store. Options: [--show-pass, --pattern])
        - add       (add a new credential to store. Options: [--name, --password])
        - remove    (remove a credential from store. Options: [--name])
        - help      (displays this message)
    )";