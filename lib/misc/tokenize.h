vector<string> tokenize(string line, string separator) {
    vector<string> tokens;
    while(true) {
        string token = line.substr(0, line.find(separator));
        tokens.emplace_back(token);

        if(line.find(separator) == string::npos) {
            break;
        }
        line = line.substr(line.find(separator) + 1, int(line.size()) - line.find(separator) + 1);
    }
    return tokens;
};
