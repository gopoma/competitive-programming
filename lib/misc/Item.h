struct Item {
    int nxt;
    int group;

    Item() {}

    Item(int _nxt, int _group): nxt(_nxt), group(_group) {}

    bool operator<(const Item& rhs) const { //! Note the last const
        if(nxt == rhs.nxt) return group < rhs.group;
        return nxt < rhs.nxt;
    }
};

// TODO: For Comparator for set/multiset/priority_queue
multiset<Item> ms; ms.emplace(Item(-79, 1));
set<Item> ms2; ms2.emplace(Item(-79, 1));
priority_queue<Item> ms3; ms3.push(Item(-79, 1));
