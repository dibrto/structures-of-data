#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <iomanip>

using namespace std;

template <typename K, typename V>
class ListMap
{
public:
    class Pair
    {
    public:
        Pair(const K &k = K(), const V &v = V()) : _key(k), _value(v) {}

        const K &GetKey() const { return _key; }
        void SetKey(const K &val) { _key = val; }

        const V &GetValue() const { return _value; }
        void SetValue(const V &val) { _value = val; }

    private:
        K _key;
        V _value;
    };

    typedef typename list<Pair>::iterator MIter;
    ListMap() : n(0) {}
    int size() const { return n; } // LMap.size();
    bool empty() const { return size() == 0; }
    MIter begin() { LMap.begin(); }
    MIter end() { LMap.end(); }

    MIter find(const K &k);
    MIter put(const K &k, const V &v);
    void erase(const K &k);
    void erase(const MIter &p);
    void print();

private:
    int n;
    list<Pair> LMap;
};

template <typename K, typename V>
typename ListMap<K, V>::MIter ListMap<K, V>::find(const K &k)
{
    for (MIter p = LMap.begin(); p != LMap.end(); p++)
    {
        Pair currenrPair = *p;
        if ((*p).GetKey() == k)
            return p;
    }
    return end();
}

template <typename K, typename V>
typename ListMap<K, V>::MIter ListMap<K, V>::put(const K &k, const V &v)
{
    Pair newPair = Pair(k, v);
    MIter p;
    for (p = LMap.begin(); p != LMap.end(); p++)
    {
        Pair currenrPair = *p;
        if (currenrPair.GetKey() == k)
        {
            *p = newPair;
            return p;
        }
    }
    LMap.insert(p, newPair);
    n++;
    return p;
}

template <typename K, typename V>
void ListMap<K, V>::erase(const K &k)
{
    for (MIter p = LMap.begin(); p != LMap.end(); p++)
    {
        if ((*p).GetKey() == k)
            LMap.erase(p);
        n--;
    }
}

template <typename K, typename V>
void ListMap<K, V>::erase(const MIter &p)
{
    LMap.erase(p);
    n--;
}
template <typename K, typename V>
void ListMap<K, V>::print()
{
    ListMap<int, int>::Pair cPair;
    cout << setw(6) << "Keys" << setw(11) << "Values" << endl;
    for (MIter p = LMap.begin(); p != LMap.end(); p++)
    {
        cPair = *p;
        cout << "Key: " << cPair.GetKey() << setw(10) << "Value: " << cPair.GetValue() << endl;
    }
}